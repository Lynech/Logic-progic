#include "logic_elems.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace logic;

Value spec::Input_element::get_value() const
{
  if (!arg)
    return Value::Undef;
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
  std::vector<Value> depend_value;
  for (size_t i = 0; i < dependings.size(); i++)
  {
    depend_value.push_back(dependings[i]->get_value());
    dependings[i]->calculate_value();
  }
  for (size_t i = 0; i < dependings.size(); i++)
    if (depend_value[i] != dependings[i]->get_value())
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

Value Element::get_value() const { return value; }

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
  t->dependings.push_back(this);
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
  if (value == Value::False)
    value = Value::True;
  else if (value == Value::True)
    value = Value::False;

  calculate_dependings();
  return *this;
}

// Logic& Logic::operator!()
// {
//   inverted = !inverted;
//   return *this;
// }

// void Src::calculate_value()
// {
//   if (inverted)
//   {
//     if (value == Value::False)
//       value = Value::True;
//     else if (value == Value::True)
//       value = Value::False;
//   }
// }

void Element::add_dependings(logic::Logic& t) { dependings.push_back(&t); }

void Element::add_dependings(logic::Logic* t) { dependings.push_back(t); }