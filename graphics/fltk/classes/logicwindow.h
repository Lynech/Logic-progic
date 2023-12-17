#ifndef LOGICWINDOW_H
#define LOGICWINDOW_H
#include "elemlist.h"
#include "fltk.h"
#include "logicmap.h"
#include <FL/Fl_File_Chooser.H>

class LogicWindow : public Fl_Window
{
  LogicMap* map;
  Fl_Menu_Bar* menu_bar;
  Fl_Box* map_box;
  Fl_Box* elems_box;
  Fl_Scroll* elems;
  Fl_File_Chooser* file_choose;

public:
  LogicMap* get_map () { return map; }

  Fl_File_Chooser* get_file_choose () { return file_choose; }

  LogicWindow();
};

#endif