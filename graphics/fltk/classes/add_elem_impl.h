#ifndef ADD_ELEM_IMPL_H
#define ADD_ELEM_IMPL_H
#include "fltk.h"
#include "type_elem.h"

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
    // map->begin();
    auto temp = new T{Fl::event_x(), Fl::event_y(), 70, 70};
    map->add(temp);
    // map->end();
    map->redraw();
  }
}

template <class T> T* add_elem_from_file (void* userdata, int xx, int yy)
{
  MapGroup* map = (MapGroup*)userdata;
  LogicMap* mamamap = (LogicMap*)map->parent();

  map->begin();
  T* temp = new T{xx, yy, 70, 70};

  map->end();
  map->redraw();
  return temp;
}

#endif