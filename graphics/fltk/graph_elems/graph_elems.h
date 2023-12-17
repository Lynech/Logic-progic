#ifndef GRAPH_ELEMS_H
#define GRAPH_ELEMS_H
#include "fltk.h"
#include "logic_elems.h"
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

#include "fltk.h"
#include "graph_elem.h"
#include "graph_elems.h"
#include "graph_label.h"
#include "graph_link.h"
#include "graph_port.h"
#include <vector>

namespace graph {
class And;
class Or;
class Buff;
class Element;
class Src0;
class Src1;
};  // namespace graph

namespace port_menu {
constexpr uchar noflag = 0;
constexpr uchar labeltype = FL_NORMAL_LABEL;
constexpr uchar labelfont = FL_HELVETICA;
const uchar labelsize = FL_NORMAL_SIZE;
constexpr uchar labelcolor = FL_BLACK;
constexpr uchar noshortcut = 0;
constexpr char* endmenu = 0;
constexpr Fl_Callback* nocallback = nullptr;
constexpr void* nouserdata = nullptr;
};  // namespace port_menu

bool add_input (graph::Element* inputgoeshere, graph::Element* fromhere);

bool add_inverted_input (graph::Element* inputgoeshere,
                         graph::Element* fromhere);

// enum class port_types
// {
//   input = 0,
//   output = 1
// };
// class Link;

// //// Все что связано с классом #Port vvvvvvvvvvvvvvvvvvvvvvvvv
// // класс кружочков связи
// class Port : public Fl_Widget
// {
// private:
//   port_types type;           //
//   std::vector<Link*> links;  //
//   Fl_Menu_Item* menu;

//   bool is_entered = false;

//   bool inverted = false;

// public:
//   Port(int x, int y, int w, int h, port_types t, const char* l = 0);

//   void draw () override;

//   int handle (int event) override;

//   port_types get_type () { return type; }  //

//   std::vector<Link*> get_links () { return links; }  //

//   void add_link (Link* l) { links.push_back(l); }  //

//   void delete_link_by_index (int i);  //

//   int release_handle ();  //

//   Port* find_port ();  //

//   bool linked ();  //

//   void invert () { inverted = !inverted; }

//   bool is_inverted () { return inverted; }
// };

// ports callbacks
void invert_port (Fl_Widget*, void* userdata);
void delete_through_port (Fl_Widget*, void* userdata);

// // --------------------------------------------------------------
// // class InputPort : public Port
// // {
// // private:
// //   Link* link;

// // public:
// //   InputPort(int x, int y, int w, int h, const char* l = 0);

// //   Link* get_link () { return link; }

// //   void set_link (Link* l) { link = l; }

// //   void delete_link ();
// // };

// // class OutportPort : public Port
// // {
// // private:
// //   std::vector<Link*> links;

// // public:
// //   OutportPort(int x, int y, int w, int h, const char* l = 0);

// //   std::vector<Link*> get_links () { return links; }

// //   void push_link (Link* l) { links.push_back(l); }

// //   void delete_link_by_index (int i);
// // };

// void invert_output_port (Fl_Widget*, void* userdata);
// void delete_output_linkS (Fl_Widget*, void* userdata);

// void delete_input_link (Fl_Widget*, void* userdata);
// void delete_input_port (Fl_Widget*, void* userdata);
// void invert_input_port (Fl_Widget*, void* userdata);

// //// Все что связано с классом ##Port ^^^^^^^^^^^^^^^^^^^^^^^^^

// //// Все что связано с классом #Link vvvvvvvvvvvvvvvvvvvvvvvvv
// // доделать -- нияз: что доделать?
// // класс связи
void delete_link (Fl_Widget* w, void* userdata);
void delete_input_port (Fl_Widget* w, void* userdata);

// class Link : public Fl_Widget
// {
// private:
//   Port *input_port, *output_port;

// public:
//   Link(Port* c1, Port* c2);

//   void draw () override;
//   void delete_link ();
//   void delete_link_input_port ();

//   Port* get_input_port () { return input_port; }

//   Port* get_output_port () { return output_port; }

//   // logic::Element* get_output_element () {return...
//   // ...output_port->parent()->get_draw_elem()->logic_elem} типа того
// };

// //// Все что связано с классом ##Link ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// //// Все что связано с классом #Label vvvvvvvvvvvvvvvvvvvvvvvvv
// // Класс фигурки для отрисовки (содержит логику)
// class Label : public Fl_Widget
// {
// protected:
//   // logic::Value value{logic::Value::Undef};
//   bool is_entered = false;
//   Fl_Menu_Item* menu{nullptr};

// public:
//   logic::Element* logic_elem;

//   Label(
//       int x, int y, int w, int h, const char* l = 0,
//       std::function<void(int, int, int, int, logic::Value)> Label_draw =
//       0);

//   std::function<void(int, int, int, int, logic::Value)> Label_draw_;

//   void draw () override;

//   // void set_value (logic::Value value_) { value = value_; }

//   int handle (int event) override;

//   void delete_all_links ();

//   // TODO: удалить:
//   // LinkCircle* get_start_circle {return start_circle;}

//   // LinkCircle* get_end_circle {return end_circle;}
// };

// //// Все что связано с классом #Label ^^^^^^^^^^^^^^^^^^^^^^^^^^

// //// Все что связано с классом #Element vvvvvvvvvvvvvvvvvvvvvvvvv
// // абстрактный класс для всех элементов (графическая часть логики)
// class graph::Element : public Fl_Group
// {
// private:
//   // TODO удалить:
//   // void set_value (logic::Value val);

//   int elem_link_lenth{20};
//   int line_thikness{2};

// protected:
//   // единственный выход:
//   Port* output_port;
//   // мно-во входов
//   std::vector<Port*> input_ports;

//   // фигурка
//   Label* draw_elem;  // TODO: ПЕРЕИМЕНОВАТЬ В figure или т.п.
//   int inputs_n;
//   Fl_Menu_Item* menu{nullptr};

// public:
//   Element(int x = 50, int y = 50, int w = 50, int h = 50, int inputs_n =
//   0,
//           const char* l = 0);

//   Label* get_draw_elem () { return draw_elem; }

//   void set_lable (
//       std::function<void(int, int, int, int, logic::Value)> label_draw)
//   {
//     draw_elem->Label_draw_ = label_draw;
//   }

//   // void add_input_link (Link* link) { input_links.push_back(link); }

//   // void add_output_link (Link* link) { output_links.push_back(link); }

//   void add_input_port ();

//   void add_input_port_nodraw ();

//   // int handle (int x) override;

//   void draw () override;

//   int delete_port (Port* l_c);

//   // void delete_link (Port* l_c); TODO: СДЕЛАТЬ!!!

//   std::vector<Port*> get_input_ports () { return input_ports; }

//   Port* get_output_port () { return output_port; }

//   virtual void invert ();
// };

// callback для перерисовки фигурки Label в graph::Element
void callback4logic (void* lable);

// elems callbacks
void invert_elem (Fl_Widget*, void* userdata);
void delete_elem (Fl_Widget*, void* userdata);
void delete_all_elem_links (Fl_Widget*, void* userdata);
void add_port (Fl_Widget* w, void* userdata);

// //// Все что связано с классом ##Element ^^^^^^^^^^^^^^^^^^^^^^^^^^^

//// Все что связано с классами элементов vvvvvvvvvvvvvvvvvvvvvvvvv
// функции для отрисовки рисунков на элементах
void draw_and (int x, int y, int w, int h,
               logic::Value = logic::Value::False);
void draw_buff (int x, int y, int w, int h,
                logic::Value = logic::Value::False);
void draw_or (int x, int y, int w, int h,
              logic::Value = logic::Value::False);
void draw_src0 (int x, int y, int w, int h, logic::Value value);
void draw_src1 (int x, int y, int w, int h, logic::Value value);

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

#endif