#include "logic_elems.h"
#include <algorithm>
#include <iostream>
using namespace logic;

Value spec::Input_element::get_value() const
{
  if (inverted)
  {
    if (arg->get_value() == Value::False)
      return Value::True;
    else if (arg->get_value() == Value::True)
      return Value::False;
  }
  return arg->get_value();
}

void Element::calculate_dependings()
{
  for (size_t i = 0; i < dependings.size(); i++)
    dependings[i]->calculate_value();
  for (size_t i = 0; i < dependings.size(); i++)
    dependings[i]->calculate_dependings();
}

void And::calculate_value()
{
  if (arg_vec.size() < 2)
    // throw std::runtime_error("and must have >= 2 inputs");
    value = Value::Undef;
  else
  {
    value = Value::True;
    for (size_t i = 0; value > Value::False && i < arg_vec.size(); i++)
      value = arg_vec[i].get_value();
    if (inverted)
    {
      if (value == Value::True)
        value = Value::False;
      else if (value == Value::False)
        value = Value::True;
    }
  }
}

void Or::calculate_value()
{
  if (arg_vec.size() < 2)
    // throw std::runtime_error("or must have >= 2 inputs");
    value = Value::Undef;
  else
  {
    value = Value::False;
    for (size_t i = 0; value < Value::True && i < arg_vec.size(); i++)
      value = arg_vec[i].get_value();
    if (inverted)
    {
      if (value == Value::True)
        value = Value::False;
      else if (value == Value::False)
        value = Value::True;
    }
  }
}

Value Element::get_value() const
{
  if (inverted)
  {
    if (value == Value::False)
      return Value::True;
    else if (value == Value::True)
      return Value::False;
  }
  return value;
}

void Src::set_value(bool value_)
{
  value = value_ ? Value::True : Value::False;
  calculate_dependings();
}

void Element::remove_depending(logic::Logic* t)
{
  auto temp = std::find(dependings.begin(), dependings.end(),
                        t);  // потенциальная ошибка
  if (temp != dependings.end())
    dependings.erase(temp);
}

void spec::Input_element::remove(logic::Logic* t)
{
  arg->remove_depending(t);
}

void Logic ::reset_sorses()
{
  for (size_t i = 0; i < arg_vec.size(); i++)
  {
    arg_vec[i].remove(this);
  }
  arg_vec.clear();
}

// void Or ::reset_sorses() { arg_vec.clear(); }

Src::Src(bool value_) { set_value(value_); }

Src::Src() { set_value(0); }

void Logic::add_sorce(Element& t) { add_sorce(&t); }

void Logic::add_sorce(Element* t)
{
  spec::Input_element temp{t, inverse_input};
  this->arg_vec.push_back(temp);
  inverse_input = 0;
  calculate_value();
  calculate_dependings();
}

Element& operator>> (Element& a, Element& b)
{
  b.add_sorce(a);
  return b;
}

Element& operator<< (Element& a, Element& b)
{
  a.add_sorce(b);
  return a;
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

// Logic& Logic::operator!()
// {
//   inverted = !inverted;
//   return *this;
// }

void Element::add_dependings(logic::Logic& t) { dependings.push_back(&t); }

void Element::add_dependings(logic::Logic* t) { dependings.push_back(t); }