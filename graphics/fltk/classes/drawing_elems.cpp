#include "drawing_elems.h"

int DrawingElement::get_x() { return x; }

int DrawingElement::get_y() { return y; }

bool DrawingElement::is_inverted() { return inverted; }

const std::string& DrawingElement::get_name() { return name; }

logic::Logic* DrawingLogic::get_element() { return elem; }

std::vector<logic::spec::Input_element> DrawingLogic::get_input_elems()
{
  return get_element()->get_input_elements();
}

logic::Element* DrawingElement::get_element() { return elem; }