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
class Src0;
class Src1;
};  // namespace graph

#include "fltk.h"
#include "graph_elems.h"
#include <vector>

enum class port_types
{
  input = 0,
  output = 1
};
class Link;

// класс кружочков связи
class Port : public Fl_Widget
{
private:
  port_types type;
  std::vector<Link*> links{};
  Fl_Menu_Item* menu;

  bool is_entered = false;

public:
  Port(int x, int y, int w, int h, port_types t, const char* l = 0);

  void draw () override;
  int handle (int event) override;

  // TODO добавить метод change inverted
  bool inverted = false;

  // TODO ;  /// добавить изменения в draw() у Elem

  port_types get_type () { return type; }

  std::vector<Link*> get_links () { return links; }

  void add_link (Link* l) { links.push_back(l); }

  void delete_link_by_index (int i);
};

// ports callbacks
void invert_port (Fl_Widget*, void* userdata);
void delete_through_port (Fl_Widget*, void* userdata);

// elems callbacks
void invert_elem (Fl_Widget*, void* userdata);
void delete_elem (Fl_Widget*, void* userdata);
void delete_all_elem_links (Fl_Widget*, void* userdata);

// доделать
// класс связи
// class Element;
class Link : public Fl_Widget
{
private:
  Port *input_port, *output_port;

public:
  Link(Port* c1, Port* c2);

  void draw () override;
  void delete_link ();

  Port* get_input_port () { return input_port; }

  Port* get_output_port () { return output_port; }
};

class Label : public Fl_Widget
{
protected:
  logic::Value value{logic::Value::Undef};
  bool is_entered = false;
  Fl_Menu_Item* menu{nullptr};

public:
  logic::Element* logic_elem;

  Label(
      int x, int y, int w, int h, const char* l = 0,
      std::function<void(int, int, int, int, logic::Value)> Label_draw = 0);

  std::function<void(int, int, int, int, logic::Value)> Label_draw_;

  void draw () override;

  void set_value (logic::Value value_) { value = value_; }

  int handle (int event) override;

  void delete_all_links ();
  // LinkCircle* get_start_circle {return start_circle;}

  // LinkCircle* get_end_circle {return end_circle;}
};

// абстрактный класс для всех элементов
class graph::Element : public Fl_Group
{
private:
  // logic::Value get_value () { return elem->get_value(); }

  logic::Value get_value () { return logic::Value::Undef; }

  void set_value (logic::Value val) { draw_elem->set_value(val); }

  int elem_link_lenth{20};
  int line_thikness{2};

protected:
  // // убрать input_links output_links
  // std::vector<Link*> input_links{0};
  // std::vector<Link*> output_links{0};

  // единственный выход:
  Port* output_port;
  // мно-во входов
  std::vector<Port*> input_ports;

  // фигурка
  Label* draw_elem;
  int inputs_n{-1}, outputs_n{0};
  Fl_Menu_Item* menu{nullptr};

public:
  Label* get_draw_elem () { return draw_elem; }

  void set_lable (
      std::function<void(int, int, int, int, logic::Value)> label_draw)
  {
    draw_elem->Label_draw_ = label_draw;
  }

  Element(int x = 50, int y = 50, int w = 50, int h = 50,
          const char* l = 0);

  // Element(Element&) = delete;

  // void add_input_link (Link* link) { input_links.push_back(link); }

  // void add_output_link (Link* link) { output_links.push_back(link); }

  void add_input_port ();

  int handle (int x) override;

  void draw () override;

  void delete_port (Port* l_c);

  // void resize(int x, int y, int w, int h) override
  // {

  //   draw_elem->resize(x+2*w/9, y, w/9*5, h);
  //   redraw();
  // }
  std::vector<Port*> get_input_ports () { return input_ports; }

  Port* get_output_port () { return output_port; }

  virtual void invert ();
};

// класс для элемента Source
class graph::Src0 : public graph::Element
{
public:
  Src0(int x, int y, int s = 50, int h = 0, const char* l = 0);
};

// класс для элемента Source
class graph::Src1 : public graph::Element
{
public:
  Src1(int x, int y, int s = 50, int h = 0, const char* l = 0);
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
void draw_src0 (int x, int y, int w, int h, logic::Value value);
void draw_src1 (int x, int y, int w, int h, logic::Value value);

#endif