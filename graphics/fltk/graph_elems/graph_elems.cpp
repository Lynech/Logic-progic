#include "graph_elems.h"
#include <algorithm>
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
  case FL_DRAG:
    is_entered =
        true;  //////////////////////////////// рисование новой линии
    redraw();
    return parent()->handle(event);
  case FL_RELEASE:
  {
    MapGroup* par = (MapGroup*)this->parent();
    int n = par->children();
    int x = Fl::event_x();
    int y = Fl::event_y();
    LinkCircle* baby;
    for (int i = 0; i < n; i++)
    {
      baby = dynamic_cast<LinkCircle*>(par->child(i));
      // лежит ли ребенок под мышью и правильно ли соединяем
      if ((baby && ((x >= baby->x() && x <= baby->x() + baby->w()) &&
                    (y >= baby->y() && y <= baby->y() + baby->w()))) &&
          (baby->type != this->type))
        break;
    }
    if (!baby)
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
Link::Link(int x, int y, int w, int h, const char* l)
    : Fl_Widget{x, y, w, h, l}
{
}

// отрисовка объектов класса Link
void Link::draw()
{
  fl_line_style(0, 4);
  fl_color(FL_BLACK);
  fl_line(start_circle->x() + start_circle->link_circle_radius,
          start_circle->y() + start_circle->link_circle_radius,
          end_circle->x() + end_circle->link_circle_radius,
          end_circle->y() + end_circle->link_circle_radius);
}

// конструктор абстрактного класса Element
Element::Element(int x, int y, int w, int h, const char* l)
    : Fl_Widget{x, y, w, h, l}
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
int Element::handle(int x)
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

void Element::draw()
{
  int x_input_link = x() - elem_link_lenth;
  int y_input_link = y() + h() / 2;

  int x_output_link = x() + w() + elem_link_lenth;
  int y_output_link = y() + h() / 2;

  fl_push_clip(x() - 10 - x_output_link, y() - 10,
               w() + 20 + 2 * x_output_link, h() + 20);
  // обрамление
  fl_color(16);
  fl_line_style(0, 2);
  fl_rectf(x(), y(), w(), h());
  // левая часть (прямоугольник) заливка

  // output link
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x() + w(), y() + h() / 2, x_output_link, y_output_link);
  // input link
  fl_line(x(), y() + h() / 2, x_input_link, y_input_link);

  if (is_entered)
    fl_color(FL_BLACK);
  else
    fl_color(16);

  fl_line_style(0, 2);
  fl_rect(x() + 1, y() + 1, w() - 2, h() - 2);

  int x_elem = x() + w() / 6;
  int y_elem = y() + h() / 6;
  int w_elem = 2 * w() / 3;
  int h_elem = 2 * h() / 3;
  draw_elem(x_elem, y_elem, w_elem, h_elem, get_value());
  if (inverted)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_arc(x() + w() / 2 - 6, y() + h() / 2, 6, 0, 360);
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