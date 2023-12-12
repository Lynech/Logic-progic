#include "fltk.h"

int choise (int a, int b, int c)
{
  if (b > c)
    return c;
  if (b < a)
    return a;
  return b;
}

void add_butt (Fl_Widget*, void* v)
{
  Fl_Scroll* t = (Fl_Scroll*)v;
  t->begin();
  new Fl_Light_Button(Fl::event_x(), Fl::event_y(), 100, 20, "jessey");
  t->end();
  t->redraw();
}

void add_butt2 (Fl_Widget*, void* v)
{
  Fl_Scroll* t = (Fl_Scroll*)v;
  t->begin();
  new Fl_Button(Fl::event_x(), Fl::event_y(), 100, 20, "heisenberg");
  t->end();
  t->redraw();
}
