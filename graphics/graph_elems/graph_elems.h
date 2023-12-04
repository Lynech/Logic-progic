#ifndef GRAPH_ELEMS_H
#define GRAPH_ELEMS_H
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
#include <FL/fl_draw.H>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace graph {
class And;
class Or;
class Not;
};  // namespace graph

// класс для точки
class Point
{
private:
  int xx;
  int yy;

public:
  Point(int xxx = 0, int yyy = 0)
  {
    xx = xxx;
    yy = yyy;
  }

  int x () { return xx; }

  int y () { return yy; }

  void set_x (int xxx) { xx = xxx; }

  void set_y (int yyy) { yy = yyy; }
};

// класс для элемента И
class graph::And : public Fl_Widget
{
private:
  int size = 50;
  bool is_entered = false;
  Point p1, p2, p3, p4, p_center, p_frame;

public:
  And(int x, int y, int s = 50, int h = 0, const char* l = 0);

  void draw () override;

  int handle (int x) override;
};

// класс для элемента НЕ
class graph::Not : public Fl_Widget
{
private:
  int frame_size = 50;
  Point p1, p2, p3, p_frame;
  bool is_entered = false;

public:
  Not(int x, int y, int fr_size, int h = 0, const char* l = 0);

  int get_size () { return frame_size; }

  void draw () override;

  int handle (int x) override;
};

// класс для элемента ИЛИ
class graph::Or : public Fl_Widget
{
private:
  int frame_size = 50;
  bool is_entered = false;
  Point p_ellipse, p_circle, p_frame;

public:
  Or(int x, int y, int fr_size = 50, int h = 0, const char* l = 0);

  void draw () override;

  int handle (int x) override;
};
#endif