#ifndef DRAWING_ELEMS_H
#define DRAWING_ELEMS_H

#include "logic_elems/logic_elems.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class DrawingElement
{
protected:
  logic::Element* elem = nullptr;
  string name;
  int x{0};
  int y{0};
  bool inverted{0};

public:
  DrawingElement(logic::Element* const elem_, const string& name_,
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

class DrawingLogic : public DrawingElement
{
private:
  logic::Logic* elem;

public:
  DrawingLogic(logic::Logic* const elem_, const string& name_,
               bool inverted_, int x_, int y_)
      : DrawingElement(elem_, name_, inverted_, x_, y_)
  {
    elem = elem_;
  }

  logic::Logic* get_element ();

  vector<logic::spec::Input_element> get_input_elems () override;
};

class DrawingAnd : public DrawingLogic
{
private:

public:
  DrawingAnd(logic::And* const elem_, const string& name_, bool inverted_,
             int x_, int y_)
      : DrawingLogic(elem_, name_, inverted_, x_, y_)

  {
  }
};

class DrawingOr : public DrawingLogic
{
private:

public:
  DrawingOr(logic::Or* const elem_, const string& name_, bool inverted_,
            int x_, int y_)
      : DrawingLogic(elem_, name_, inverted_, x_, y_)
  {
  }
};

class DrawingBuff : public DrawingLogic
{
private:

public:
  DrawingBuff(logic::Buff* const elem_, const string& name_, bool inverted_,
              int x_, int y_)
      : DrawingLogic(elem_, name_, inverted_, x_, y_)
  {
  }
};

class DrawingRes : public DrawingLogic
{
private:

public:
  DrawingRes(logic::Res* const elem_, const string& name_, bool inverted_,
             int x_, int y_)
      : DrawingLogic(elem_, name_, inverted_, x_, y_)
  {
  }
};

class DrawingSrc : public DrawingElement

{
private:

public:
  DrawingSrc(logic::Src* const elem_, const string& name_, bool inverted_,
             int x_, int y_)
      : DrawingElement(elem_, name_, inverted_, x_, y_)
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