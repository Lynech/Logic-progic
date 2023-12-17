#ifndef MAPGROUP_H
#define MAPGROUP_H

#include "fltk.h"
#include "graph_elem.h"
#include "graph_elems.h"
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

  graph::Element* add_el (TypeElement what_el, bool inverted, int x, int y);
};

#endif