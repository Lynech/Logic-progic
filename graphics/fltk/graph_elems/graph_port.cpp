#include "graph_port.h"
#include "graph_elem.h"

using namespace graph;

// конструктор класса LinkCircle
Port::Port(int x, int y, int w, int h, port_types t, const char* l)
    : Fl_Widget{x, y, w, h, l}
{
  links.clear();
  type = t;
  if (type == port_types::input)
  {
    menu = new Fl_Menu_Item[4];
    // TODO: make if-else to swap from "invert" to "uninvert"
    menu[0] = Fl_Menu_Item{"inversion",          port_menu::noshortcut,
                           invert_port,          this,
                           port_menu::noflag,    port_menu::labeltype,
                           port_menu::labelfont, port_menu::labelsize,
                           port_menu::labelcolor};
    menu[1] = Fl_Menu_Item{"delete links",       port_menu::noshortcut,
                           delete_link,          this,
                           port_menu::noflag,    port_menu::labeltype,
                           port_menu::labelfont, port_menu::labelsize,
                           port_menu::labelcolor};
    menu[2] = Fl_Menu_Item{"delete port",        port_menu::noshortcut,
                           delete_input_port,    this,
                           port_menu::noflag,    port_menu::labeltype,
                           port_menu::labelfont, port_menu::labelsize,
                           port_menu::labelcolor};
    menu[3] = Fl_Menu_Item{port_menu::endmenu,    port_menu::noshortcut,
                           port_menu::nocallback, port_menu::nouserdata,
                           port_menu::noflag,     port_menu::labeltype,
                           port_menu::labelfont,  port_menu::labelsize,
                           port_menu::labelcolor};
  }
  else
  {
    menu = new Fl_Menu_Item[3];
    menu[0] = Fl_Menu_Item{"inversion",          port_menu::noshortcut,
                           invert_port,          this,
                           port_menu::noflag,    port_menu::labeltype,
                           port_menu::labelfont, port_menu::labelsize,
                           port_menu::labelcolor};
    menu[1] = Fl_Menu_Item{"delete links",       port_menu::noshortcut,
                           delete_link,          this,
                           port_menu::noflag,    port_menu::labeltype,
                           port_menu::labelfont, port_menu::labelsize,
                           port_menu::labelcolor};
    menu[2] = Fl_Menu_Item{port_menu::endmenu,    port_menu::noshortcut,
                           port_menu::nocallback, port_menu::nouserdata,
                           port_menu::noflag,     port_menu::labeltype,
                           port_menu::labelfont,  port_menu::labelsize,
                           port_menu::labelcolor};
  }
}

Port::~Port()
{
  delete menu;
  for (size_t i = 0; i < links.size(); i++)
  {
    delete links[i];
  }
}

// отрисовка объектов класса LinkCircle
void Port::draw()
{
  fl_color(16);
  fl_line_style(0, 4);
  fl_pie(x(), y(), w(), h(), 0, 360);
  if (is_entered)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_arc(x(), y(), w(), h(), 0, 360);
  }
}

// обработка взаимодействий с объектом класса LinkCircle
int Port::handle(int event)
{
  switch (event)
  {
  case FL_PUSH:
    if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
    {
      auto temp = menu->popup(Fl::event_x(), Fl::event_y());
      if (temp && temp->callback())
        temp->do_callback(nullptr);
      return 1;
    }
    return 1;
  case FL_ENTER:
    is_entered = true;
    redraw();
    return 1;
  case FL_LEAVE:
    is_entered = false;
    redraw();
    return 1;
  case FL_RELEASE:
  {
    return release_handle();
  }
  default:
    return Fl_Widget::handle(event);
  }
}

int Port::release_handle()
{  // элемент (группа), которому принадлежит этот порт
  graph::Element* this_elem_group = (graph::Element*)this->parent();
  MapGroup* map = (MapGroup*)this_elem_group->parent();
  Port* p = find_port();
  if (!p)
    return 1;

  {  // add link to logic
    Port* input_port;
    Port* output_port;

    if (this->get_type() == port_types::input)
    {
      input_port = this;
      output_port = p;
    }
    else
    {
      output_port = this;
      input_port = p;
    }

    logic::Element* in_log_el = ((graph::Element*)(input_port->parent()))
                                    ->get_draw_elem()
                                    ->logic_elem;
    logic::Element* out_log_el = ((graph::Element*)(output_port->parent()))
                                     ->get_draw_elem()
                                     ->logic_elem;  // Установили связь
    if (input_port->is_inverted())
    {
      if (!((*out_log_el) >> ~(*in_log_el)))
        return 1;
    }
    else if (!((*out_log_el) >> (*in_log_el)))
      return 1;
  }

  Link* l = new Link{p, this};

  map->add(l);

  l->redraw();
  this->redraw();
  p->redraw();

  // is_entered = false;
  return 1;
}

Port* Port::find_port()
{
  graph::Element* this_elem_group = (graph::Element*)this->parent();
  MapGroup* map = (MapGroup*)this_elem_group->parent();
  int n = map->children();

  Port* p;

  graph::Element* elem_group;
  // bool needed_found = false;
  for (int i = 0; i < n; i++)
  {
    // взяли элемент (группа)
    elem_group = dynamic_cast<graph::Element*>(map->child(i));
    // кол-во сущностей в элементе
    if (elem_group != nullptr && (Fl::event_inside(elem_group)))
    {
      int n1 = elem_group->children();
      for (int j = 0; j < n1; j++)
      {
        // взяли сущность в надежде что она порт
        p = dynamic_cast<Port*>(elem_group->child(j));
        // проверяем, что это порт, он нужного типа и что наведение на
        // него
        if ((p != nullptr) && (Fl::event_inside(p)))
        {
          if ((p->type == this->type) || (p->linked()))
            return nullptr;
          return p;
        }
      }
    }
  }
  return nullptr;
}

bool Port::linked()
{
  bool res = 0;
  for (size_t i = 0; i < links.size() && !res; i++)
  {
    if (links[i])
      res = 1;
  }
  return res;
}

void Port::delete_link_by_index(int i)
{
  links.erase(links.begin() + i);
  std::vector<Link*>(links).swap(links);
}
