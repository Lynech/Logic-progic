#include "graph_elems.h"
#include "logic_elems.h"
#include <algorithm>
#include <cmath>

#include <cassert>
#include <iostream>
#include <vector>

using namespace graph;

// todo spetial
void callback4logic (void* lable)
{
  Label* lableptr = (Label*)(lable);
  lableptr->redraw();
}

// todo spetial
// инвертирует выход
void invert_elem (Fl_Widget*, void* userdata)
{
  Label* l = (Label*)userdata;
  logic::Element* log_el = l->logic_elem;
  log_el->invert();
  l->redraw();
}

// todo spetial
void delete_all_elem_links (Fl_Widget*, void* userdata)
{
  Label* l = (Label*)userdata;
  l->delete_all_links();
}

// todo spetial
void delete_elem (Fl_Widget*, void* userdata)
{
  Label* l = (Label*)userdata;

  // удаляем связи
  l->delete_all_links();

  // удаляем Element
  l->logic_elem->reset_sorses();
  l->logic_elem->reset_dependings();
  delete (l->logic_elem);
  ///////////////////////////////////////// TODO сделать деструктор
  Fl::delete_widget(l->parent());
  Fl::do_widget_deletion();
}

// //// Все что связано с классом Element ^^^^^^^^^^^^^^^^^^^^^^^^^^

// //// Все что связано с классом #Port vvvvvvvvvvvvvvvvvvvvvvvvvvvv
// todo spetial
void invert_port (Fl_Widget*, void* userdata)
{
  Port* l_c = (Port*)userdata;
  Label* label = ((Element*)(l_c->parent()))->get_draw_elem();
  logic::Element* log_el = (logic::Element*)(label->logic_elem);

  // label->logic_elem->invert_sorse(l_c.li);

  if (l_c->get_type() == port_types::input)
  {
    logic::Element* log_el____leftside = nullptr;
    for (size_t i = 0; i < (l_c->get_links().size()) && !log_el____leftside;
         i++)
      if ((l_c->get_links()[i]) &&
          (l_c->get_links()[i]->get_output_port()) &&
          (((Element*)(l_c->get_links()[i]->get_output_port()->parent()))
               ->get_draw_elem()) &&
          (((Element*)(l_c->get_links()[i]->get_output_port()->parent()))
               ->get_draw_elem()
               ->logic_elem))

        log_el____leftside =
            ((Element*)(l_c->get_links()[i]->get_output_port()->parent()))
                ->get_draw_elem()
                ->logic_elem;

    log_el->invert_sorse(log_el____leftside, l_c->is_inverted());
    l_c->invert();
  }
  else
  {
    log_el->invert();
  }
  label->redraw();
}

// todo spetial
void delete_through_port (Fl_Widget*, void* userdata)
{
  Port* l_c = (Port*)userdata;

  std::vector<Link*> links = l_c->get_links();
  for (Link* i : links)
  {
    if ((i != nullptr) && ((i->get_input_port()) != nullptr) &&
        ((i->get_output_port()) != nullptr))
    {
      i->delete_link_input_port();
    }
  }
}

// todo spetial
void delete_link (Fl_Widget*, void* userdata)
{
  Port* port = (Port*)userdata;
  std::vector<Link*> links = port->get_links();
  for (size_t i = 0; i < links.size(); i++)
  {
    if ((links[i] != nullptr) &&
        ((links[i]->get_input_port()) != nullptr) &&
        ((links[i]->get_output_port()) != nullptr))
    {
      links[i]->delete_link();
    }
  }
}

// todo spetial
void delete_input_port (Fl_Widget*, void* userdata)
{
  Port* input_port = (Port*)userdata;
  // проверка на всякий случай
  if (input_port->get_type() != port_types::input)
    return;

  // нужно удалять сам входной порт
  auto temp = (graph::Element*)input_port->parent();
  if (!(temp->delete_port(input_port)))
    return;

  int n = temp->get_input_ports().size();

  temp->resize(temp->x(), temp->y(), temp->w(),
               (temp->h()) * (n + 1) / (n + 2));
  int circle_w = temp->w();
  circle_w /= 9;
  for (int i = 0; i < n; i++)
  {
    Port* l_c = temp->get_input_ports()[i];
    l_c->resize(temp->x(),
                temp->y() + temp->h() / (n + 1) * (i + 1) - circle_w / 2,
                circle_w, circle_w);
  }
  temp->get_output_port()->resize(temp->x() + temp->w() - circle_w,
                                  temp->y() + temp->h() / 2 - circle_w / 2,
                                  circle_w, circle_w);
}

//  конструктор класса Source

Src0::Src0(int x, int y, int h, int w, const char*) : Element{x, y, h, w, 0}
{
  type = "src0";
  draw_elem->logic_elem = new logic::Src(callback4logic, draw_elem, 0);
  // draw_elem->set_value(logic::Value::False);
  // input_ports = {};

  set_lable(draw_src0);
}

//  конструктор класса Source

Src1::Src1(int x, int y, int h, int w, const char*) : Element{x, y, h, w, 0}
{
  type = "src1";
  draw_elem->logic_elem = new logic::Src(callback4logic, draw_elem, 1);
  // draw_elem->set_value(logic::Value::True);
  // input_ports = {};

  set_lable(draw_src1);
}

//  конструктор класса И
And::And(int x, int y, int h, int w, const char* l)
    : Element{x, y, h, w, -2, l}
{
  type = "and";
  draw_elem->logic_elem = new logic::And{callback4logic, draw_elem};
  set_lable(draw_and);
}

// todo spetial
void add_port (Fl_Widget*, void* userdata)
{
  Label* label = (Label*)userdata;
  Element* elem = (Element*)(label->parent());
  elem->add_input_port();
}

// конструктор класса НЕ
Buff::Buff(int x, int y, int w, int h, const char* l)
    : Element{x, y, w, h, 1, l}
{
  type = "buff";
  draw_elem->logic_elem = new logic::Buff{callback4logic, draw_elem};
  set_lable(draw_buff);
}

// конструктор класса ИЛИ
Or::Or(int x, int y, int w, int h, const char* l)
    : Element{x, y, w, h, -2, l}
{
  type = "or";
  draw_elem->logic_elem = new logic::Or{callback4logic, draw_elem};
  set_lable(draw_or);
}

// todo spetial
void draw_and (int x, int y, int w, int h, logic::Value value)
{
  // выбор цвета в зависимости от значения
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_rectf(x + 1, y + 1, w / 2, h);

  // правая часть (окружность) заливка
  fl_pie(x + 1, y + 1, w - 2, h - 2, -90.0, 90.0);

  // левая часть обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 2);
  fl_line(x, y, x, y + h);
  fl_line(x, y, x + w / 2, y);
  fl_line(x, y + h, x + w / 2, y + h);

  // правая часть обрамление
  fl_arc(x, y, w, h, -90.0, 90.0);
}

// todo spetial
void draw_src0 (int x, int y, int w, int h, logic::Value value)
{
  // выбор цвета в зависимости от значения
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_rectf(x + 1, y + 1, w - 2, h - 2);
  fl_color(FL_BLACK);
  if (value == logic::Value::False)
  {
    fl_draw("0", x + w / 2, y + h / 2);
  }
  else if (value == logic::Value::True)
  {
    fl_draw("1", x + w / 2, y + h / 2);
  }
}

// todo spetial
void draw_src1 (int x, int y, int w, int h, logic::Value value)
{
  // выбор цвета в зависимости от значения
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_rectf(x + 1, y + 1, w - 2, h - 2);
  fl_color(FL_BLACK);
  if (value == logic::Value::False)
  {
    fl_draw("0", x + w / 2, y + h / 2);
  }
  else if (value == logic::Value::True)
  {
    fl_draw("1", x + w / 2, y + h / 2);
  }
}

// todo spetial
void draw_buff (int x, int y, int w, int h, logic::Value value)
{
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  // заполнение
  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_polygon(x, y, x, y + h, x + w, y + h / 2);
  // обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 2);
  fl_begin_loop();
  fl_vertex(x, y);
  fl_vertex(x, y + h);
  fl_vertex(x + w, y + h / 2);
  fl_end_loop();
}

// todo spetial
void draw_or (int x, int y, int w, int h, logic::Value value)
{

  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_push_matrix();
  fl_begin_complex_polygon();
  fl_translate(x, 0);
  fl_scale(2 * w / (double)h, 1.);
  fl_arc(0, y + h / 2, h / 2, -90, 90);
  fl_scale(1 / 4., 1.);
  fl_arc(0, y + h / 2, h / 2, 90, -90);
  fl_end_complex_polygon();
  fl_pop_matrix();

  fl_color(FL_BLACK);
  fl_line_style(0, 2);
  fl_push_matrix();
  fl_begin_loop();
  fl_translate(x, 0);
  fl_scale(2 * w / (double)h, 1.);
  fl_arc(0, y + h / 2, h / 2, -90, 90);
  fl_scale(1 / 4., 1.);
  fl_arc(0, y + h / 2, h / 2, 90, -90);
  fl_end_loop();
  fl_pop_matrix();
}
