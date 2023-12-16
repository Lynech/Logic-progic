#include "graph_label.h"
#include "graph_elem.h"

using namespace graph;

Label::Label(
    int x, int y, int w, int h, const char* l,
    std::function<void(int, int, int, int, logic::Value)> Label_draw)
    : Label_draw_{Label_draw}, Fl_Widget{x, y, w, h, l}
{
  menu = new Fl_Menu_Item[5];
  menu[0] = Fl_Menu_Item{"inversion",          port_menu::noshortcut,
                         invert_elem,          this,
                         port_menu::noflag,    port_menu::labeltype,
                         port_menu::labelfont, port_menu::labelsize,
                         port_menu::labelcolor};

  menu[1] = Fl_Menu_Item{"delete all links",    port_menu::noshortcut,
                         delete_all_elem_links, this,
                         port_menu::noflag,     port_menu::labeltype,
                         port_menu::labelfont,  port_menu::labelsize,
                         port_menu::labelcolor};
  menu[2] = Fl_Menu_Item{"delete elem",        port_menu::noshortcut,
                         delete_elem,          this,
                         port_menu::noflag,    port_menu::labeltype,
                         port_menu::labelfont, port_menu::labelsize,
                         port_menu::labelcolor};

  menu[3] = Fl_Menu_Item{"add port",
                         port_menu::noshortcut,
                         add_port,
                         this,
                         port_menu::noflag,
                         port_menu::labeltype,
                         port_menu::labelfont,
                         port_menu::labelsize,
                         port_menu::labelcolor};

  menu[4] = Fl_Menu_Item{
      port_menu::endmenu,    port_menu::noshortcut, port_menu::nocallback,
      port_menu::nouserdata, port_menu::noflag,     port_menu::labeltype,
      port_menu::labelfont,  port_menu::labelsize,  port_menu::labelcolor};
}

Label::~Label()
{
  delete menu;
  delete logic_elem;
}

void Label::delete_all_links()
{
  Element* el = (Element*)(this->parent());
  std::vector<Port*> ports = el->get_input_ports();

  // удаляем связи у каждого входа
  for (Port* i : ports)
  {
    if (i != nullptr)
    {
      std::vector<Link*> links = i->get_links();
      for (Link* j : links)
        if (j != nullptr)
        {
          j->delete_link();
        }
    }
  }
  // удаляем все связи у выхода
  Port* output_port = el->get_output_port();
  // std::vector<Link*> links = output_port->get_links();
  delete_link(nullptr, output_port);
  // удаляем выход
  el->delete_port(output_port);
}

void Label::draw()
{
  draw_box(FL_FLAT_BOX, 16);
  if (Label_draw_)
  {
    int x_elem = x() + w() / 6;
    int y_elem = y() + h() / 6;
    int w_elem = 2 * w() / 3;
    int h_elem = 2 * h() / 3;
    Label_draw_(x_elem, y_elem, w_elem, h_elem, logic_elem->get_value());
  }
  if (is_entered)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_rect(x() + 4, y() + 4, w() - 8, h() - 8);
  }

  // рисуем инвертированность выхода
  if (logic_elem->is_inverted())
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);

    fl_begin_polygon();
    fl_circle(x() + w() - w() / 11, y() + h() / 2, w() / 11);
    fl_end_polygon();

    fl_color(FL_WHITE);
    fl_line_style(0, 2);
    fl_begin_loop();
    fl_circle(x() + w() - w() / 10, y() + h() / 2, w() / 10);
    fl_end_loop();
  }

  // рисуем инвертированность входа
  Element* par = (Element*)(this->parent());
  std::vector<Port*> input_ports = par->get_input_ports();

  for (size_t i = 0; i < input_ports.size(); i++)
  {
    if (input_ports[i]->is_inverted())
    {
      Port* p = input_ports[i];
      fl_color(FL_BLACK);
      fl_line_style(0, 2);

      fl_begin_polygon();
      fl_circle(this->x() + this->w() / 11, p->y() + p->h() / 2,
                this->w() / 11);
      fl_end_polygon();

      fl_color(FL_WHITE);
      fl_line_style(0, 2);
      fl_begin_loop();
      fl_circle(this->x() + this->w() / 10, p->y() + p->h() / 2,
                this->w() / 10);
      fl_end_loop();
    }
  }
}

int Label::handle(int event)
{
  if (event == FL_ENTER)
  {
    std::cout << "+__________Label_enter__________+\n";
    is_entered = true;
    redraw();
    return 1;
  }
  if (event == FL_LEAVE)
  {
    std::cout << "+__________Label_leave__________+\n";
    is_entered = false;
    redraw();
    return 1;
  }
  if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
  {
    auto temp = menu->popup(Fl::event_x(), Fl::event_y());
    if (temp && temp->callback())
      temp->do_callback(nullptr);
    return 1;
  }
  return 1;
  // return 0;
}