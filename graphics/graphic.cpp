#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "fltk.h"
#include <cmath>

// int main (int argc, char** argv)
// {
//   Fl_Window* window = new Fl_Window(50, 50, 600, 600);
//   // window->color(FL_RED);
//   new Not{200, 200};
//   new And{100, 100};
//   new Or{300, 300};
//   window->color(FL_BLACK);
//   window->end();
//   window->show(argc, argv);
//   return Fl::run();
// }

int main (int argc, char** argv)
{

  LogicWindow* window = new LogicWindow{};
  // new Not{200, 200};
  // new And{100, 100};
  // new Or{300, 300};
  window->color(FL_BLACK);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}

// int main (int argc, char** argv)
// {
//   Fl_Window* window = new Fl_Window(50, 50, 600, 600);
//   Fl_Counter* counter = new Fl_Counter(20, 160, 300, 40, "LOL shadow");
//   counter->labeltype(FL_SHADOW_LABEL);
//   MyBox* box = new MyBox(20, 40, 300, 100, "Hello, World!");
//   box->labelfont(FL_BOLD + FL_ITALIC);
//   box->labelsize(36);
//   box->labeltype(FL_SHADOW_LABEL);
//   LogicMap* map = new LogicMap(20, 400, 300, 180);
//   map->end();
//   Fl_Menu_Bar* menu = new Fl_Menu_Bar(0, 0, 600, 20);
//   menu->add("string", 0, nullptr);
//   Fl_Scroll* elements = new Fl_Scroll(400, 30, 180, 380);
//   elements->type(Fl_Scroll::VERTICAL_ALWAYS);
//   elements->begin();
//   new Fl_Light_Button(410, 40, 100, 20, "lol");
//   new Fl_Light_Button(600, 600, 100, 20, "ыыыы");
//   elements->end();
//   window->end();
//   window->show(argc, argv);
//   return Fl::run();
// }
/*

int main (int argc, char** argv)
{
  LogicWindow* window = new LogicWindow{};
  window->end();
  window->show(argc, argv);
  return Fl::run();
}