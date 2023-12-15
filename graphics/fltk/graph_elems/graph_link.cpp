#include "graph_link.h"
#include "graph_elem.h"

using namespace graph;

Link::Link(Port* c1, Port* c2)
    : Fl_Widget{std::min(c1->x(), c2->x()), std::min(c1->y(), c2->y()),
                abs(c1->x() - c2->x()) + c1->w(),
                abs(c1->y() - c2->y()) + c1->w()}
{
  if (c1->get_type() == port_types::input)
  {
    input_port = c1;
    output_port = c2;
  }
  else
  {
    output_port = c1;
    input_port = c2;
  }
  c1->add_link(this);
  c2->add_link(this);
  {  // add link to logic

    logic::Element* in_log_el = ((graph::Element*)(input_port->parent()))
                                    ->get_draw_elem()
                                    ->logic_elem;
    logic::Element* out_log_el = ((graph::Element*)(output_port->parent()))
                                     ->get_draw_elem()
                                     ->logic_elem;
    // Установили связь
    if (input_port->is_inverted())
      (*out_log_el) >> ~(*in_log_el);
    else
      (*out_log_el) >> (*in_log_el);
  }
}

// отрисовка объектов класса Link
void Link::draw()
{
  fl_line_style(0, 3);
  fl_color(FL_BLACK);

  fl_line(input_port->x(), input_port->y() + input_port->h() / 2,
          output_port->x() + output_port->w(),
          output_port->y() + output_port->h() / 2);
}

void Link::delete_link()
{
  logic::Element* input_log_el;
  logic::Element* output_log_el;

  // удаляем связь из порта-начала:
  for (int i = 0;
       ((input_port != nullptr) && (i < input_port->get_links().size()));
       i++)
  {
    if (input_port->get_links()[i] == this)
    {
      input_port->delete_link_by_index(i);

      input_log_el =
          ((Element*)(input_port->parent()))->get_draw_elem()->logic_elem;
      break;
    }
  }

  // удаляем связь из порта-конца:
  for (int i = 0;
       ((input_port != nullptr) && (i < output_port->get_links().size()));
       i++)
  {
    if (output_port->get_links()[i] == this)
    {
      output_port->delete_link_by_index(i);

      output_log_el =
          ((Element*)(output_port->parent()))->get_draw_elem()->logic_elem;
      break;
    }
  }

  if (input_log_el->remove_sorse(output_log_el, input_port->is_inverted()))
    std::cout << "deleted sorse" << std::endl;

  /*
  {// нужно удалять сам входной порт
  auto temp = (graph::Element*)input_port->parent();
  temp->delete_port(input_port);
  int n = temp->get_input_ports().size();

  temp->resize(temp->x(), temp->y(), temp->w(),
               (temp->h()) * (n + 1) / (n + 2));
  int circle_w = temp->w();
  circle_w /= 9;
  for (int i = 0; i < n; i++)
  {
    Port* l_c = temp->get_input_ports()[i];
    l_c->resize(temp->x(),
                temp->y() + temp->h() / (n + 1) * (i + 1) - circle_w / 2,
                circle_w, circle_w);
  }
  temp->get_output_port()->resize(temp->x() + temp->w() - circle_w,
                                  temp->y() + temp->h() / 2 - circle_w / 2,
                                  circle_w, circle_w);
}
*/
  // удаляем связь как виджет:
  Fl::delete_widget(this);
  Fl::do_widget_deletion();
}

void Link::delete_link_input_port()
{
  logic::Element* input_log_el;
  logic::Element* output_log_el;

  // удаляем связь из порта-начала:
  for (int i = 0;
       ((input_port != nullptr) && (i < input_port->get_links().size()));
       i++)
  {
    if (input_port->get_links()[i] == this)
    {
      input_port->delete_link_by_index(i);

      input_log_el =
          ((Element*)(input_port->parent()))->get_draw_elem()->logic_elem;
      break;
    }
  }

  // удаляем связь из порта-конца:
  for (int i = 0;
       ((input_port != nullptr) && (i < output_port->get_links().size()));
       i++)
  {
    if (output_port->get_links()[i] == this)
    {
      output_port->delete_link_by_index(i);

      output_log_el =
          ((Element*)(output_port->parent()))->get_draw_elem()->logic_elem;
      break;
    }
  }

  if (input_log_el->remove_sorse(output_log_el, input_port->is_inverted()))
    std::cout << "deleted sorse" << std::endl;

  {  // нужно удалять сам входной порт
    auto temp = (graph::Element*)input_port->parent();
    temp->delete_port(input_port);
    int n = temp->get_input_ports().size();

    temp->resize(temp->x(), temp->y(), temp->w(),
                 (temp->h()) * (n + 1) / (n + 2));
    int circle_w = temp->w();
    circle_w /= 9;
    for (int i = 0; i < n; i++)
    {
      Port* l_c = temp->get_input_ports()[i];
      l_c->resize(temp->x(),
                  temp->y() + temp->h() / (n + 1) * (i + 1) - circle_w / 2,
                  circle_w, circle_w);
    }
    temp->get_output_port()->resize(
        temp->x() + temp->w() - circle_w,
        temp->y() + temp->h() / 2 - circle_w / 2, circle_w, circle_w);
  }

  // удаляем связь как виджет:
  Fl::delete_widget(this);
  Fl::do_widget_deletion();
}