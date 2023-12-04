#include "drawing_elems.h"

int Drawing_Element::get_x() { return x; }

int Drawing_Element::get_y() { return y; }

bool Drawing_Element::is_inverted() { return inverted; }

const string& Drawing_Element::get_name() { return name; }

logic::Logic* Drawing_Logic::get_element() { return elem; }

vector<logic::spec::Input_element> Drawing_Logic::get_input_elems()
{
  return get_element()->get_input_elements();
}

logic::Element* Drawing_Element::get_element() { return elem; }