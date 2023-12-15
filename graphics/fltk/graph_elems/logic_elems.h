#ifndef LOGIC_ELEMS_H
#define LOGIC_ELEMS_H
#include "graph_elems.h"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

class Label;

namespace logic {
class Element;
class Logic;
class And;
class Or;
class Src;
class Buff;

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
std::ostream& operator<< (std::ostream& a, logic::Value b);
logic::Value operator!(logic::Value value);

class logic::Element
{
protected:
  std::function<void(void*)> callback;
  void* lable;
  bool inverted{0};
  Value value{Value::Undef};
  void add_dependings (logic::Logic& t);
  void add_dependings (logic::Logic* t);

public:
  void invert ();
  std::vector<logic::Logic*> dependings;
  Value get_value () const;
  void calculate_dependings ();

  bool is_inverted () { return inverted; }

  // void remove_depending (logic::Logic* t);
  // virtual void calculate_value () { value = inverted ? !value : value; }

  void reset_dependings ();
  Element& operator!();
  virtual Element& operator~() = 0;
  virtual void add_sorce (logic::Element& t) = 0;
  virtual void add_sorce (logic::Element* t) = 0;
  virtual void reset_sorses () = 0;
  virtual void remove_occurences_sourses (Element* src) = 0;
  virtual int remove_sorse (Element* src, bool inverted) = 0;
  virtual void invert_sorse (Element* src, bool inverted) = 0;

  Element(
      std::function<void(void*)> callback = [] (void*) {},
      void* lable = nullptr)
  {
    this->callback = callback;
    this->lable = lable;
  }
};

class logic::Logic : public logic::Element
{
private:
  bool inverse_input{0};

protected:
  // std::vector<logic::spec::Input_element> arg_vec;

public:
  Logic(
      std::function<void(void*)> callback = [] (void*) {},
      void* lable = nullptr)
      : Element{callback, lable}
  {
  }

  std::vector<logic::spec::Input_element> arg_vec;
  Element& operator~() override;
  virtual void calculate_value () = 0;
  void add_sorce (logic::Element& t) override;
  void add_sorce (logic::Element* t) override;
  void reset_sorses () override;
  void remove_occurences_sourses (Element* src) override;
  int remove_sorse (Element* src, bool inverted) override;
  void invert_sorse (Element* src, bool inverted) override;
};

class logic::And : public logic::Logic
{
private:

public:
  And(
      std::function<void(void*)> callback = [] (void*) {},
      void* lable = nullptr)
      : Logic{callback, lable}
  {
  }

  void calculate_value () override;
};

class logic::Or : public logic::Logic
{
private:

public:
  Or(
      std::function<void(void*)> callback = [] (void*) {},
      void* lable = nullptr)
      : Logic{callback, lable}
  {
  }

  void calculate_value () override;
};

class logic::Buff : public logic::Logic
{
private:

public:
  Buff(
      std::function<void(void*)> callback = [] (void*) {},
      void* lable = nullptr)
      : Logic{callback, lable}
  {
  }

  void calculate_value () override;
};

class logic::Src : public logic::Element
{
private:

public:
  // Src();
  Src(
      std::function<void(void*)> callback = [] (void*) {},
      void* lable = nullptr, bool value_ = 0);
  void set_value (bool value_);

  void reset_sorses () override { return; }

  void remove_occurences_sourses (Element* src) override
  {
    throw std::runtime_error("src has no sources");
  }

  int remove_sorse (Element* src, bool inverted) override
  {
    throw std::runtime_error("src has no sources");
  }

  void invert_sorse (Element* src, bool inverted) override
  {
    throw std::runtime_error("src has no sources");
  }

  virtual Element& operator~() override
  {
    throw std::runtime_error("src has no sources to invert");
  }

  // void calculate_value () override;

  void
  add_sorce (logic::Element&) override  // возможна ошибка, надо обдумать
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
  // void remove (logic::Logic*);
  Input_element() : arg{nullptr}, inverted{0} {};
  Input_element(const logic::spec::Input_element& elem)
      : arg{elem.arg}, inverted{elem.inverted} {};
  Input_element(logic::Element* arg_) : arg{arg_}, inverted{0} {};
  Input_element(logic::Element* arg_, bool inverted_)
      : arg{arg_}, inverted{inverted_} {};

  logic::Element* get_arg () { return arg; }

  bool is_inverted () { return inverted; }

  void change_invertion () { inverted = (!inverted); }
};

#endif
