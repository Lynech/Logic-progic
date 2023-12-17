#ifndef GRAPH_LINK_H
#define GRAPH_LINK_H

#include "graph_elems.h"
#include "graph_port.h"

class Link : public Fl_Widget
{
private:
  Port *input_port, *output_port;

public:
  Link(Port* c1, Port* c2);

  void draw () override;
  void delete_link ();
  void delete_link_input_port ();

  Port* get_input_port () { return input_port; }

  Port* get_output_port () { return output_port; }

  // logic::Element* get_output_element () {return...
  // ...output_port->parent()->get_draw_elem()->logic_elem} типа того
};

#endif