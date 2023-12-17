#ifndef LOGICWINDOW_H
#define LOGICWINDOW_H
#include "elemlist.h"
#include "fltk.h"
#include "logicmap.h"

class LogicWindow : public Fl_Window
{
  LogicMap* map;
  Fl_Menu_Bar* menu_bar;
  Fl_Box* map_box;
  Fl_Box* elems_box;
  Fl_Scroll* elems;

public:
  LogicWindow();
};

#endif