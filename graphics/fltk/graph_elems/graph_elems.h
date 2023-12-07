#ifndef GRAPH_ELEMS_H
#define GRAPH_ELEMS_H
#include "fltk.h"
#include "logic_elems/logic_elems.h"
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
class Buff;
class Element;
};  // namespace graph

const int link_circle_radius = 5;
const int elem_link_lenth = 20;
enum class link_circle_types
{
  input = 0,
  output = 1
};

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

// класс кружочков связи
class LinkCircle : public Fl_Widget
{
private:
  Point p_center;
  link_circle_types type;
  bool is_entered = false;
  graph::Element* parent_elem;

public:
  LinkCircle(int xx = 0, int yy = 0,
             link_circle_types t = link_circle_types::input, int h = 0,
             const char* l = 0);

  void draw () override;
  int handle (int event) override;

  void set_parent_elem (graph::Element* e) { parent_elem = e; }

  graph::Element* get_parent_elem () { return parent_elem; }

  link_circle_types get_type () { return type; }
};

// класс связи
class Link : public Fl_Widget
{
private:
  Point p_start, p_end;
  LinkCircle *start_circle, *end_circle;

public:
  Link(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, const char* l = 0);

  void draw () override;
};

// абстрактный класс для всех элементов
class graph::Element : public Fl_Widget
{
private:
  std::vector<Link*> input_links{0};
  std::vector<Link*> output_links{0};

protected:
  LinkCircle *input_port, *output_port;

public:
  Element(int x = 0, int y = 0, int s = 50, int h = 0, const char* l = 0)
      : Fl_Widget{x - 5, y - 5, s + 10, s + 10, l}
  {
    // input_links = {0};
    // output_links = {0};
  }

  // virtual void print () = 0;

  void add_input_link (Link* link) { input_links.push_back(link); }

  void add_output_link (Link* link) { output_links.push_back(link); }
};

// класс для элемента И
class graph::And : public graph::Element

{
private:
  int size = 50;
  bool is_entered = false;
  Point p1, p2, p3, p4, p_center, p_frame, p_input_port, p_output_port;
  logic::And* logic_and;
  // std::vector<Link*> input_links;
  // std::vector<Link*> output_links;

public:
  And(int x, int y, int s = 50, int h = 0, const char* l = 0);

  void draw () override;

  int handle (int x) override;
};

// класс для элемента НЕ
class graph::Buff : public Element
{
private:
  int size = 50;
  Point p1, p2, p3, p_frame, p_input_port, p_output_port;
  bool is_entered = false;
  logic::Buff* logic_buff;

public:
  Buff(int x, int y, int fr_size, int h = 0, const char* l = 0);

  int get_size () { return size; }

  void draw () override;

  int handle (int x) override;
};

// класс для элемента ИЛИ
class graph::Or : public Element
{
private:
  int size = 50;
  bool is_entered = false;
  Point p_ellipse, p_circle, p_frame, p_input_port, p_output_port;
  logic::Or* logic_or;

public:
  Or(int x, int y, int fr_size = 50, int h = 0, const char* l = 0);

  void draw () override;

  int handle (int x) override;
};
#endif