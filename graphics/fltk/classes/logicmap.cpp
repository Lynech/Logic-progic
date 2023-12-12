#include "logicmap.h"

LogicMap::LogicMap(int x, int y, int w, int h, const char* l)
    : Fl_Scroll{x, y, w, h, l}
{
  map_group = new MapGroup{x, y, 1000, 1000, ""};
  map_group->end();

  type(Fl_Scroll::BOTH_ALWAYS);
  color(FL_WHITE);
};

// int LogicMap::handle(int x)
// {
//   if (x == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
//   {
//     return map_group->handle(x);
//   }
//   else
//     return Fl_Scroll::handle(x);
// }