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
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace graph {
class And;
class Or;
class Buff;
class Element;
};  // namespace graph

enum class link_circle_types
{
  input = 0,
  output = 1
};

// класс кружочков связи
class LinkCircle : public Fl_Widget
{
private:
  link_circle_types type;
  bool is_entered = false;
  graph::Element* parent_elem;

public:
  static const int link_circle_radius{5};
  LinkCircle(int x = 0, int y = 0,
             link_circle_types t = link_circle_types::input,
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
  LinkCircle *start_circle, *end_circle;

public:
  Link(int x = 0, int y = 0, int w = 0, int h = 0, const char* l = 0);

  void draw () override;
};

// абстрактный класс для всех элементов
class graph::Element : public Fl_Widget
{
private:
  // logic::Value get_value () { return elem->get_value(); }

  logic::Value get_value () { return logic::Value::Undef; }

  bool is_entered = false;

  static void draw_Element (int, int, int, int, logic::Value) {}

  int elem_link_lenth{20};
  int line_thikness{2};

protected:
  logic::Element* elem;
  std::function<void(int, int, int, int, logic::Value)> draw_elem;
  std::vector<Link*> input_links{0};
  std::vector<Link*> output_links{0};
  LinkCircle *input_port, *output_port;
  bool inverted{0};
  int inputs_n{0}, outputs_n{0};

public:
  Element(int x = 50, int y = 50, int w = 50, int h = 50,
          const char* l = 0);

  // Element(Element&) = delete;

  void add_input_link (Link* link) { input_links.push_back(link); }

  void add_output_link (Link* link) { output_links.push_back(link); }

  int handle (int x) override;

  void draw () override;

  virtual void invert ();
};

// класс для элемента И
class graph::And : public graph::Element
{
public:
  And(int x, int y, int s = 50, int h = 0, const char* l = 0);
};

// класс для элемента НЕ
class graph::Buff : public Element
{
public:
  Buff(int x, int y, int fr_size, int h = 0, const char* l = 0);
};

// класс для элемента ИЛИ
class graph::Or : public Element
{
public:
  Or(int x, int y, int fr_size = 50, int h = 0, const char* l = 0);
};

void draw_and (int x, int y, int w, int h,
               logic::Value = logic::Value::False);

void draw_buff (int x, int y, int w, int h,
                logic::Value = logic::Value::False);

void draw_or (int x, int y, int w, int h,
              logic::Value = logic::Value::False);

#endif