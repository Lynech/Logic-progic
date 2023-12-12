#ifndef LOGICMAP_H
#define LOGICMAP_H

#include "fltk.h"

#include "logicmap.h"
#include "mapgroup.h"

class LogicMap : public Fl_Scroll
{
  MapGroup* map_group;

public:
  LogicMap(int x, int y, int w, int h, const char* l = 0);

  // int handle (int x) override;

  MapGroup* map () { return map_group; }
};
#endif