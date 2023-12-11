#include "graph_elems.h"
#include <algorithm>
#include <cmath>

#include <iostream>
#include <vector>

using namespace graph;

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
  fl_pie(x(), y(), w(), h(), 0., 360.);
  if (is_entered)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_arc(x(), y(), w(), h(), 0., 360.);
  }
}

int Label::handle(int event)
{
  if (event == FL_ENTER)
  {
    std::cout << "+__________Label_enter__________+\n";
    is_entered = true;
    redraw();
    return 1;
  }
  if (event == FL_LEAVE)
  {
    std::cout << "+__________Label_leave__________+\n";
    is_entered = false;
    redraw();
    return 1;
  }
  if (event == FL_PUSH)
  {
    std::cout << "+__Label push handled -- here should be menu__+\n";
    return 1;
  }
  return 0;
}

// обработка взаимодействий с объектом класса LinkCircle
int LinkCircle::handle(int event)
{

  int x_ = x(), y_ = y(), w_ = w(), h_ = h();

  // std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << event << " "
  //           << FL_ENTER << std::endl;
  switch (event)
  {
  case FL_PUSH:
    // if(event_button == fl_left) ... что-то тут
    //
    std::cout << "__LinkCircle push handled -- here should be menu__\n";
    //
    return 1;
  // case FL_MOVE:
  case FL_ENTER:
    std::cout << "______entered_circle________\n";
    // draw_focus(FL_FRAME_BOX, x(), y(), w(), h());
    is_entered = true;
    redraw();
    return 1;

  case FL_LEAVE:
    std::cout << "______leave_circle________\n";
    is_entered = false;
    redraw();
    return 1;
  case FL_DRAG:
    // is_entered =
    //     true;  //////////////////////////////// рисование новой линии
    // redraw();
    return 1;
  case FL_RELEASE:
  {
    // элемент (группа), которому принадлежит этот порт
    Element* this_elem_group = (Element*)this->parent();
    MapGroup* map = (MapGroup*)this_elem_group->parent();
    int n = map ->children();

    // int x = Fl::event_x();
    // int y = Fl::event_y();
    Element* elem_group;
    LinkCircle* l_c;

    bool needed_found = false;
    for (int i = 0; i < n && !needed_found; i++)
    {
      // взяли элемент (группа)
      elem_group = dynamic_cast<Element*>(map->child(i));
      // кол-во сущностей в элементе
      if (elem_group != nullptr)
      {
        int n1 = elem_group->children();
        for (int j = 0; j < n1 && !needed_found; j++)
        {
          // взяли сущность в надежде что она порт
          l_c = dynamic_cast<LinkCircle*>(elem_group->child(j));
          // проверяем, что это порт, он нужного типа и что наведение на него
          if ((l_c != nullptr) && (l_c != this) && (Fl::event_inside(l_c)) &&
              (l_c->type != this->type))
            needed_found = true;
        }
      }
    }
    if (!needed_found)
      return 1;
    // определяем, из какого выходит связь и в какой входит
    Element* input_el;
    Element* output_el;
    if (this->type == link_circle_types::input)
    {
      // ведем связь из this в l_c -> нужно добавить еще один вход в элемент порта
      input_el = (graph::Element*)this->parent();
      output_el = (graph::Element*)l_c->parent();
    }
    else
    {
      // ведем связь из l_c в this -> нужно добавить в еще один вход в элемент порта
      output_el = (graph::Element*)this->parent();
      input_el = (graph::Element*)l_c->parent();
    }
    input_el ->add_input_port();

    Link* l = new Link{l_c, this};
    map->add(l);

    l->redraw();

    input_el->add_input_link(l);
    output_el->add_output_link(l);
    
    input_el ->redraw();
    output_el ->redraw();

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
                abs(c1->x() - c2->x()) + c1->w(),
                abs(c1->y() - c2->y()) + c1->w()}
{
  start_circle = c1;
  end_circle = c2;
}

// отрисовка объектов класса Link
void Link::draw()
{
  fl_line_style(0, 3);
  fl_color(FL_BLACK);

  if (start_circle->get_type() == link_circle_types::input)
  {
  fl_line(start_circle->x(), start_circle->y() + start_circle->h()/2, end_circle->x() + end_circle->w(),
          end_circle->y()+ end_circle->h()/2) ;
  }
  else{
        fl_line(start_circle->x() +start_circle->w()/2 , start_circle->y() + start_circle->h()/2, end_circle->x(),
          end_circle->y()+ end_circle->h()/2) ;

  }
}

// конструктор абстрактного класса Element
Element::Element(int x_, int y_, int w_, int h_, const char* l)
    : Fl_Group{x_ - w_ * 2 / 5, y_, w_ * 9 / 5, h_, l},
      elem_link_lenth{w_ * 2 / 5}, line_thikness{w_ / 25}
{
  draw_elem = new Label{x_, y_, w_, h_};
  add(draw_elem);

  LinkCircle* first_input_port = new LinkCircle{x_ - w_ * 2 / 5, y_ + h_ / 2 - w_ / 10,
                              w_ / 5, w_ / 5, link_circle_types::input};
  
  add(first_input_port);

  input_ports.push_back(first_input_port);

  // Выходной порт
  output_port = new LinkCircle{x_ + w_ * 6 / 5, y_ + h_ / 2 - w_ / 10,
                               w_ / 5, w_ / 5, link_circle_types::output};
  add(output_port);
}

//  конструктор класса И
And::And(int x, int y, int h, int w, const char* l) : Element{x, y, h, w, l}
{
  inputs_n = 1;
  outputs_n = 1;
  draw_elem->elem = new logic::And{};
  set_lable(draw_and);
}

// обработка взаимодействия с объектом класса Elem
int Element::handle(int event)
{
  if (Fl_Group::handle(event))
    return 1;
  return 0;
}

void Element::add_input_port()
{
  int n = this->input_ports.size(); // кол-во входов
  Label* this_dr_el = this->get_draw_elem();
  // this_dr_el->resize(this_dr_el->x(), this_dr_el->y(), this_dr_el->w(), (this_dr_el->h()) * (n+2)/(n+1));
  
  LinkCircle* last_l_s = input_ports[input_ports.size() - 1]; ////////////////// TODO: при удалении оставлять 1 связь

  LinkCircle* new_l_s = new LinkCircle{last_l_s->x(), last_l_s->y() + (this_dr_el->h())/(n+1), last_l_s->w(), last_l_s->h(), link_circle_types::input};
  this->input_ports.push_back(new_l_s);
  this->add(new_l_s);
  this->resize(x(), y(), w(), (h()) * (n+2)/(n+1));
  redraw();
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
  if (is_entered)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_rect(x() + 4, y() + 4, w() - 8, h() - 8);
  }
}

void Element::draw()
{
  int x_ = x() + elem_link_lenth;
  int w_ = w() - 2 * elem_link_lenth;
  int y_ = y();
  int h_ = h();
  int x_input_link = x_ - elem_link_lenth;
  int y_input_link = y_ + h_ / 2;

////// если 0 портов - рисовать 1

    // input link
  int n = input_ports.size(); // кол-во входов 
  for (int i = 0; i<n; i++)
  {
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x_, y_ + (h_ / (n+1)) * (i + 1), x_input_link, y_ +  (h_ / (n+1)) * (i + 1));
  }
  int x_output_link = x_ + w_ + elem_link_lenth;
  int y_output_link = y_ + h_ / 2;


  
  //  output link
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x_ + w_, y_ + h_ / 2, x_output_link, y_output_link);
  
  Fl_Group::draw();

}

void Element::invert()
{
  output_port->inverted = !(output_port->inverted);
  redraw();
}

// конструктор класса НЕ
Buff::Buff(int x, int y, int w, int h, const char* l)
    : Element{x, y, w, h, l}
{
  inputs_n = 1;
  outputs_n = 1;
  draw_elem->elem = new logic::And{};
  set_lable(draw_buff);
}

// конструктор класса ИЛИ
Or::Or(int x, int y, int w, int h, const char* l) : Element{x, y, w, h, l}
{
  inputs_n = 1;
  outputs_n = 1;
  draw_elem->elem = new logic::Or{};
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