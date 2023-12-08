#ifndef ADD_ELEM_IMPL_H
#define ADD_ELEM_IMPL_H
#include "fltk.h"

template <class T> void add_elem (Fl_Widget*, void* userdata)
{
  MapGroup* map = (MapGroup*)userdata;
  LogicMap* mamamap = (LogicMap*)map->parent();

  if ((Fl::event_x() > mamamap->x() &&
       Fl::event_x() <
           (mamamap->x() + mamamap->w() - mamamap->scrollbar.w())) &&
      (Fl::event_y() > mamamap->y() &&
       Fl::event_y() <
           (mamamap->y() + mamamap->h() - mamamap->hscrollbar.h())))
  {
    T* temp = new T{Fl::event_x(), Fl::event_y(), 50, 50};
    map->add(temp);
    map->redraw();
  }
}

#endif