#include "fltk.h"
#include "logicwindow.h"
#include <FL/Fl_File_Chooser.H>

int main (int argc, char** argv)
{
  LogicWindow* window = new LogicWindow{};
  window->end();
  window->show(argc, argv);
  return Fl::run();
}