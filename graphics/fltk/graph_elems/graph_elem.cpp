#include "graph_elem.h"
using namespace graph;

// конструктор абстрактного класса Element
Element::Element(int x_, int y_, int w_, int h_, int inputs_n_,
                 const char* l)
    : Fl_Group{x_ - w_ * 2 / 5, y_, w_ * 9 / 5, h_, l}, inputs_n{inputs_n_},
      elem_link_lenth{w_ * 2 / 5}, line_thikness{w_ / 25}
{
  type = "element";
  input_ports.clear();
  end();
  draw_elem = new Label{x_, y_, w_, h_};
  add_resizable(*draw_elem);
  // если входных портов не ноль, добавляем 1 начальный порт
  if (inputs_n != 0)
  {
    Port* first_input_port =
        new Port{x_ - w_ * 2 / 5, y_ + h_ / 2 - w_ / 10, w_ / 5, w_ / 5,
                 port_types::input};

    add(first_input_port);

    input_ports.push_back(first_input_port);
  }

  // Выходной порт
  output_port = new Port{x_ + w_ * 6 / 5, y_ + h_ / 2 - w_ / 10, w_ / 5,
                         w_ / 5, port_types::output};
  add(output_port);

  // Добавляем входные порты если их число конечно или ограничено снизу
  for (int i = 1; i < inputs_n; i++)
    add_input_port_nodraw();
  if (inputs_n < 0)
    for (int i = 1; i < -inputs_n; i++)
      add_input_port_nodraw();
}

// Element::~Element()
// {
//   Fl::delete_widget(draw_elem);
//   Fl::do_widget_deletion();
//   delete menu;
//   delete output_port;
//   for (size_t i = 0; i < input_ports.size(); i++)
//     delete input_ports[i];
// }

void Element::draw()
{
  int x_ = x() + elem_link_lenth;
  int w_ = w() - 2 * elem_link_lenth;
  int y_ = y();
  int h_ = h();

  ////// если 0 портов - рисовать 1

  // input link
  int n = input_ports.size();  // кол-во входов
  for (int i = 0; i < n; i++)
  {
    fl_color(16);
    fl_line_style(0, 4);
    fl_line(x_, y_ + (h_ / (n + 1)) * (i + 1), x_ - elem_link_lenth,
            y_ + (h_ / (n + 1)) * (i + 1));
  }
  int x_output_link = x_ + w_ + elem_link_lenth;
  int y_output_link = y_ + h_ / 2;

  //  output link
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x_ + w_, y_ + h_ / 2, x_output_link, y_output_link);

  Fl_Group::draw();
}

void Element::invert()
{
  output_port->invert();
  redraw();
}

int Element::delete_port(Port* l_c)
{
  if ((l_c->get_type() == port_types::input) && (inputs_n < 0) &&
      (input_ports.size() > (size_t)(-inputs_n)))
  {
    for (size_t i = 0; i < input_ports.size(); i++)
    {
      if (input_ports[i] == l_c)
      {
        input_ports.erase(input_ports.begin() + i);
        std::vector<Port*>(input_ports).swap(input_ports);

        delete_link(nullptr, l_c);
        Fl::delete_widget(l_c);
        Fl::do_widget_deletion();
        return 1;
      }
    }
  }
  return 0;
}

void Element::add_input_port()
{
  if (inputs_n < 0)
  {
    add_input_port_nodraw();
    // если закомментировать, предположительно перестенет мерцать
    //  redraw();
    window()->redraw();
  }
}

void Element::add_input_port_nodraw()
{
  int n = this->input_ports.size();  // кол-во входов
  std::cout << x() << std::endl
            << y() << std::endl
            << w() << std::endl
            << h();
  this->resize(x(), y(), w(),
               (h()) * (n + 2) /
                   (n + 1));  // пропорционально увеличили всю группу

  int circle_w = this->w();
  circle_w /= 9;
  Port* new_l_s = new Port{0, 0, circle_w, circle_w, port_types::input};

  this->input_ports.push_back(new_l_s);
  this->add(new_l_s);

  n++;

  for (int i = 0; i < n; i++)
  {
    Port* l_c = input_ports[i];
    l_c->resize(x(), y() + h() / (n + 1) * (i + 1) - circle_w / 2, circle_w,
                circle_w);
  }

  output_port->resize(x() + w() - circle_w, y() + h() / 2 - circle_w / 2,
                      circle_w, circle_w);
}