#include "mapgroup.h"

int MapGroup::handle(int event)
{
  if ((void*)this == (void*)(Fl::belowmouse()))
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

      return 1;
    }
    else if (event == FL_RELEASE && Fl::event_button() == FL_LEFT_MOUSE)
    {
      moving_left = 0;
      int temp = 1;
      return temp;
    }
    else
      return Fl_Group::handle(event);
  }
  else if (Fl::belowmouse() && (event == FL_PUSH || event == FL_RELEASE))
  {
    last_pused = Fl::belowmouse();
    return last_pused->handle(event);
  }
  return Fl_Group::handle(event);
}

MapGroup::MapGroup(int x, int y, int w, int h, const char* l)
    : Fl_Group{x, y, w, h, l}
{
  menu = new Fl_Menu_Item[7];
  menu[0] = Fl_Menu_Item{"add elem", 0, 0, 0, FL_SUBMENU};
  menu[1] = Fl_Menu_Item{"and", 0, add_elem<graph::And>, this};
  menu[2] = Fl_Menu_Item{"or", 0, add_elem<graph::Or>, this};
  menu[3] = Fl_Menu_Item{"not", 0, add_elem<graph::Not>, this};
  menu[4] = Fl_Menu_Item{0};
  menu[5] = Fl_Menu_Item{"00", 0, add_elem<graph::And>, this};
  menu[6] = Fl_Menu_Item{0};

  Fl_Scroll* mama = (Fl_Scroll*)parent();
  x_min = 0;
  y_min = 0;
  x_max = w - mama->w() + mama->scrollbar.w();
  y_max = h - mama->h() + mama->hscrollbar.h();
  last_pused = nullptr;
}