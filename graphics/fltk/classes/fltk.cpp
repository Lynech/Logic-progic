#include "fltk.h"

int choise (int a, int b, int c)
{
  if (b > c)
    return c;
  if (b < a)
    return a;
  return b;
}

void add_butt (Fl_Widget*, void* v)
{
  Fl_Scroll* t = (Fl_Scroll*)v;
  t->begin();
  new Fl_Light_Button(Fl::event_x(), Fl::event_y(), 100, 20, "jessey");
  t->end();
  t->redraw();
}

void add_butt2 (Fl_Widget*, void* v)
{
  Fl_Scroll* t = (Fl_Scroll*)v;
  t->begin();
  new Fl_Button(Fl::event_x(), Fl::event_y(), 100, 20, "heisenberg");
  t->end();
  t->redraw();
}

// LogicMap::LogicMap(int x, int y, int w, int h, const char* l)
//     : Fl_Scroll{x, y, w, h, l}
// {
//   map_group = new MapGroup{x, y, 1000, 1000, ""};
//   map_group->end();

//   type(Fl_Scroll::BOTH_ALWAYS);
//   color(FL_WHITE);
// };

// int LogicMap::handle(int x)
// {
//   if (x == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
//   {
//     return map_group->handle(x);
//   }
//   else
//     return Fl_Scroll::handle(x);
// }

// int MapGroup::handle(int event)
// {
//   if ((void*)this == (void*)(Fl::belowmouse()))
//   {
//     if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
//     {
//       auto temp = menu->popup(Fl::event_x(), Fl::event_y());
//       if (temp && temp->callback())
//         temp->do_callback(nullptr);
//       return 1;
//     }
//     else if (event == FL_PUSH && Fl::event_button() == FL_LEFT_MOUSE)
//     {
//       Fl_Scroll* mama = (Fl_Scroll*)parent();
//       moving_left = 1;
//       x_ = Fl::event_x() + mama->xposition();
//       y_ = Fl::event_y() + mama->yposition();
//       return 1;
//     }
//     else if (event == FL_DRAG && moving_left &&
//              Fl::event_button() == FL_LEFT_MOUSE)
//     {
//       Fl_Scroll* mama = (Fl_Scroll*)parent();

//       mama->scroll_to(choise(x_min, x_ - Fl::event_x(), x_max),
//                       choise(y_min, y_ - Fl::event_y(), y_max));

//       return 1;
//     }
//     else if (event == FL_RELEASE && Fl::event_button() ==
//     FL_LEFT_MOUSE)
//     {
//       moving_left = 0;
//       int temp = 1;
//       return temp;
//     }
//     else
//       return Fl_Group::handle(event);
//   }
//   else if (Fl::belowmouse() && (event == FL_PUSH || event ==
//   FL_RELEASE))
//   {
//     last_pused = Fl::belowmouse();
//     return last_pused->handle(event);
//   }
//   return Fl_Group::handle(event);
// }

// MapGroup::MapGroup(int x, int y, int w, int h, const char* l)
//     : Fl_Group{x, y, w, h, l}
// {
//   menu = new Fl_Menu_Item[7];
//   menu[0] = Fl_Menu_Item{"add elem", 0, 0, 0, FL_SUBMENU};
//   menu[1] = Fl_Menu_Item{"and", 0, add_elem<graph::And>, this};
//   menu[2] = Fl_Menu_Item{"or", 0, add_elem<graph::Or>, this};
//   menu[3] = Fl_Menu_Item{"not", 0, add_elem<graph::Not>, this};
//   menu[4] = Fl_Menu_Item{0};
//   menu[5] = Fl_Menu_Item{"00", 0, add_elem<graph::And>, this};
//   menu[6] = Fl_Menu_Item{0};

//   Fl_Scroll* mama = (Fl_Scroll*)parent();
//   x_min = 0;
//   y_min = 0;
//   x_max = w - mama->w() + mama->scrollbar.w();
//   y_max = h - mama->h() + mama->hscrollbar.h();
//   last_pused = nullptr;
// }

// ElemList::ElemList(int x, int y, int w, int h, MapGroup* map)
//     : Fl_Scroll{x, y, w, h}, mapgroup{map}
// {
//   type(Fl_Scroll::VERTICAL_ALWAYS);
//   color(FL_GREEN);
//   ElemGroup = new Fl_Group{x, y, w, 1000, ""};
//   gap_x = (w - scrollbar.w()) / 20;
//   gap_y = h / 60;
//   button_h = h / 5 - 2 * gap_y / 3;
//   button_w = w - scrollbar.w() - 2 * gap_x;
//   new CreateButton<graph::Not>{gap_x + x, y + gap_y, button_w,
//   button_h,
//                                "not"};
//   new CreateButton<graph::And>{gap_x + x, y + 2 * gap_y + button_h,
//                                button_w, button_h, "and"};
//   new CreateButton<graph::Or>{gap_x + x, y + 3 * gap_y + 2 *
//   button_h,
//                               button_w, button_h, "or"};
//   // int size = 50;
//   // new graph::Not{x + (w - size) / 2, y + 30, size};
//   // new graph::And{x + (w - size) / 2, y + 30 * 2 + size, size};
//   // new graph::Or{x + (w - size) / 2, x + 30 * 3 + 2 * size, size};
//   ElemGroup->end();
// };

// template <class T> int CreateButton<T>::handle(int event)
// {
//   if (event == FL_RELEASE)
//   {
//     Fl_Window* map = (Fl_Window*)(parent()->parent()->parent());
//     int n = map->children();
//     LogicMap* scroll = nullptr;
//     for (int i = 0; i < n && !scroll; i++)
//       scroll = dynamic_cast<LogicMap*>(map->child(i));
//     MapGroup* group = nullptr;
//     if (scroll)
//     {
//       n = scroll->children();
//       for (int i = 0; i < n && !group; i++)
//         group = dynamic_cast<MapGroup*>(scroll->child(i));
//     }
//     if (group)
//       add_elem<T>(nullptr, group);
//     return Fl_Button::handle(event);
//   }
//   if (event == FL_DRAG)
//     return 1;
//   return Fl_Button::handle(event);
// }
