#ifndef MAPGROUP_H
#define MAPGROUP_H

#include "fltk.h"

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

class MapGroup : public Fl_Group
{
  Fl_Menu_Item* menu;
  bool moving_left = 0;
  int x_, y_, x_max, y_max, x_min, y_min;
  Fl_Widget* last_pused;

public:
  MapGroup(int x, int y, int w, int h, const char* l = 0);

  int handle (int event) override;
};

#endif