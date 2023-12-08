#include "graph_elems.h"
#include <algorithm>
#include <cmath>

#include <iostream>
#include <vector>

using namespace graph;

// конструктор класса LinkCircle
LinkCircle::LinkCircle(int x, int y, link_circle_types t, const char* l)
    : Fl_Widget{x - link_circle_radius - 5, y - link_circle_radius - 5,
                link_circle_radius * 2 + 10, link_circle_radius * 2 + 10, l}
{
  type = t;
}

// отрисовка объектов класса LinkCircle
void LinkCircle::draw()
{
  fl_color(16);
  fl_begin_polygon();
  fl_circle(x() + link_circle_radius, y() + link_circle_radius,
            link_circle_radius - 1);
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
  fl_circle(x() + link_circle_radius, y() + link_circle_radius,
            link_circle_radius);
  fl_end_loop();
}

// обработка взаимодействий с объектом класса LinkCircle
int LinkCircle::handle(int event)
{
  switch (event)
  {
  case FL_ENTER:
    is_entered = true;
    redraw();
    return 1;
  case FL_LEAVE:
    is_entered = false;
    redraw();
    return 1;
  //case FL_DRAG:
  //  is_entered =
  //      true;  //////////////////////////////// рисование новой линии
  //  redraw();
  //  return 1;
  case FL_RELEASE:
  {
    MapGroup* par = (MapGroup*)this->parent();
    int n = par->children();
    int x = Fl::event_x();
    int y = Fl::event_y();
    LinkCircle* baby;
    bool needed_found = false;
    for (int i = 0; i < n && !needed_found; i++)
    {
      baby = dynamic_cast<LinkCircle*>(par->child(i));
      // лежит ли ребенок под мышью и правильно ли соединяем
      if (baby != nullptr &&
           Fl::event_inside(baby) &&
          baby->type != this->type)
        needed_found = true;
      
    }
    if (!needed_found)
      return 1;
    // определяем, из какого выходит связь и в какой входит
    Element* input_el;
    Element* output_el;
    if (baby->type == link_circle_types::input)
    {
      input_el = baby->get_parent_elem();
      output_el = this->parent_elem;
    }
    else
    {
      output_el = baby->get_parent_elem();
      input_el = this->parent_elem;
    }
    Link* l = new Link{baby->x(), baby->y(), this->x(), this->y()};

    // par->add(*l);
    l->redraw();
    // par->end();

    input_el->add_input_link(l);
    output_el->add_output_link(l);

    is_entered = false;
    redraw();
    return 1;
  }
  default:
    return Fl_Widget::handle(event);
  }
}

// конструктор класса Link
Link::Link(int x1, int y1, int x2, int y2, const char* l)
    : Fl_Widget{std::min(x1, x2), std::min(y1, y2),
                abs(x1 - x2) + link_circle_radius + 5,
                abs(y1 - y2) + link_circle_radius + 5, l}
{
}

// отрисовка объектов класса Link
void Link::draw()
{
  // fl_push_clip(0, 0, 1000, 1000);

  fl_line_style(0, 4);
  fl_color(FL_BLACK);
  fl_line(start_circle->x() + start_circle->link_circle_radius,
          start_circle->y() + start_circle->link_circle_radius,
          end_circle->x() + end_circle->link_circle_radius,
          end_circle->y() + end_circle->link_circle_radius);
}

// конструктор абстрактного класса Element
Element::Element(int x, int y, int w, int h, const char* l)
    : Fl_Widget{x - w * 2 / 5, y, w * 9 / 5, h, l},
      elem_link_lenth{w * 2 / 5}, line_thikness{w / 25}
{
  draw_elem = draw_Element;
  int x_input_link = x - elem_link_lenth;
  int y_input_link = y + h / 2;

  int x_output_link = x + w + elem_link_lenth;
  int y_output_link = y + h / 2;

  input_port =
      new LinkCircle{x_input_link, y_input_link, link_circle_types::input};
  input_port->set_parent_elem(this);
  output_port = new LinkCircle{x_output_link, y_output_link,
                               link_circle_types::output};
  output_port->set_parent_elem(this);
  p_frame = Point{x, y};

  int x1 = x + s / 3;
  int y1 = y + s / 3;
  p1 = Point{x1, y1};

  int x2 = x + s / 2;
  int y2 = y + s / 3;
  p2 = Point{x2, y2};

  int x3 = x + s / 3;
  int y3 = y + 2 * s / 3;
  p3 = Point{x3, y3};

  int x4 = x + s / 2;
  int y4 = y + 2 * s / 3;
  p4 = Point{x4, y4};

  int x_center = x + s / 2;
  int y_center = y + s / 2;
  p_center = Point{x_center, y_center};

  int x_input_link = p_frame.x() - elem_link_lenth;
  int y_input_link = p_frame.y() + size / 2;
  p_input_port = Point{x_input_link, y_input_link};

  int x_output_link = p_frame.x() + size + elem_link_lenth;
  int y_output_link = p_frame.y() + size / 2;
  p_output_port = Point{x_output_link, y_output_link};

  input_port = new LinkCircle{p_input_port.x(), p_input_port.y(),
                              link_circle_types::input};
  input_port->set_parent_elem(this);
  parent()->add(*input_port);

  output_port = new LinkCircle{p_output_port.x(), p_output_port.y(),
                               link_circle_types::output};
  output_port->set_parent_elem(this);
  parent()->add(*output_port);

  menu = new Fl_Menu_Item[2];
  menu[0] = Fl_Menu_Item{"invert", 0, invert_and, this};
  // menu[1] = Fl_Menu_Item{"and", 0, add_elem<graph::And>, this};
  // menu[2] = Fl_Menu_Item{"or", 0, add_elem<graph::Or>, this};
  // menu[3] = Fl_Menu_Item{"not", 0, add_elem<graph::Buff>, this};
  // menu[4] = Fl_Menu_Item{0};
  // menu[5] = Fl_Menu_Item{"00", 0, add_elem<graph::And>, this};
  menu[1] = Fl_Menu_Item{0};
  output_port->set_parent_elem(this);
}

//  конструктор класса И
And::And(int x, int y, int h, int w, const char* l) : Element{x, y, h, w, l}
{
  inputs_n = 1;
  outputs_n = 1;
  elem = new logic::And{};
  draw_elem = draw_and;
}

// обработка взаимодействия с объектом класса Elem
int Element::handle(int event)
{
  if (Fl::event_inside(x() + elem_link_lenth, y(),
                       w() - 2 * elem_link_lenth, h()))
  {
    if (!is_entered)
    {
      is_entered = true;
      redraw();
    }
    switch (event)
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
      return Fl_Widget::handle(event);
    }
  }

  if (is_entered)
  {
    is_entered = false;
    redraw();
  }
  return Fl_Widget::handle(event);
}

void Element::draw()
{
  int x_ = x() + elem_link_lenth;
  int w_ = w() - 2 * elem_link_lenth;
  int y_ = y();
  int h_ = h();
  int x_input_link = x_ - elem_link_lenth;
  int y_input_link = y_ + h_ / 2;

  int x_output_link = x_ + w_ + elem_link_lenth;
  int y_output_link = y_ + h_ / 2;

  fl_push_clip(x_ - 10 - x_output_link, y_ - 10,
               w_ + 20 + 2 * x_output_link, h_ + 20);
  // обрамление
  fl_color(16);
  fl_line_style(0, 2);
  fl_rectf(x_, y_, w_, h_);
  // левая часть (прямоугольник) заливка

  // output link
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x_ + w_, y_ + h_ / 2, x_output_link, y_output_link);
  // input link
  fl_line(x_, y_ + h_ / 2, x_input_link, y_input_link);

  if (is_entered)
    fl_color(FL_BLACK);
  else
    fl_color(16);

  fl_line_style(0, 2);
  fl_rect(x_ + 1, y_ + 1, w_ - 2, h_ - 2);

  int x_elem = x_ + w_ / 6;
  int y_elem = y_ + h_ / 6;
  int w_elem = 2 * w_ / 3;
  int h_elem = 2 * h_ / 3;
  draw_elem(x_elem, y_elem, w_elem, h_elem, get_value());
  if (inverted)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_arc(x_ + w_ / 2 - 6, y_ + h_ / 2, 6, 0, 360);
  }

  fl_pop_clip();
}

void Element::invert()
{
  inverted = !inverted;
  redraw();
}

// конструктор класса НЕ
Buff::Buff(int x, int y, int w, int h, const char* l)
    : Element{x, y, w, h, l}
{
  inputs_n = 1;
  outputs_n = 1;
  elem = new logic::And{};
  draw_elem = draw_buff;
}

// конструктор класса ИЛИ
Or::Or(int x, int y, int w, int h, const char* l) : Element{x, y, w, h, l}
{
  inputs_n = 1;
  outputs_n = 1;
  elem = new logic::Or{};
  draw_elem = draw_or;
}

void draw_and (int x, int y, int w, int h, logic::Value value)
{
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
  // fl_begin_loop();
  fl_line(x, y, x, y + h);
  fl_line(x, y, x + w / 2, y);
  fl_line(x, y + h, x + w / 2, y + h);
  // fl_end_loop();

  // правая часть обрамление
  fl_arc(x, y, w, h, -90.0, 90.0);
}

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