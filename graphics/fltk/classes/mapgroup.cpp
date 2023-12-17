#include "mapgroup.h"
#include "type_elem.h"

namespace map_menu {
uchar noflag = 0;
uchar labeltype = FL_NORMAL_LABEL;
uchar labelfont = FL_HELVETICA;
uchar labelsize = FL_NORMAL_SIZE;
uchar labelcolor = FL_BLACK;
uchar noshortcut = 0;
const char* endmenu = 0;
Fl_Callback* nocallback = nullptr;
void* nouserdata = nullptr;
};  // namespace map_menu

void MapGroup::add_el(TypeElement what_el, int x, int y)
{
  if (what_el == TypeElement::AND)
    add_elem_from_file<graph::And>(nullptr, this, x, y);
  else if (what_el == TypeElement::OR)
    add_elem_from_file<graph::Or>(nullptr, this, x, y);
  else if (what_el == TypeElement::BUFF)
    add_elem_from_file<graph::Buff>(nullptr, this, x, y);
  else if (what_el == TypeElement::SRC0)
    add_elem_from_file<graph::Src0>(nullptr, this, x, y);
  else if (what_el == TypeElement::SRC1)
    add_elem_from_file<graph::Src1>(nullptr, this, x, y);
}

int MapGroup::handle(int event)
{
  if (Fl_Group::handle(event))
    return 1;
  if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
  {
    auto temp = menu->popup(Fl::event_x(), Fl::event_y());
    if (temp && temp->callback())
      temp->do_callback(nullptr);
    return 1;
  }
  if (event == FL_PUSH && Fl::event_button() == FL_LEFT_MOUSE)
  {
    Fl_Scroll* mama = (Fl_Scroll*)parent();
    moving_left = 1;
    x_ = Fl::event_x() + mama->xposition();
    y_ = Fl::event_y() + mama->yposition();
    return 1;
  }
  if (event == FL_DRAG && moving_left &&
      Fl::event_button() == FL_LEFT_MOUSE)
  {
    Fl_Scroll* mama = (Fl_Scroll*)parent();

    mama->scroll_to(choise(x_min, x_ - Fl::event_x(), x_max),
                    choise(y_min, y_ - Fl::event_y(), y_max));
    return 1;
  }
  if (event == FL_RELEASE && Fl::event_button() == FL_LEFT_MOUSE)
  {
    moving_left = 0;
    return 1;
  }
  return 0;
}

MapGroup::MapGroup(int x, int y, int w, int h, const char* l)
    : Fl_Group{x, y, w, h, l}
{
  menu = new Fl_Menu_Item[7];
  menu[0] = Fl_Menu_Item{
      "add elem",           map_menu::noshortcut, map_menu::nocallback,
      map_menu::nouserdata, FL_SUBMENU,           map_menu::labeltype,
      map_menu::labelfont,  map_menu::labelsize,  map_menu::labelcolor};
  menu[1] = Fl_Menu_Item{"and",
                         map_menu::noshortcut,
                         add_elem<graph::And>,
                         this,
                         map_menu::noflag,
                         map_menu::labeltype,
                         map_menu::labelfont,
                         map_menu::labelsize,
                         map_menu::labelcolor};
  menu[2] = Fl_Menu_Item{"or",
                         map_menu::noshortcut,
                         add_elem<graph::Or>,
                         this,
                         map_menu::noflag,
                         map_menu::labeltype,
                         map_menu::labelfont,
                         map_menu::labelsize,
                         map_menu::labelcolor};
  menu[3] = Fl_Menu_Item{"not",
                         map_menu::noshortcut,
                         add_elem<graph::Buff>,
                         this,
                         map_menu::noflag,
                         map_menu::labeltype,
                         map_menu::labelfont,
                         map_menu::labelsize,
                         map_menu::labelcolor};
  menu[4] = Fl_Menu_Item{
      map_menu::endmenu,    map_menu::noshortcut, map_menu::nocallback,
      map_menu::nouserdata, map_menu::noflag,     map_menu::labeltype,
      map_menu::labelfont,  map_menu::labelsize,  map_menu::labelcolor};
  menu[5] = Fl_Menu_Item{"00",
                         map_menu::noshortcut,
                         add_elem<graph::And>,
                         this,
                         map_menu::noflag,
                         map_menu::labeltype,
                         map_menu::labelfont,
                         map_menu::labelsize,
                         map_menu::labelcolor};
  menu[6] = Fl_Menu_Item{
      map_menu::endmenu,    map_menu::noshortcut, map_menu::nocallback,
      map_menu::nouserdata, map_menu::noflag,     map_menu::labeltype,
      map_menu::labelfont,  map_menu::labelsize,  map_menu::labelcolor};

  Fl_Scroll* mama = (Fl_Scroll*)parent();
  x_min = 0;
  y_min = 0;
  x_max = w - mama->w() + mama->scrollbar.w();
  y_max = h - mama->h() + mama->hscrollbar.h();
  last_pused = nullptr;
}