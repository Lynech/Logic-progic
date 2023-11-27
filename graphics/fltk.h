#ifndef MY_FLTK_H
#define MY_FLTH_H
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <iostream>

class MyBox : public Fl_Box
{
public:
  MyBox(int x, int y, int w, int h, const char* l)
      : Fl_Box{FL_DOWN_BOX, x, y, w, h, l} {};

  int handle (int x) override;
};

void add_butt (Fl_Widget*, void* v);

void add_butt2 (Fl_Widget*, void* v);

class LogicMap : public Fl_Scroll
{
  Fl_Menu_Item* menu;

public:
  LogicMap(int x, int y, int w, int h, const char* l = 0);

  int handle (int x) override;
};

class LogicBox : Fl_Box
{
public:
  LogicBox(int x, int y, int w, int h, const char* l = 0)
      : Fl_Box{x, y, w, h, l} {

        };
};

class LogicWindow : public Fl_Window
{
  Fl_Menu_Bar* menu_bar;
  Fl_Box* map_box;
  Fl_Box* elems_box;
  Fl_Scroll* elems;
  LogicMap* map;

public:
  LogicWindow() : Fl_Window{50, 50, 900, 620, "LOGIC"}
  {
    menu_bar = new Fl_Menu_Bar{0, 0, 900, 20};
    menu_bar->add("file");
    map_box = new Fl_Box{FL_BORDER_BOX, 5, 25, 690, 590, ""};
    map = new LogicMap{10, 30, 680, 580};
    new Fl_Group{10, 30, 1000, 1000, ""};
    map->end();
    elems_box = new Fl_Box{FL_BORDER_BOX, 700, 25, 195, 590, ""};

    elems = new Fl_Scroll{705, 30, 185, 580};
    elems->color(FL_GREEN);
    // Fl_Box*and = new Fl_Box{};
    elems->end();
    elems->type(Fl_Scroll::VERTICAL_ALWAYS);
    color(FL_MAGENTA);
  }
};

#endif