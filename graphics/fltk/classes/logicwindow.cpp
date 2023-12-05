#include "logicwindow.h"
#include "..\graph_elems\graph_elems.h"

LogicWindow::LogicWindow() : Fl_Window{50, 50, 900, 620, "LOGIC"}
{
  menu_bar = new Fl_Menu_Bar{0, 0, 900, 20};
  menu_bar->add("file");
  map_box = new Fl_Box{FL_BORDER_BOX, 5, 25, 690, 590, ""};

  map = new LogicMap{10, 30, 680, 580};
  std::string way = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
                    "Logic-progic/graphics/fltk/classes/sheme.txt";
  std::string way2 = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
                     "Logic-progic/graphics/fltk/classes/temp.txt";
  std::vector<DrawingElement*> data = read_file(way);
  for (DrawingElement* el : data)
  {
    if (el->get_name()[0] == 'a')
    {
      graph::And* temp{};
      map->add(temp);
    }
    else if (el->get_name()[0] == 'o')
    {
      graph::Or* temp{};
      map->add(temp);
    }
  }
  map->end();

  elems_box = new Fl_Box{FL_BORDER_BOX, 700, 25, 195, 590, ""};
  elems = new ElemList{705, 30, 185, 580, map->map()};
  /////////////////////////////////////////////////////////
  elems->end();
  color(FL_MAGENTA);
}