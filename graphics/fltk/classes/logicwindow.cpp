#include "logicwindow.h"
#include "add_elem_impl.h"
#include "createbutton.h"
#include "graph_elems.h"
#include "mapgroup.h"

// LogicMap* map_ptr = nullptr;

void open_cb (Fl_Widget*, void* window)
{
  LogicWindow* window_ptr = (LogicWindow*)window;
  LogicMap* map_ptr = (LogicMap*)window_ptr->get_map();
  Fl_File_Chooser* file_choose = window_ptr->get_file_choose();
  file_choose->show();
  while (file_choose->shown())
    Fl::wait();
  if (file_choose->count() == 1)
  {
    std::string file_name = file_choose->value();
    clear_map(nullptr, map_ptr->map());
    read_file(file_name, map_ptr);
  }
}

void write_cb (Fl_Widget*, void* window)
{
  LogicWindow* window_ptr = (LogicWindow*)window;
  LogicMap* map_ptr = (LogicMap*)window_ptr->get_map();
  Fl_File_Chooser* file_choose = window_ptr->get_file_choose();
  file_choose->show();
  while (file_choose->shown())
    Fl::wait();
  if (file_choose->count() == 1)
  {
    std::string file_name = file_choose->value();
    write_file(file_name, map_ptr);
  }
}

LogicWindow::LogicWindow() : Fl_Window{50, 50, 900, 620, "LOGIC"}
{
  menu_bar = new Fl_Menu_Bar{0, 0, 900, 20};

  file_choose = new Fl_File_Chooser(".", "*.{txt}", Fl_File_Chooser::SINGLE,
                                    "File_Chooser_Dialog");

  map_box = new Fl_Box{FL_BORDER_BOX, 5, 25, 690, 590, ""};

  map = new LogicMap{10, 30, 680, 580};

  map->end();

  elems_box = new Fl_Box{FL_BORDER_BOX, 700, 25, 195, 590, ""};

  elems = new ElemList{705, 30, 185, 580, map->map()};

  menu_bar->add("&Open", FL_CTRL + 'o', (Fl_Callback*)open_cb, this);
  menu_bar->add("&Save as", FL_CTRL + 's', (Fl_Callback*)write_cb, this);
  menu_bar->add("&Delete", 0, (Fl_Callback*)clear_map, map->map());
  resizable(map_box);
  elems->end();
  color(FL_MAGENTA);
}
