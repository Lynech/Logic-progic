#ifndef LOGICWINDOW_H
#define LOGICWINDOW_H
#include "drawing_elems.h"
#include "elemlist.h"
#include "fltk.h"
#include "logicmap.h"

class LogicWindow : public Fl_Window
{
  Fl_Menu_Bar* menu_bar;
  Fl_Box* map_box;
  Fl_Box* elems_box;
  Fl_Scroll* elems;
  LogicMap* map;

public:
  LogicWindow();
};

#endif