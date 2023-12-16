#include "logicwindow.h"

LogicWindow::LogicWindow() : Fl_Window{50, 50, 900, 620, "LOGIC"}
{
  menu_bar = new Fl_Menu_Bar{0, 0, 900, 20};
  menu_bar->add("file");
  map_box = new Fl_Box{FL_BORDER_BOX, 5, 25, 690, 590, ""};

  map = new LogicMap{10, 30, 680, 580};
  map->end();

  elems_box = new Fl_Box{FL_BORDER_BOX, 700, 25, 195, 590, ""};
  elems = new ElemList{705, 30, 185, 580, map->map()};
  elems->end();
  color(FL_MAGENTA);
  resizable(map_box);
}

LogicWindow::~LogicWindow()
{
  delete menu_bar;
  delete map_box;
  delete map;
  delete elems;
}