#ifndef READ_H
#define READ_H

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
  int x;
  int y;
  bool is_inverted;
  vector<Drawing_Element*> vec_input_elements;

public:
  Drawing_Element(logic::Element* const elem_, const string& name_,
                  bool is_inverted_, int x_, int y_)
      : elem{elem_}, name{name_}, x{x_}, y{y_}, is_inverted{is_inverted_}
  {
  }

  logic::Element* get_element ();

  const string& get_name ();

  virtual vector<Drawing_Element*> get_input_elements ();

  virtual void push (Drawing_Element* el);
};

class Drawing_And : public Drawing_Element
{
private:

public:
  Drawing_And(logic::Element* const elem_, const string& name_,
              bool is_inverted_, int x_, int y_)
      : Drawing_Element(elem_, name_, is_inverted_, x_, y_)
  {
  }
};

class Drawing_Or : public Drawing_Element
{
private:

public:
  Drawing_Or(logic::Element* const elem_, const string& name_,
             bool is_inverted_, int x_, int y_)
      : Drawing_Element(elem_, name_, is_inverted_, x_, y_)
  {
  }
};

class Drawing_Source : public Drawing_Element
{
private:

public:
  Drawing_Source(logic::Element* const elem_, const string& name_,
                 bool is_inverted_, int x_, int y_)
      : Drawing_Element(elem_, name_, is_inverted_, x_, y_)
  {
  }
};

void read_file (const string& file_name);
void write_file (const string& file_name);

#endif