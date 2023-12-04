#ifndef MY_FLTK_H
#define MY_FLTH_H
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <iostream>

// #include "logicmap.h"
// #include "logicwindow.h"
// #include "mapgroup.h"

int choise (int a, int b, int c);

void add_butt (Fl_Widget*, void*);

void add_butt2 (Fl_Widget*, void*);

template <class T> void add_elem (Fl_Widget*, void*);

// void resize_mapgroup (Fl_Widget*, void*);

class MapGroup : public Fl_Group
{
  Fl_Menu_Item* menu;
  bool moving_left = 0;
  int x_, y_, x_max, y_max, x_min, y_min;
  Fl_Widget* last_pused;

public:
  MapGroup(int x, int y, int w, int h, const char* l = 0);

  int handle (int event) override;
};

class LogicMap : public Fl_Scroll
{
  MapGroup* map_group;

public:
  LogicMap(int x, int y, int w, int h, const char* l = 0);

  int handle (int x) override;

  MapGroup* map () { return map_group; }
};

class ElemList : public Fl_Scroll
{
  MapGroup* mapgroup;
  Fl_Group* ElemGroup;
  int gap_y, gap_x, button_w, button_h;

public:
  ElemList(int x, int y, int w, int h, MapGroup* mapgroup);

  MapGroup* map () { return mapgroup; }
};

template <class T> class CreateButton : public Fl_Button
{
public:
  CreateButton(int x, int y, int w, int h, const char* l = /*T::type*/ 0)
      : Fl_Button{x, y, w, h, l}
  {
  }  // надо сделать поле type с названием типа

  int handle (int event);
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
    map->end();

    elems_box = new Fl_Box{FL_BORDER_BOX, 700, 25, 195, 590, ""};
    elems = new ElemList{705, 30, 185, 580, map->map()};
    new graph::Not{elems_x + (elems_w - size) / 2, elems_y + 30, size};
    new graph::And{elems_x + (elems_w - size) / 2, elems_y + 30 * 2 + size,
                   size};
    new graph::Or{elems_x + (elems_w - size) / 2,
                  elems_y + 30 * 3 + 2 * size, size};
    elems->end();
    color(FL_MAGENTA);
  }
};

#endif
