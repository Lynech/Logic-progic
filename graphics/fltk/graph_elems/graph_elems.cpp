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
  fl_color(FL_BLACK);
  fl_line(p_start.x(), p_start.y(), p_end.x(), p_end.y());
}

// конструктор абстрактного класса Element
// Element::Element(int x, int y, int s, int h, const char* l)
//     : Fl_Widget{x - 5, y - 5, s + 10, s + 10, l}
// {
// }

//  конструктор класса И
And::And(int x_, int y_, int s, int, const char* l)
    : Element{x_, y_, s, s, l}
{
  logic_and = new logic::And;

  // size = s;

  // p_frame = Point{x, y};

  // int x1 = x + s / 3;
  // int y1 = y + s / 3;
  // p1 = Point{x1, y1};

  // int x2 = x + s / 2;
  // int y2 = y + s / 3;
  // p2 = Point{x2, y2};

  // int x3 = x + s / 3;
  // int y3 = y + 2 * s / 3;
  // p3 = Point{x3, y3};

  // int x4 = x + s / 2;
  // int y4 = y + 2 * s / 3;
  // p4 = Point{x4, y4};

  // int x_center = x + s / 2;
  // int y_center = y + s / 2;
  // p_center = Point{x_center, y_center};

  int frame_thicness = 0;
  int& f_t = frame_thicness;

  int x_input_link = x() + f_t - elem_link_lenth;
  int y_input_link = y() + f_t + (h() - f_t * 2) / 2;
  // p_input_link = Point{x_input_link, y_input_link};

  int x_output_link = x() + f_t + (w() - f_t * 2) + elem_link_lenth;
  int y_output_link = y() + f_t + (h() - f_t * 2) / 2;
  // p_output_link = Point{x_output_link, y_output_link};

  input_port =
      new LinkCircle{x_input_link, y_input_link, link_circle_types::input};
  input_port->set_parent_elem(this);
  output_port = new LinkCircle{x_output_link, y_output_link,
                               link_circle_types::output};
  output_port->set_parent_elem(this);
}

// extern const uchar* fl_gray_ramp ();

// рисование объекта класса И
void And::draw()
{
  // draw_box();

  // w(w() & -2l);
  // h(h() & -2l);
  // int x1 = x() + w() / 2;
  // int y1 = y() + h() / 2;
  // // const uchar* g = fl_gray_ramp();
  // // fl_color(g[(int)'P']);
  // // fl_line(x() + 0, y1, x1, y() + 0, x() + w() - 0, y1);
  // // fl_color(g[(int)'N']);
  // // fl_line(x() + 1, y1, x1, y() + 1, x() + w() - 1, y1);
  // // fl_color(g[(int)'H']);
  // // fl_line(x() + 2, y1, x1, y() + 2, x() + w() - 2, y1);
  // // fl_color(g[(int)'W']);
  // // fl_line(x() + 2, y1, x1, y() + h() - 2, x() + w() - 2, y1);
  // // fl_color(g[(int)'U']);
  // // fl_line(x() + 1, y1, x1, y() + h() - 1, x() + w() - 1, y1);
  // // fl_color(g[(int)'S']);
  // // fl_line(x() + 0, y1, x1, y() + h() - 0, x() + w() - 0, y1);
  // Fl::set_box_color(FL_GRAY);

  // // fl_pop_clip();
  // fl_line_style(FL_DOT, 1);
  // if (is_entered)
  // {
  //   fl_color(FL_BLACK);
  //   // Fl::set_box_color(FL_BLACK);
  // }
  // else
  // {
  //   fl_color(FL_GRAY);
  //   // Fl::set_box_color(FL_GRAY);
  // }
  // fl_polygon(x(), y(), x() + w(), y(), x() + w(), y() + h(), x(),
  //            y() + h());
  // fl_color(FL_MAGENTA);
  // fl_loop(x(), y(), x() + w(), y(), x() + w(), y() + h(), x(), y() +
  // h());

  // fl_push_clip(parent()->x(), parent()->y(), parent()->w(),
  // parent()->h());fl_color(16);

  // p_frame = Point{x, y};
  int frame_thicness = 0;
  int& f_t = frame_thicness;

  int x1 = x() + f_t + (w() - f_t * 2) / 3;
  int y1 = y() + f_t + (h() - f_t * 2) / 3;
  // p1 = Point{x1, y1};

  int x2 = x() + f_t + (w() - f_t * 2) / 2;
  int y2 = y() + f_t + (h() - f_t * 2) / 3;
  // p2 = Point{x2, y2};

  int x3 = x() + f_t + (w() - f_t * 2) / 3;
  int y3 = y() + f_t + 2 * (h() - f_t * 2) / 3;
  // p3 = Point{x3, y3};

  int x4 = x() + f_t + (w() - f_t * 2) / 2;
  int y4 = y() + f_t + 2 * (h() - f_t * 2) / 3;
  // p4 = Point{x4, y4};

  int x_center = x() + f_t + (w() - f_t * 2) / 2;
  int y_center = y() + f_t + (h() - f_t * 2) / 2;
  // p_center = Point{x_center, y_center};

  int x_input_link = x() + f_t - elem_link_lenth;
  int y_input_link = y() + f_t + (h() - f_t * 2) / 2;
  // p_input_link = Point{x_input_link, y_input_link};

  int x_output_link = x() + f_t + (w() - f_t * 2) + elem_link_lenth;
  int y_output_link = y() + f_t + (h() - f_t * 2) / 2;
  // p_output_link = Point{x_output_link, y_output_link};

  fl_push_clip(x() - 10 - x_output_link, y() - 10,
               w() + 20 + 2 * x_output_link, h() + 20);
  fl_push_matrix();
  // обрамление
  fl_color(16);
  fl_rectf(x() + f_t, y() + f_t, w() - f_t * 2, h() - f_t * 2);
  // левая часть (прямоугольник) заливка
  fl_color(FL_RED);
  fl_polygon(x4, y4, x3, y3, x1, y1, x2, y2);

  // правая часть (окружность) заливка
  fl_color(FL_RED);
  fl_begin_polygon();

  fl_pie(x_center, y_center, (w() - f_t * 2) / 3 - 1,
         (h() - f_t * 2) / 3 - 1, -90.0, 90.0);  // полный оборот
  // fl_vertex(x_center, y_center);
  // fl_vertex(x_center + f_t, y_center + f_t);
  // fl_vertex(x_center + (w() - f_t * 2) / 3 - f_t, y_center + f_t);
  // fl_vertex(x_center + (w() - f_t * 2) / 3 - f_t,
  //           y_center + (h() - f_t * 2) / 3 - f_t);
  // fl_vertex(x_center + f_t, y_center + f_t);
  // fl_vertex(x_center, y_center);
  // fl_vertex(x_center + (w() - f_t * 2) / 3, y_center);
  // fl_vertex(x_center + (w() - f_t * 2) / 3, y_center + (h() - f_t * 2) /
  // 3);
  fl_end_polygon();

  // левая часть обрамление
  fl_color(FL_BLACK);
  // fl_begin_loop();
  fl_line(x1, y1, x2, y2);
  fl_line(x1, y1, x3, y3);
  fl_line(x3, y3, x4, y4);
  // fl_end_loop();

  // правая часть обрамление
  fl_color(FL_BLACK);
  // fl_begin_line();
  fl_arc(x_center, y_center, (w() - f_t * 2) / 3, (h() - f_t * 2) / 3,
         -90.0, 90.0);
  // fl_end_line();

  fl_line_style(0, 4);
  if (is_entered)
  {
    fl_color(FL_BLACK);
    // fl_line(x() + f_t, y() + f_t, x() + f_t, y() + f_t + h() - f_t * 2);
    // fl_line(x() + f_t + w() - f_t * 2, y() + f_t, x() + f_t + w() - f_t *
    // 2,
    //         y() + f_t + h() - f_t * 2);
    // fl_line(x() + f_t, y() + f_t, x() + f_t + w() - f_t * 2, y() + f_t);
    // fl_line(x() + f_t, y() + f_t + h() - f_t * 2, x() + f_t + w() - f_t *
    // 2,
    //         y() + f_t + h() - f_t * 2);
  }
  else
  {
    fl_color(16);
  }
  fl_rect(x() + f_t, y() + f_t, w() - f_t * 2, h() - f_t * 2);

  // output link
  fl_color(16);
  fl_line_style(0, 4);

  fl_line(x() + f_t + w() - f_t * 2, y() + f_t + (h() - f_t * 2) / 2,
          x_output_link, y_output_link);

  // input link
  fl_line(x() + f_t, y() + f_t + (h() - f_t * 2) / 2, x_input_link,
          y_input_link);
  fl_pop_matrix();
  fl_pop_clip();
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
  // case FL_FOCUS:
  // case FL_UNFOCUS:
  // //   redraw();
  //   return parent()->handle(x);
  default:
    // redraw();
    // return Fl_Button::handle(x);
    return 1;
  }
}

// конструктор класса НЕ
Buff::Buff(int x, int y, int fr_size, int h, const char* l)
    : Element{x - 5, y - 5, fr_size + 10, fr_size + 10, l}
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

  input_port = new LinkCircle{p_input_link.x(), p_input_link.y()};
  output_port = new LinkCircle{p_output_link.x(), p_output_link.y()};
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
    // redraw();
    return Fl_Widget::handle(x);
  }
}

// конструктор класса ИЛИ
Or::Or(int x, int y, int fr_size, int h, const char* l)
    : Element{x - 5, y - 5, fr_size + 10, fr_size + 10, l}
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

  input_port = new LinkCircle{p_input_link.x(), p_input_link.y()};
  output_port = new LinkCircle{p_output_link.x(), p_output_link.y()};
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
    // redraw();
    return Fl_Widget::handle(x);
  }
}