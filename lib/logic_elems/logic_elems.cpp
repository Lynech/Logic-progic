#include "logic_elems.h"
#include <iostream>
using namespace logic;

bool spec::Input_element::get_value() const
{
  return (inverted ? !(arg->get_value()) : arg->get_value());
}

bool And ::get_value() const
{
  if (arg_vec.size() < 2)
    throw std::runtime_error("and must have >= 2 inputs");
  bool value = 1;
  for (size_t i = 0; value && i < arg_vec.size(); i++)
    value = arg_vec[i].get_value();
  value = inverted ? !value : value;
  return value;
}

bool Or ::get_value() const
{
  if (arg_vec.size() < 2)
    throw std::runtime_error("or must have >= 2 inputs");
  bool value = 0;
  for (size_t i = 0; !value && i < arg_vec.size(); i++)
    value = arg_vec[i].get_value();
  value = inverted ? !value : value;
  return value;
}

bool Src::get_value() const { return inverted ? !value : value; }

void Src::set_value(bool value_) { value = value_; }

void And ::reset_sorses() { arg_vec.clear(); }

void Or ::reset_sorses() { arg_vec.clear(); }

Src::Src(bool value_) { value = value_; }

Src::Src() { value = 0; }

void Logic::add_sorce(const Element& t)
{
  spec::Input_element temp{&t, inverse_input};
  this->arg_vec.push_back(temp);
  inverse_input = 0;
}

void Logic::add_sorce(const Element* t)
{
  spec::Input_element temp{t, inverse_input};
  this->arg_vec.push_back(temp);
  inverse_input = 0;
}

// Logic& operator>> (const Element& a, Logic& b)
// {
//   b.add_sorce(a);
//   return b;
// }
Element& operator>> (Element const& a, Element& b)
{
  b.add_sorce(a);
  return b;
}

Logic& Logic::operator~()
{
  inverse_input = !inverse_input;
  return *this;
}

Element& Element::operator!()
{
  inverted = !inverted;
  return *this;
}

Logic& Logic::operator!()
{
  inverted = !inverted;
  return *this;
}