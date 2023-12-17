#ifndef GRAPH_LABEL_H
#define GRAPH_LABEL_H

#include "graph_elems.h"

// Класс фигурки для отрисовки (содержит логику)
class Label : public Fl_Widget
{
protected:
  // logic::Value value{logic::Value::Undef};
  bool is_entered = false;
  Fl_Menu_Item* menu{nullptr};

public:
  logic::Element* logic_elem;

  Label(
      int x, int y, int w, int h, const char* l = 0,
      std::function<void(int, int, int, int, logic::Value)> Label_draw = 0);

  std::function<void(int, int, int, int, logic::Value)> Label_draw_;

  void draw () override;

  // void set_value (logic::Value value_) { value = value_; }

  int handle (int event) override;

  void delete_all_links ();

  // ~Label() override;
};

#endif