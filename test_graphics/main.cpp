#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>  //для отрисовки
#define BG_COLOR 0

class MyBox : public Fl_Box
{
  void draw ()
  {
    int width = this->w();
    int heigth = this->h();

    Fl_Box::draw();  // предопределяем функцию
    fl_color(24);
    // fl_line(0, 0, width, heigth);
    // fl_line(0, heigth, width, 0);
    fl_color(25);
    fl_circle(width / 2, heigth / 2, 100);
  }

public:
  MyBox(int x, int y, int w, int h) : Fl_Box(x, y, w, h, "My window")
  {
    box(FL_FLAT_BOX);  // устанавливаем "бокс" - область
    color(BG_COLOR);
  }
};

int main ()
{
  Fl_Window win(640, 480, "Window");
  MyBox bx(0, 0, 640, 480);
  win.show();
  return (Fl::run());
};