#ifndef LOGIC_ELEMS_H
#define LOGIC_ELEMS_H
#include <iostream>
#include <stdexcept>
#include <vector>

namespace logic {
class Element;
class Logic;
class And;
class Or;
class Src;
enum class Value
{
  False = 0,
  Undef,
  True,
};

namespace spec {
class Input_element;
}
}  // namespace logic

logic::Element& operator>> (logic::Element& a, logic::Element& b);
logic::Element& operator<< (logic::Element& a, logic::Element& b);

class logic::Element
{
protected:
  bool inverted{0};
  Value value{Value::Undef};
  std::vector<logic::Logic*> dependings;
  void add_dependings (logic::Logic& t);
  void add_dependings (logic::Logic* t);

public:
  Value get_value () const;
  void calculate_dependings ();
  void remove_depending (logic::Logic* t);

  virtual Element& operator!();
  virtual void
  add_sorce (logic::Element& t) = 0;  // возможна ошибка, надо обдумать
  virtual void add_sorce (logic::Element* t) = 0;
};

class logic::Logic : public logic::Element
{
private:
  bool inverse_input{0};

protected:
  std::vector<logic::spec::Input_element> arg_vec;

public:
  virtual void calculate_value () = 0;
  Logic& operator~();
  // Logic& operator!();  // поменять на invert
  void add_sorce (logic::Element& t);  // возможна ошибка, надо обдумать
  void add_sorce (logic::Element* t) override;
  void reset_sorses ();
};

class logic::And : public logic::Logic
{
private:

public:
  void calculate_value () override;
};

class logic::Or : public logic::Logic
{
private:

public:
  void calculate_value () override;
};

class logic::Src : public logic::Element
{
private:

public:
  Src();
  Src(bool value_);
  void set_value (bool value_);

  void add_sorce (logic::Element&)  // возможна ошибка, надо обдумать
  {
    throw std::runtime_error("src can't get '&'sources");
  }

  void add_sorce (logic::Element*) override
  {
    throw std::runtime_error("src can't get '*'sources");
  }
};

///////////////////////////////////////////////////////////////////////////////

class logic::spec::Input_element
{
private:
  logic::Element* arg;
  bool inverted{0};

public:
  Value get_value () const;
  void remove (logic::Logic*);
  Input_element() : arg{nullptr}, inverted{0} {};
  Input_element(const logic::spec::Input_element& elem)
      : arg{elem.arg}, inverted{elem.inverted} {};
  Input_element(logic::Element* arg_) : arg{arg_}, inverted{0} {};
  Input_element(logic::Element* arg_, bool inverted_)
      : arg{arg_}, inverted{inverted_} {};
};

#endif