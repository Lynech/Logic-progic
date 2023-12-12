// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_File_Chooser.H>
// #include <FL/Fl_Window.H>
// #include <FL/fl_draw.H>
// #include <fstream>
// #include <iostream>

// // для отрисовки
// // class MyBox : public Fl_Box
// // {
// //   void draw ()
// //   {
// //     int width = this->w();
// //     int heigth = this->h();

// //     Fl_Box::draw();  // предопределяем функцию
// //     fl_color(24);
// //     // fl_line(0, 0, width, heigth);
// //     // fl_line(0, heigth, width, 0);
// //     fl_color(25);
// //     fl_circle(width / 2, heigth / 2, 100);
// //   }

// // public:
// //   MyBox(int x, int y, int w, int h) : Fl_Box(x, y, w, h, "My window")
// //   {
// //     box(FL_FLAT_BOX);  // устанавливаем "бокс" - область
// //     color(BG_COLOR);
// //   }
// // };

// void choice () {}

// int main ()
// {
//   Fl_Window win(640, 480, "Window");
//   // MyBox bx(0, 0, 640, 480);
//   Fl_File_Chooser f{"C:/Users/MrWh1teF0x/OneDrive/Cpp_projects/", NULL,
//   50,
//                     "choose file"};

//   f.show();
//   std::ifstream txt_f{f.value(), std::ios_base::in};
//   std::string str;
//   txt_f >> str;
//   std::cout << str;
//   win.show();
//   return (Fl::run());
// };

// HEADERS
#include <FL/Fl.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <iostream>
// GLOBALS
Fl_Menu_Bar* m;
Fl_File_Chooser* fc;
#define FONT_SIZE 14

void open_cb (Fl_Widget*, void*)
{
  fc->show();
  while (fc->shown())
    Fl::wait();
  if (fc->count() == 1)
  {
    std::string file_name = fc->value();
    std::cout << file_name << '\n';
    printf("File was selected\n");
  }
}

void quit_cb (Fl_Widget*, void*) { exit(0); }

Fl_Menu_Item MenuEng[] = {
    {"&File", 0, 0, 0, FL_SUBMENU},
    {"&Open", FL_CTRL + 'o', (Fl_Callback*)open_cb},
    {"&Save", FL_CTRL + 's', 0},
    {"E&xit", FL_CTRL + 'q', (Fl_Callback*)quit_cb, 0},
    {0},
    {"&Help", 0, 0, 0, FL_SUBMENU},
    {"&About", FL_CTRL + 'a', 0},
    {0},
    {0}};

int main (int argc, char** argv)
{
  Fl_Window* window = new Fl_Window(300, 300, "Sample");
  window->color(FL_WHITE);
  m = new Fl_Menu_Bar(0, 0, 640, 25);
  m->copy(MenuEng);
  fc = new Fl_File_Chooser(".", "*.{txt}", Fl_File_Chooser::SINGLE,
                           "File_Chooser_Dialog");
  Fl_File_Input* fi = new Fl_File_Input{100, 100, 200, 30};
  fi->show();
  window->show();
  window->callback((Fl_Callback*)quit_cb, window);
  return Fl::run();
}