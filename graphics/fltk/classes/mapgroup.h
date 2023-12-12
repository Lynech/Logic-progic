#ifndef MAPGROUP_H
#define MAPGROUP_H

#include "fltk.h"
#include "type_elem.h"

class MapGroup : public Fl_Group
{
  Fl_Menu_Item* menu;
  bool moving_left = 0;
  int x_, y_, x_max, y_max, x_min, y_min;
  Fl_Widget* last_pused;

public:
  MapGroup(int x, int y, int w, int h, const char* l = 0);

  int handle (int event) override;

  void add_el (TypeElement what_el, int x, int y);
};

#endif