#ifndef ELEMLIST_H
#define ELEMLIST_H

#include "createbutton.h"
#include "fltk.h"
#include "mapgroup.h"

class ElemList : public Fl_Scroll
{
  MapGroup* mapgroup;
  Fl_Group* ElemGroup;
  int gap_y, gap_x, button_w, button_h;

public:
  ElemList(int x, int y, int w, int h, MapGroup* mapgroup);

  MapGroup* map () { return mapgroup; }

  ~ElemList();
};

#endif