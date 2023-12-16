#include "logic_elems.h"
#include "graph_elems.h"
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
  callback(lable);
  std::cout << "wqertyuiop[qwertyuioptyertyioup[]]" << std::endl;
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
  Value temp = Value::True;
  if (arg_vec.size() <= 1)
    temp = Value::Undef;

  for (size_t i = 0; temp != Value::False && i < arg_vec.size(); i++)
  {
    std::cout << "input " << i << " " << arg_vec[i].get_value()
              << std::endl;
    if (temp > arg_vec[i].get_value())
      temp = arg_vec[i].get_value();
  }
  value = temp;
}

void Or::calculate_value()
{
  Value temp = Value::False;
  if (arg_vec.size() <= 1)
    temp = Value::Undef;

  for (size_t i = 0; temp != Value::True && i < arg_vec.size(); i++)
    if (temp < arg_vec[i].get_value())
      temp = arg_vec[i].get_value();
  value = temp;
}

void Buff::calculate_value()
{
  if (arg_vec.size() > 1)
    throw std::runtime_error("or must have < 1 inputs");
  else if (arg_vec.size() == 0)
    value = Value::Undef;
  else
  {
    Value temp = arg_vec[0].get_value();
    value = temp;
  }
}

Value Element::get_value() const { return inverted ? !value : value; }

void Src::set_value(bool value_)
{
  value = value_ ? Value::True : Value::False;
  calculate_dependings();
}

/// @brief удаляет все входы, ссылки на себя у этих входов
void Logic ::reset_sorses()
{
  for (size_t i = 0; i < arg_vec.size(); i++)
  {
    arg_vec[i].get_arg()->dependings.erase(
        std::remove(arg_vec[i].get_arg()->dependings.begin(),
                    arg_vec[i].get_arg()->dependings.end(), this),
        arg_vec[i].get_arg()->dependings.end());
  }
  arg_vec.clear();
  calculate_value();
  calculate_dependings();
}

/// @brief полностью удаляет src из своих sorses
/// @param src ссылка на Src или другой вход
void Logic::remove_occurences_sourses(Element* src)
{
  while (remove_sorse(src, 1))
    ;
  while (remove_sorse(src, 0))
    ;

  calculate_value();
  calculate_dependings();
}

/// @brief удаляет все выходы и себя из этих выходов
void Element::reset_dependings()
{
  while (dependings.size())
  {
    dependings[0]->remove_occurences_sourses(this);
  }
  // calculate_value();
  calculate_dependings();
}

/// @brief удаляет конкретную связь оп src и inverted
/// @param src
/// @param inverted
/// @return  0 -- если ничего не нашел, 1 -- если нашел
int Logic ::remove_sorse(Element* src, bool inverted)
{
  for (size_t i = 0; i < arg_vec.size(); i++)
  {
    if ((arg_vec[i].get_arg() == src) &&
        (arg_vec[i].is_inverted() == inverted))
    {
      auto temp =
          std::find(src->dependings.begin(), src->dependings.end(), this);
      src->dependings.erase(temp);
      // auto temp2 = std::find(arg_vec.begin(), arg_vec.end(), arg_vec[i]);
      arg_vec.erase(arg_vec.begin() + i);
      calculate_value();
      calculate_dependings();
      return 1;
    }
  }
  // calculate_value();
  // calculate_dependings();
  return 0;
}

Src::Src(std::function<void(void*)> callback, void* lable, bool value_)
    : Element{callback, lable}
{
  set_value(value_);
}

// Src::Src() { set_value(0); }

bool Logic::add_sorce(Element& t) { return add_sorce(&t); }

bool Element::does_include(Element* e)
{
  if (this == e)
    return 1;
  for (size_t i = 0; i < dependings.size(); i++)
    if (dependings[i] == e)
      return 1;
    else
      return dependings[i]->does_include(e);

  return 0;
}

bool Logic::add_sorce(Element* t)
{
  if (does_include(t))
    return 0;

  spec::Input_element temp{t, inverse_input};
  this->arg_vec.push_back(temp);
  inverse_input = 0;
  t->dependings.push_back(this);
  calculate_value();
  calculate_dependings();
  return 1;
}

bool operator>> (logic::Element& a, logic::Element& b)
{
  return b.add_sorce(a);
}

// Element& operator>> (Element& a, Element& b)
// {
//   b.add_sorce(a);
//   return b;
// }

// Element& operator<< (Element& a, Element& b)
// {
//   a.add_sorce(b);
//   return a;
// }

Element& Logic::operator~()
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

void Logic::invert_sorse(Element* src, bool inverted)
{
  for (size_t i = 0; i < arg_vec.size(); i++)
  {
    if (arg_vec[i].get_arg() == src && arg_vec[i].is_inverted() == inverted)
    {
      arg_vec[i].change_invertion();
      calculate_value();
      calculate_dependings();
      return;
    }
  }
}

void Element::invert()
{
  inverted = !inverted;
  // calculate_value();
  calculate_dependings();
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
