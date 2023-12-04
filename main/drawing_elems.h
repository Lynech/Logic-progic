#ifndef DRAWING_ELEMS_H
#define DRAWING_ELEMS_H

#include "logic_elems/logic_elems.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Drawing_Element
{
protected:
  logic::Element* elem = nullptr;
  string name;
  int x{0};
  int y{0};
  bool inverted{0};

public:
  Drawing_Element(logic::Element* const elem_, const string& name_,
                  bool inverted_, int x_, int y_)
      : elem{elem_}, name{name_}, x{x_}, y{y_}, inverted{inverted_}
  {
  }

  logic::Element* get_element ();

  const string& get_name ();

  int get_x ();

  int get_y ();

  bool is_inverted ();

  virtual vector<logic::spec::Input_element> get_input_elems () = 0;
};

class Drawing_Logic : public Drawing_Element
{
private:
  logic::Logic* elem;

public:
  Drawing_Logic(logic::Logic* const elem_, const string& name_,
                bool inverted_, int x_, int y_)
      : Drawing_Element(elem_, name_, inverted_, x_, y_)
  {
    elem = elem_;
  }

  logic::Logic* get_element ();

  vector<logic::spec::Input_element> get_input_elems () override;
};

class Drawing_And : public Drawing_Logic
{
private:

public:
  Drawing_And(logic::And* const elem_, const string& name_, bool inverted_,
              int x_, int y_)
      : Drawing_Logic(elem_, name_, inverted_, x_, y_)

  {
  }
};

class Drawing_Or : public Drawing_Logic
{
private:

public:
  Drawing_Or(logic::Or* const elem_, const string& name_, bool inverted_,
             int x_, int y_)
      : Drawing_Logic(elem_, name_, inverted_, x_, y_)
  {
  }
};

class Drawing_Src : public Drawing_Element
{
private:

public:
  Drawing_Src(logic::Src* const elem_, const string& name_, bool inverted_,
              int x_, int y_)
      : Drawing_Element(elem_, name_, inverted_, x_, y_)
  {
  }

  virtual vector<logic::spec::Input_element> get_input_elems ()
  {
    throw runtime_error("src has no input elements");
  };
};

void read_file (const string& file_name);
void write_file (const string& file_name);

#endif