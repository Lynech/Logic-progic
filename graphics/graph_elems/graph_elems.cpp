#include "graph_elems.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace graph;

// конструктор класса И
And::And(int x, int y, int s, int h, const char* l)
    : Fl_Widget{x - 5, y - 5, s + 15, s + 15, l}
{
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
  fl_line_style(0, 3);
  fl_rect(p_frame.x(), p_frame.y(), size, size);
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
Not::Not(int x, int y, int fr_size, int h, const char* l)
    : Fl_Widget{x - 5, y - 5, fr_size + 15, fr_size + 15, l}
{
  frame_size = fr_size;
  p_frame = Point{x, y};

  // точки треугольника
  int x1 = x + frame_size / 3;
  int y1 = y + frame_size / 3;
  p1 = Point{x1, y1};

  int x2 = x + frame_size / 3;
  int y2 = y + 2 * frame_size / 3;
  p2 = Point{x2, y2};

  int x3 = x + 2 * frame_size / 3;
  int y3 = y + frame_size / 2;
  p3 = Point{x3, y3};
}

// рисование объекта класса НЕ
void Not::draw()
{
  // рамка
  fl_color(16);
  fl_rectf(p_frame.x(), p_frame.y(), frame_size, frame_size);
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
  fl_rect(p_frame.x(), p_frame.y(), frame_size, frame_size);
}

// обработка взаимодействия с объектом класса НЕ
int Not::handle(int x)
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
    : Fl_Widget{x - 5, y - 5, fr_size * 3 / 2 + 10, fr_size + 10, l}
{
  frame_size = fr_size;
  p_frame = Point{x, y};

  p_ellipse = Point{x, y + frame_size / 3};
  p_circle = Point{x + frame_size / 3, y + frame_size / 2};
}

// рисование объекта класса ИЛИ
void Or::draw()
{
  // рамка
  fl_color(16);
  fl_rectf(p_frame.x(), p_frame.y(), frame_size, frame_size);
  // обрамление рамки
  if (is_entered)
  {
    fl_color(FL_BLACK);
  }
  else
  {
    fl_color(16);
  }
  fl_rect(p_frame.x(), p_frame.y(), frame_size, frame_size);

  // эллипс заливка
  fl_color(FL_RED);
  fl_line_style(0, 3);
  fl_pie(p_ellipse.x(), p_ellipse.y(), 2 * frame_size / 3, frame_size / 3,
         -90.0, 90.0);

  // полуокружность заливка
  fl_color(16);
  fl_begin_polygon();
  fl_arc(p_circle.x(), p_circle.y(), frame_size / 6, -100, 100);
  fl_end_polygon();
  fl_begin_polygon();

  // эллипс обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 3);
  fl_begin_line();
  fl_arc(p_ellipse.x(), p_ellipse.y(), 2 * frame_size / 3, frame_size / 3,
         -90.0, 90.0);
  fl_end_line();

  // окружность обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 3);
  fl_begin_line();
  fl_arc(p_circle.x(), p_circle.y(), frame_size / 6, -70, 70);
  fl_end_line();
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