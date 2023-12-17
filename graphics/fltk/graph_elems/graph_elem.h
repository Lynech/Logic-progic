#ifndef GRAPH_ELEM_H
#define GRAPH_ELEM_H

#include "graph_elems.h"
#include "graph_label.h"

namespace graph {
class And;
class Or;
class Buff;
class Element;
class Src0;
class Src1;
};  // namespace graph

class Port;
class Label;

class graph::Element : public Fl_Group
{
private:
  // удалить если не нужно TODO
  int elem_link_lenth{20};
  int line_thikness{2};

protected:
  std::string type;
  // единственный выход:
  Port* output_port;
  // мно-во входов
  std::vector<Port*> input_ports;

  // фигурка
  Label* draw_elem;  // TODO: ПЕРЕИМЕНОВАТЬ В figure или т.п.
  int inputs_n;
  Fl_Menu_Item* menu{nullptr};

public:
  Element(int x = 50, int y = 50, int w = 50, int h = 50, int inputs_n = 0,
          const char* l = 0);

  Label* get_draw_elem () { return draw_elem; }

  void set_lable (
      std::function<void(int, int, int, int, logic::Value)> label_draw)
  {
    draw_elem->Label_draw_ = label_draw;
  }

  void add_input_port ();

  void add_input_port_nodraw ();

  void draw () override;

  int delete_port (Port* l_c);

  const std::string get_type () { return type; }

  // void delete_link (Port* l_c); TODO: СДЕЛАТЬ!!!

  //   logic::Element get_logic_element(); TODO

  std::vector<Port*> get_input_ports () { return input_ports; }

  Port* get_output_port () { return output_port; }

  virtual void invert ();

  // ~Element() override;
};

#endif