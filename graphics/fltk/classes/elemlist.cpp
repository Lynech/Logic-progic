#include "elemlist.h"

ElemList::ElemList(int x, int y, int w, int h, MapGroup* map)
    : Fl_Scroll{x, y, w, h}, mapgroup{map}
{
  type(Fl_Scroll::VERTICAL_ALWAYS);
  color(FL_GREEN);
  ElemGroup = new Fl_Group{x, y, w, 1000, ""};
  gap_x = (w - scrollbar.w()) / 20;
  gap_y = h / 60;
  button_h = h / 5 - 2 * gap_y / 3;
  button_w = w - scrollbar.w() - 2 * gap_x;
  new CreateButton<graph::Buff>{gap_x + x, y + gap_y, button_w, button_h,
                                "not"};
  new CreateButton<graph::And>{gap_x + x, y + 2 * gap_y + button_h,
                               button_w, button_h, "and"};
  new CreateButton<graph::Or>{gap_x + x, y + 3 * gap_y + 2 * button_h,
                              button_w, button_h, "or"};
  // int size = 50;
  // new graph::Not{x + (w - size) / 2, y + 30, size};
  // new graph::And{x + (w - size) / 2, y + 30 * 2 + size, size};
  // new graph::Or{x + (w - size) / 2, x + 30 * 3 + 2 * size, size};
  ElemGroup->end();
};