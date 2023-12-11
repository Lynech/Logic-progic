#include "logicwindow.h"
#include "..\graph_elems\graph_elems.h"
#include "drawing_elems.h"

Fl_File_Chooser* file_choose;

void open_cb (Fl_Widget*, void*)
{
  file_choose->show();
  while (file_choose->shown())
    Fl::wait();
  if (file_choose->count() == 1)
  {
    std::string file_name = file_choose->value();
    std::vector<DrawingElement*> sheme = read_file(file_name);
  }
}

Fl_Menu_Item MenuEng[] = {{"&File", 0, 0, 0, FL_SUBMENU},
                          {"&Open", FL_CTRL + 'o', (Fl_Callback*)open_cb},
                          {"&Save", FL_CTRL + 's', 0},
                          {"&Delete", FL_CTRL + 'd', 0},
                          {0}};

LogicWindow::LogicWindow() : Fl_Window{50, 50, 900, 620, "LOGIC"}
{
  menu_bar = new Fl_Menu_Bar{0, 0, 900, 20};

  menu_bar->copy(MenuEng);

  file_choose = new Fl_File_Chooser(".", "*.{txt}", Fl_File_Chooser::SINGLE,
                                    "File_Chooser_Dialog");

  map_box = new Fl_Box{FL_BORDER_BOX, 5, 25, 690, 590, ""};

  map = new LogicMap{10, 30, 680, 580};
  map->end();

  elems_box = new Fl_Box{FL_BORDER_BOX, 700, 25, 195, 590, ""};
  elems = new ElemList{705, 30, 185, 580, map->map()};
  /////////////////////////////////////////////////////////
  elems->end();
  color(FL_MAGENTA);
}