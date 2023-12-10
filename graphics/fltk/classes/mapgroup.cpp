#include "mapgroup.h"

namespace graph {
namespace menu {
uchar noflag = 0;
uchar labeltype = FL_NORMAL_LABEL;
uchar labelfont = FL_HELVETICA;
uchar labelsize = FL_NORMAL_SIZE;
uchar labelcolor = FL_BLACK;
uchar noshortcut = FL_BLACK;
const char* endmenu = 0;
Fl_Callback* nocallback = nullptr;
void* nouserdata = nullptr;
};  // namespace menu
};  // namespace graph

int MapGroup::handle(int event)
{
  if (Fl_Group::handle(event))
    return 1;
  // if ((void*)this == (void*)(Fl::belowmouse()))
  {
    if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
    {
      auto temp = menu->popup(Fl::event_x(), Fl::event_y());
      if (temp && temp->callback())
        temp->do_callback(nullptr);
      return 1;
    }
    else if (event == FL_PUSH && Fl::event_button() == FL_LEFT_MOUSE)
    {
      Fl_Scroll* mama = (Fl_Scroll*)parent();
      moving_left = 1;
      x_ = Fl::event_x() + mama->xposition();
      y_ = Fl::event_y() + mama->yposition();
      return 1;
    }
    else if (event == FL_DRAG && moving_left &&
             Fl::event_button() == FL_LEFT_MOUSE)
    {
      Fl_Scroll* mama = (Fl_Scroll*)parent();

      mama->scroll_to(choise(x_min, x_ - Fl::event_x(), x_max),
                      choise(y_min, y_ - Fl::event_y(), y_max));

      // draw_children();
      return 1;
    }
    else if (event == FL_RELEASE && Fl::event_button() == FL_LEFT_MOUSE)
    {
      moving_left = 0;
      return 1;
    }
    else
      return Fl_Group::handle(event);
  }
  // else if (Fl::belowmouse() && (event == FL_PUSH || event == FL_RELEASE))
  // {
  //   last_pused = Fl::belowmouse();
  //   return last_pused->handle(event);
  // }
}

MapGroup::MapGroup(int x, int y, int w, int h, const char* l)
    : Fl_Group{x, y, w, h, l}
{
  menu = new Fl_Menu_Item[7];
  menu[0] = Fl_Menu_Item{"add elem",
                         graph::menu::noshortcut,
                         graph::menu::nocallback,
                         graph::menu::nouserdata,
                         FL_SUBMENU,
                         graph::menu::labeltype,
                         graph::menu::labelfont,
                         graph::menu::labelsize,
                         graph::menu::labelcolor};
  menu[1] = Fl_Menu_Item{"and",
                         graph::menu::noshortcut,
                         add_elem<graph::And>,
                         this,
                         graph::menu::noflag,
                         graph::menu::labeltype,
                         graph::menu::labelfont,
                         graph::menu::labelsize,
                         graph::menu::labelcolor};
  menu[2] = Fl_Menu_Item{"or",
                         graph::menu::noshortcut,
                         add_elem<graph::Or>,
                         this,
                         graph::menu::noflag,
                         graph::menu::labeltype,
                         graph::menu::labelfont,
                         graph::menu::labelsize,
                         graph::menu::labelcolor};
  menu[3] = Fl_Menu_Item{"not",
                         graph::menu::noshortcut,
                         add_elem<graph::Buff>,
                         this,
                         graph::menu::noflag,
                         graph::menu::labeltype,
                         graph::menu::labelfont,
                         graph::menu::labelsize,
                         graph::menu::labelcolor};
  menu[4] = Fl_Menu_Item{graph::menu::endmenu,    graph::menu::noshortcut,
                         graph::menu::nocallback, graph::menu::nouserdata,
                         graph::menu::noflag,     graph::menu::labeltype,
                         graph::menu::labelfont,  graph::menu::labelsize,
                         graph::menu::labelcolor};
  menu[5] = Fl_Menu_Item{"00",
                         graph::menu::noshortcut,
                         add_elem<graph::And>,
                         this,
                         graph::menu::noflag,
                         graph::menu::labeltype,
                         graph::menu::labelfont,
                         graph::menu::labelsize,
                         graph::menu::labelcolor};
  menu[6] = Fl_Menu_Item{graph::menu::endmenu,    graph::menu::noshortcut,
                         graph::menu::nocallback, graph::menu::nouserdata,
                         graph::menu::noflag,     graph::menu::labeltype,
                         graph::menu::labelfont,  graph::menu::labelsize,
                         graph::menu::labelcolor};

  // Fl_Menu_Item temp_menu[] = {{"add elem", 0, 0, 0, FL_SUBMENU},
  //                             {"and", 0, add_elem<graph::And>, this},
  //                             {"or", 0, add_elem<graph::Or>, this},
  //                             {"not", 0, add_elem<graph::Buff>, this},
  //                             {0},
  //                             {"00", 0, add_elem<graph::And>, this},
  //                             {0}};
  // menu = temp_menu;

  Fl_Scroll* mama = (Fl_Scroll*)parent();
  x_min = 0;
  y_min = 0;
  x_max = w - mama->w() + mama->scrollbar.w();
  y_max = h - mama->h() + mama->hscrollbar.h();
  last_pused = nullptr;
}