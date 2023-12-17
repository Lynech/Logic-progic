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

  logic::Element* get_logic_elem () { return logic_elem; }

  // TODO: удалить:
  // LinkCircle* get_start_circle {return start_circle;}

  // LinkCircle* get_end_circle {return end_circle;}
};

#endif