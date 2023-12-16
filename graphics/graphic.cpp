#include "fltk.h"
#include "logicwindow.h"

int main (int argc, char** argv)
{
  LogicWindow* window = new LogicWindow{};
  window->end();
  window->show(argc, argv);
  return Fl::run();
}