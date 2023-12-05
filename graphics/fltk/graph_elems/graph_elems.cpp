#include "graph_elems.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace graph;

// конструктор класса LinkCircle
LinkCircle::LinkCircle(int xx, int yy, link_circle_types t, int h,
                       const char* l)
    : Fl_Widget{xx - link_circle_radius - 5, yy - link_circle_radius - 5,
                link_circle_radius * 2 + 10, link_circle_radius * 2 + 10, l}
{
  p_center = Point{xx, yy};
  type = t;
}

// отрисовка объектов класса LinkCircle
void LinkCircle::draw()
{
  fl_color(16);
  fl_begin_polygon();
  fl_circle(p_center.x(), p_center.y(), link_circle_radius);
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
  fl_circle(p_center.x(), p_center.y(), link_circle_radius);
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
    return 1;
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
      if (((baby != nullptr) &&
           ((x >= baby->x() && x <= baby->x() + baby->w()) &&
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
      input_el = baby->parent_elem;
      output_el = this->parent_elem;
    }
    else
    {
      output_el = baby->parent_elem;
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
Link::Link(int x1, int y1, int x2, int y2, const char* l)
    : Fl_Widget{0, 0, 0, 0, l}
{
  p_start = Point{x1, y1};
  p_end = Point{x2, y2};
}

// отрисовка объектов класса Link
void Link::draw()
{
  fl_line_style(0, 4);
  fl_color(16);
  fl_line(p_start.x(), p_start.y(), p_end.x(), p_end.y());
}

// конструктор абстрактного класса Element
// Element::Element(int x, int y, int s, int h, const char* l)
//     : Fl_Widget{x - 5, y - 5, s + 10, s + 10, l}
// {
// }

//  конструктор класса И
And::And(int x, int y, int s, int h, const char* l)
    : Element{x - 5, y - 5, s + 10, s + 10, l}
{
  logic_and = new logic::And;

  size = s;

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
  p_input_link = Point{x_input_link, y_input_link};

  int x_output_link = p_frame.x() + size + elem_link_lenth;
  int y_output_link = p_frame.y() + size / 2;
  p_output_link = Point{x_output_link, y_output_link};

  input_link = new LinkCircle{p_input_link.x(), p_input_link.y(),
                              link_circle_types::input};
  input_link->set_parent_elem(this);
  output_link = new LinkCircle{p_output_link.x(), p_output_link.y(),
                               link_circle_types::output};
  output_link->set_parent_elem(this);
}

// рисование объекта класса И
void And::draw()
{
  // обрамление
  fl_color(16);
  fl_rectf(p_frame.x(), p_frame.y(), size, size);
  // левая часть (прямоугольник) заливка
  fl_color(FL_RED);
  fl_polygon(p4.x(), p4.y(), p3.x(), p3.y(), p1.x(), p1.y(), p2.x(),
             p2.y());

  // правая часть (окружность) заливка
  fl_color(FL_RED);
  fl_begin_polygon();
  fl_arc(p_center.x(), p_center.y(), size / 6, 90, -90);
  fl_end_polygon();

  // левая часть обрамление
  fl_color(FL_BLACK);
  fl_begin_loop();
  fl_line(p1.x(), p1.y(), p2.x(), p2.y());
  fl_line(p1.x(), p1.y(), p3.x(), p3.y());
  fl_line(p3.x(), p3.y(), p4.x(), p4.y());
  fl_end_loop();

  // правая часть обрамление
  fl_color(FL_BLACK);
  fl_begin_line();
  fl_arc(p_center.x(), p_center.y(), size / 6, 90.0, -90.0);
  fl_end_line();

  if (is_entered)
  {
    fl_color(FL_BLACK);
  }
  else
  {
    fl_color(16);
  }
  fl_line_style(0, 4);
  fl_rect(p_frame.x(), p_frame.y(), size, size);

  // output link
  fl_color(16);
  fl_line_style(0, 4);

  fl_line(p_frame.x() + size, p_frame.y() + size / 2, p_output_link.x(),
          p_output_link.y());

  // input link
  fl_line(p_frame.x(), p_frame.y() + size / 2, p_input_link.x(),
          p_input_link.y());
}

// обработка взаимодействия с объектом класса И
int And::handle(int x)
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

// конструктор класса НЕ
Buff::Buff(int x, int y, int fr_size, int h, const char* l)
    : Fl_Widget{x - 5, y - 5, fr_size + 10, fr_size + 10, l}
{
  logic_buff = new logic::Buff;

  size = fr_size;
  p_frame = Point{x, y};

  // точки треугольника
  int x1 = x + size / 3;
  int y1 = y + size / 3;
  p1 = Point{x1, y1};

  int x2 = x + size / 3;
  int y2 = y + 2 * size / 3;
  p2 = Point{x2, y2};

  int x3 = x + 2 * size / 3;
  int y3 = y + size / 2;
  p3 = Point{x3, y3};

  int x_input_link = p_frame.x() - elem_link_lenth;
  int y_input_link = p_frame.y() + size / 2;
  p_input_link = Point{x_input_link, y_input_link};

  int x_output_link = p_frame.x() + size + elem_link_lenth;
  int y_output_link = p_frame.y() + size / 2;
  p_output_link = Point{x_output_link, y_output_link};

  input_link = new LinkCircle{p_input_link.x(), p_input_link.y()};
  output_link = new LinkCircle{p_output_link.x(), p_output_link.y()};
}

// рисование объекта класса НЕ
void Buff::draw()
{
  // рамка
  fl_color(16);
  fl_rectf(p_frame.x(), p_frame.y(), size, size);
  // заливка
  fl_color(FL_RED);
  fl_polygon(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
  // обрамление фигуры
  fl_color(FL_BLACK);
  fl_line_style(0, 3);
  fl_begin_loop();
  fl_line(p2.x(), p2.y(), p3.x(), p3.y());
  fl_line(p1.x(), p1.y(), p3.x(), p3.y());
  fl_line(p1.x(), p1.y(), p2.x(), p2.y());
  fl_end_loop();

  // обрамление (квадрат)
  if (is_entered)
  {
    fl_color(FL_BLACK);
  }
  else
  {
    fl_color(16);
  }
  fl_line_style(0, 4);
  fl_rect(p_frame.x(), p_frame.y(), size, size);

  // output link
  fl_color(16);
  fl_line_style(0, 4);

  fl_line(p_frame.x() + size, p_frame.y() + size / 2, p_output_link.x(),
          p_output_link.y());

  // input link
  fl_line(p_frame.x(), p_frame.y() + size / 2, p_input_link.x(),
          p_input_link.y());
}

// обработка взаимодействия с объектом класса НЕ
int Buff::handle(int x)
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

// конструктор класса ИЛИ
Or::Or(int x, int y, int fr_size, int h, const char* l)
    : Fl_Widget{x - 5, y - 5, fr_size + 10, fr_size + 10, l}
{
  logic_or = new logic::Or;

  size = fr_size;
  p_frame = Point{x, y};

  p_ellipse = Point{x, y + size / 3};
  p_circle = Point{x + size / 3, y + size / 2};

  int x_input_link = p_frame.x() - elem_link_lenth;
  int y_input_link = p_frame.y() + size / 2;
  p_input_link = Point{x_input_link, y_input_link};

  int x_output_link = p_frame.x() + size + elem_link_lenth;
  int y_output_link = p_frame.y() + size / 2;
  p_output_link = Point{x_output_link, y_output_link};

  input_link = new LinkCircle{p_input_link.x(), p_input_link.y()};
  output_link = new LinkCircle{p_output_link.x(), p_output_link.y()};
}

// рисование объекта класса ИЛИ
void Or::draw()
{
  // рамка
  fl_color(16);
  fl_rectf(p_frame.x(), p_frame.y(), size, size);
  // обрамление рамки
  if (is_entered)
  {
    fl_color(FL_BLACK);
  }
  else
  {
    fl_color(16);
  }
  fl_line_style(0, 4);
  fl_rect(p_frame.x(), p_frame.y(), size, size);

  // эллипс заливка
  fl_color(FL_RED);
  fl_line_style(0, 3);
  fl_pie(p_ellipse.x(), p_ellipse.y(), 2 * size / 3, size / 3, -90.0, 90.0);

  // полуокружность заливка
  fl_color(16);
  fl_begin_polygon();
  fl_arc(p_circle.x(), p_circle.y(), size / 6, -100, 100);
  fl_end_polygon();
  fl_begin_polygon();

  // эллипс обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 3);
  fl_begin_line();
  fl_arc(p_ellipse.x(), p_ellipse.y(), 2 * size / 3, size / 3, -90.0, 90.0);
  fl_end_line();

  // окружность обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 3);
  fl_begin_line();
  fl_arc(p_circle.x(), p_circle.y(), size / 6, -70, 70);
  fl_end_line();

  // output link
  fl_color(16);
  fl_line_style(0, 4);

  fl_line(p_frame.x() + size, p_frame.y() + size / 2, p_output_link.x(),
          p_output_link.y());

  // input link
  fl_line(p_frame.x(), p_frame.y() + size / 2, p_input_link.x(),
          p_input_link.y());
}

// обработка взаимодействия с объектом класса ИЛИ
int Or::handle(int x)
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