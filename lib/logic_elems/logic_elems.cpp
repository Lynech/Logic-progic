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
  std::cout << "\nbefore: " << value;
  if (arg_vec.size() < 2)
    // throw std::runtime_error("and must have >= 2 inputs");
    value = Value::Undef;
  else
  {
    Value temp = Value::True;
    for (size_t i = 0; temp != Value::False && i < arg_vec.size(); i++)
      if (temp > arg_vec[i].get_value())
        temp = arg_vec[i].get_value();
    value = inverted ? !temp : temp;
  }
  std::cout << "\nafter: " << value << "\n";
}

void Or::calculate_value()
{
  if (arg_vec.size() < 2)
    // throw std::runtime_error("or must have >= 2 inputs");
    value = Value::Undef;
  else
  {
    Value temp = Value::False;
    for (size_t i = 0; temp != Value::True && i < arg_vec.size(); i++)
      if (temp < arg_vec[i].get_value())
        temp = arg_vec[i].get_value();
    value = inverted ? !temp : temp;
  }
}

void Buff::calculate_value()
{
  if (arg_vec.size() > 1)
    throw std::runtime_error("or must have >= 2 inputs");

  else
  {
    Value temp = arg_vec[0].get_value();
    value = inverted ? !temp : temp;
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

void Element::add_dependings(logic::Logic& t) { dependings.push_back(&t); }

void Element::add_dependings(logic::Logic* t) { dependings.push_back(t); }

std::ostream& operator<< (std::ostream& stream, logic::Value val)
{
  std::string str_val = "Undef";
  if (val == logic::Value::True)
    str_val = "True";
  else if (val == logic::Value::False)
    str_val = "False";
  stream << str_val;
  return stream;
}

logic::Value operator!(logic::Value value)
{
  if (value == Value::True)
    value = Value::False;
  else if (value == Value::False)
    value = Value::True;
  return value;
}