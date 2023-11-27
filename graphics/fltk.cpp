#include "fltk.h"

int MyBox::handle(int x)
{
  switch (x)
  {
  case FL_ENTER:
    labelcolor(FL_MAGENTA);
    redraw();
    return 1;
  case FL_LEAVE:
    labelcolor(FL_BLACK);
    redraw();
    return 1;
  default:
    return Fl_Box::handle(x);
  }
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
  new Fl_Light_Button(Fl::event_x(), Fl::event_y(), 100, 20, "heisenberg");
  t->end();
  t->redraw();
}

LogicMap::LogicMap(int x, int y, int w, int h, const char* l)
    : Fl_Scroll{x, y, w, h, l}
{
  menu = new Fl_Menu_Item[3];
  menu[0] = Fl_Menu_Item{"jessi button", 0, add_butt, this, 0};
  menu[1] = Fl_Menu_Item{"heisenberg button", 0, add_butt2, this, 0};
  menu[2] = Fl_Menu_Item{0};
  type(Fl_Scroll::BOTH_ALWAYS);
  new Fl_Light_Button(10, 30, 100, 20, "хихихыха");
  color(FL_BLACK);
};

int LogicMap::handle(int x)
{
  if (x == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
  {
    auto temp = menu->popup(Fl::event_x(), Fl::event_y());
    if (temp && temp->callback())
      temp->do_callback(nullptr);
    return 1;
  }
  else
    return Fl_Scroll::handle(x);
}