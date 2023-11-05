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

namespace spec {
class Input_element;
}
}  // namespace logic

class logic::Element
{
protected:
  bool inverted{0};

public:
  virtual bool get_value () const = 0;

  virtual Element& operator!();
  // logic::Element& operator>> (logic::Element& b) const;
  virtual void add_sorce (logic::Element const& t) = 0;
  virtual void add_sorce (logic::Element const* t) = 0;
};

class logic::Logic : public logic::Element
{
private:
  bool inverse_input{0};

protected:
  std::vector<logic::spec::Input_element> arg_vec;

public:
  Logic& operator~();
  Logic& operator!();
  void add_sorce (logic::Element const& t) override;
  void add_sorce (logic::Element const* t) override;
};

// logic::Logic& operator>> (const logic::Element& a, logic::Element& b);
logic::Element& operator>> (logic::Element const& a, logic::Element& b);

class logic::spec::Input_element
{
private:
  const logic::Element* arg;
  bool inverted{0};

public:
  bool get_value () const;
  Input_element() : arg{nullptr}, inverted{0} {};
  Input_element(const logic::spec::Input_element& elem)
      : arg{elem.arg}, inverted{elem.inverted} {};
  Input_element(const logic::Element* arg_) : arg{arg_}, inverted{0} {};
  Input_element(const logic::Element* arg_, bool inverted_)
      : arg{arg_}, inverted{inverted_} {};
};

class logic::And : public logic::Logic
{
private:

public:
  bool get_value () const;
  void reset_sorses ();
};

class logic::Or : public logic::Logic
{
private:

public:
  bool get_value () const;
  void reset_sorses ();
};

class logic::Src : public logic::Element
{
private:
  bool value{0};

public:
  Src();
  Src(bool value_);
  void set_value (bool value_);
  bool get_value () const;

  void add_sorce (logic::Element const&) override
  {
    throw std::runtime_error("src can't get '&'sources");
  }

  void add_sorce (logic::Element const*) override
  {
    throw std::runtime_error("src can't get '*'sources");
  }
};
#endif