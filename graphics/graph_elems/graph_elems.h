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

const int link_circle_radius = 5;
const int elem_link_lenth = 20;

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

enum class link_circles
{
  input = 1,
  output = 2
};

class LinkCircle : public Fl_Widget
{
private:
  int x, y;
  // link_circles link_type;
  bool is_entered = false;

public:
  LinkCircle(int xx = 0, int yy = 0, int w = 0, int h = 0,
             const char* l = 0)
      : Fl_Widget{xx - link_circle_radius, yy - link_circle_radius,
                  link_circle_radius * 2, link_circle_radius * 2, l}
  {
    x = xx;
    y = yy;
  }

  void draw () override
  {
    fl_color(16);
    fl_begin_polygon();
    fl_circle(x, y, link_circle_radius);
    fl_end_polygon();

    if (is_entered == true)
    {
      fl_color(FL_BLACK);
    }
    else
    {
      fl_color(16);
    }
    fl_line_style(0, 4);
    fl_begin_loop();
    fl_circle(x, y, link_circle_radius);
    fl_end_loop();
  }

  int handle (int x) override
  {
    switch (x)
    {
    case FL_ENTER:
      is_entered = true;
      redraw();
      return 1;
    case FL_LEAVE:
      is_entered = false;
      redraw();
      return 1;
    default:
      return Fl_Widget::handle(x);
    }
  }
};

// класс для элемента И
class graph::And : public Fl_Widget

{
private:
  int size = 50;
  bool is_entered = false;
  Point p1, p2, p3, p4, p_center, p_frame, p_input_link, p_output_link;
  LinkCircle *input_link, *output_link;

public:
  And(int x, int y, int s = 50, int h = 0, const char* l = 0);

  void draw () override;

  int handle (int x) override;
};

// класс для элемента НЕ
class graph::Not : public Fl_Widget
{
private:
  int size = 50;
  Point p1, p2, p3, p_frame, p_input_link, p_output_link;
  bool is_entered = false;
  LinkCircle *input_link, *output_link;

public:
  Not(int x, int y, int fr_size, int h = 0, const char* l = 0);

  int get_size () { return size; }

  void draw () override;

  int handle (int x) override;
};

// класс для элемента ИЛИ
class graph::Or : public Fl_Widget
{
private:
  int size = 50;
  bool is_entered = false;
  Point p_ellipse, p_circle, p_frame, p_input_link, p_output_link;
  LinkCircle *input_link, *output_link;

public:
  Or(int x, int y, int fr_size = 50, int h = 0, const char* l = 0);

  void draw () override;

  int handle (int x) override;
};
#endif