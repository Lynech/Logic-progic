#include "fltk.h"

// class MyDot : public Fl_Widget
// {
// public:
//   MyDot(int x, int y, int w = 0, int h = 0, const char* l = 0)
//       : Fl_Widget{x, y, w, h}
//   {
//   }

//   void draw () override { fl_rectf(x(), y(), 50, 50, FL_BLACK); }
// };

int main (int argc, char** argv)
{
  LogicWindow* window = new LogicWindow{};
  // Fl_Window* window = new Fl_Window{50, 50, 600, 600};
  // new MyDot{50, 50, 7, 7};
  window->end();
  window->show(argc, argv);
  return Fl::run();
}