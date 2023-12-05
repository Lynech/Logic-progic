#ifndef CREATEBUTTON_H
#define CREATEBUTTON_H
#include "fltk.h"

template <class T> class CreateButton : public Fl_Button
{
public:
  CreateButton(int x, int y, int w, int h, const char* l = /*T::type*/ 0)
      : Fl_Button{x, y, w, h, l}
  {
  }  // надо сделать поле type с названием типа

  int handle (int event)
  {
    if (event == FL_RELEASE)
    {
      Fl_Window* map = (Fl_Window*)(parent()->parent()->parent());
      int n = map->children();
      LogicMap* scroll = nullptr;
      for (int i = 0; i < n && !scroll; i++)
        scroll = dynamic_cast<LogicMap*>(map->child(i));
      MapGroup* group = nullptr;
      if (scroll)
      {
        n = scroll->children();
        for (int i = 0; i < n && !group; i++)
          group = dynamic_cast<MapGroup*>(scroll->child(i));
      }
      if (group)
        add_elem<T>(nullptr, group);
      return Fl_Button::handle(event);
    }
    if (event == FL_DRAG)
      return 1;
    return Fl_Button::handle(event);
  }
};
#endif