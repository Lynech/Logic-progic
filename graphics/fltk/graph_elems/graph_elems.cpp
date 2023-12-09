#include "graph_elems.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace graph;

// extern link_circle_radius = 5;

// конструктор класса LinkCircle
LinkCircle::LinkCircle(int x, int y, int w, int h, link_circle_types t,
                       const char* l)
    : Fl_Widget{x, y, w, h, l}
{
  type = t;
}

// отрисовка объектов класса LinkCircle
void LinkCircle::draw()
{
  fl_color(16);
  fl_line_style(0, 4);
  fl_begin_complex_polygon();
  fl_circle(x() + link_circle_radius, y() + link_circle_radius,
            link_circle_radius);
  fl_end_complex_polygon();
}

// обработка взаимодействий с объектом класса LinkCircle
int LinkCircle::handle(int event)
{

  // std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << event << " "
  //           << FL_ENTER << std::endl;
  switch (event)
  {
  case FL_PUSH:
    // if(event_button == fl_left) ... что-то тут
    //
    std::cout << "LinkCircle push handled -- here should be menu "
              << std::endl;
    //
    return 1;
  case FL_ENTER:
    std::cout << "______entered_circle________" << std::endl;
    fl_color(FL_BLACK);
    fl_line_style(0, 4);
    fl_arc(x(), y(), w() - 2, h() - 2, 0, 360);
    return 1;

  case FL_LEAVE:
    std::cout << "______leave_circle________" << std::endl;
    redraw();
    return 1;
  case FL_DRAG:
    // is_entered =
    //     true;  //////////////////////////////// рисование новой линии
    // redraw();
    return 1;
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
      if ((baby != nullptr) && (Fl::event_inside(baby)) &&
          (baby->type != this->type))
        needed_found = true;
    }
    if (!needed_found)
      return 1;
    // определяем, из какого выходит связь и в какой входит
    Element* input_el;
    Element* output_el;
    if (baby->type == link_circle_types::input)
    {
      input_el = (graph::Element*)baby->parent();
      output_el = (graph::Element*)this->parent();
    }
    else
    {
      output_el = (graph::Element*)baby->parent();
      input_el = (graph::Element*)this->parent();
    }
    Link* l = new Link{baby, this};

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
Link::Link(LinkCircle* c1, LinkCircle* c2)
    : Fl_Widget{std::min(c1->x(), c2->x()), std::min(c1->y(), c2->y()),
                abs(c1->x() - c2->x()) + 2 * c1->link_circle_radius,
                abs(c1->y() - c2->y()) + 2 * c1->link_circle_radius}
{
}

// отрисовка объектов класса Link
void Link::draw()
{
  fl_line_style(0, 4);
  fl_color(FL_BLACK);
  fl_line(start_circle->x(), start_circle->y(), end_circle->x(),
          end_circle->y());
}

// конструктор абстрактного класса Element
Element::Element(int x_, int y_, int w_, int h_, const char* l)
    : Fl_Group{x_ - w_ * 2 / 5, y_, w_ * 9 / 5, h_, l},
      elem_link_lenth{w_ * 2 / 5}, line_thikness{w_ / 25}
{
  draw_elem = new Label{x_, y_, w_, h_};
  add(draw_elem);
  input_port = new LinkCircle{x_ - w_ * 2 / 5, y_ + h_ / 2 - w_ / 10,
                              w_ / 5, w_ / 5, link_circle_types::input};
  add(input_port);
  output_port = new LinkCircle{x_ + w_ * 6 / 5, y_ + h_ / 2 - w_ / 10,
                               w_ / 5, w_ / 5, link_circle_types::output};
  add(output_port);
}

//  конструктор класса И
And::And(int x, int y, int h, int w, const char* l) : Element{x, y, h, w, l}
{
  inputs_n = 1;
  outputs_n = 1;
  elem = new logic::And{};
  set_lable(draw_and);
}

// обработка взаимодействия с объектом класса Elem
int Element::handle(int event)
{
  // if (event == FL_PUSH && Fl::event_inside(draw_elem))
  // {
  //   // меню сюда
  //   // жобавлять лучше в конструкторе////////////////////////
  //   return 1;
  // }
  // несовсем правильно работает
  // int n = children();
  // for (int i = 0; i < n; i++)
  // {

  //   int x_ = child(i)->x() - 2;
  //   int y_ = child(i)->y() - 2;
  //   int w_ = child(i)->w() + 4;
  //   int h_ = child(i)->h() + 4;
  //   if (Fl::event_inside(x_, y_, w_, h_))
  //     return Fl_Group::handle(event);
  // }

  if (Fl_Group::handle(event))
    return 1;
  // return Fl_Group::handle(event);
  return 0;
  // return Fl_Widget::handle(event);
}

void Label::draw()
{

  draw_box(FL_FLAT_BOX, 16);
  if (Label_draw_)
  {
    int x_elem = x() + w() / 6;
    int y_elem = y() + h() / 6;
    int w_elem = 2 * w() / 3;
    int h_elem = 2 * h() / 3;
    Label_draw_(x_elem, y_elem, w_elem, h_elem, value);
  }
}

int Label::handle(int event)
{
  if (event == FL_ENTER)
  {
    fl_color(FL_BLACK);
    fl_line_style(FL_DASH, 4);
    draw_focus(FL_BORDER_FRAME, x() + 2, y() + 2, w() - 4, h() - 4);
    return 1;
  }
  if (event == FL_LEAVE)
  {
    redraw();
    return 1;
  }
  if (event == FL_PUSH)
  {
    std::cout << "Label push handled -- here should be menu" << std::endl;
    return 1;
  }
  return 0;
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

  // output link
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x_ + w_, y_ + h_ / 2, x_output_link, y_output_link);
  // input link
  fl_line(x_, y_ + h_ / 2, x_input_link, y_input_link);

  if (inverted)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_arc(x_ + w_ / 2 - 6, y_ + h_ / 2, 6, 0, 360);
  }
  Fl_Group::draw();
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
  set_lable(draw_buff);
}

// конструктор класса ИЛИ
Or::Or(int x, int y, int w, int h, const char* l) : Element{x, y, w, h, l}
{
  inputs_n = 1;
  outputs_n = 1;
  elem = new logic::Or{};
  set_lable(draw_or);
}

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