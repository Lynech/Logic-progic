#include "drawing_elems.h"

vector<DrawingElement*> sheme;

enum class TypeElement
{
  SRC,
  OR,
  AND,
  BUFF,
  RES
};

int get_pos (const string& el)
{
  for (size_t i = 0; i < sheme.size(); ++i)
  {
    if (sheme[i]->get_name() == el)
      return i;
  }
  return -1;
}

void read_file (const string& file_name)
try
{
  ifstream f(file_name, ios_base::in);
  string str;
  f >> str;
  while (str != ";")
  {
    if (str == "and" || str == "src" || str == "or" || str == "buff")
    {
      TypeElement what_el;
      if (str == "src")
        what_el = TypeElement::SRC;
      else if (str == "or")
        what_el = TypeElement::OR;
      else if (str == "and")
        what_el = TypeElement::AND;
      else if (str == "buff")
        what_el = TypeElement::BUFF;
      else if (str == "res")
        what_el = TypeElement::RES;
      f >> str;
      string name = str;
      f >> str;
      bool inverted = stoi(str);
      f >> str;
      int xx = stoi(str);
      f >> str;
      int yy = stoi(str);
      DrawingElement* temp;
      if (what_el == TypeElement::SRC)
        temp = new DrawingSrc{new logic::Src, name, inverted, xx, yy};
      else if (what_el == TypeElement::OR)
        temp = new DrawingOr{new logic::Or, name, inverted, xx, yy};
      else if (what_el == TypeElement::AND)
        temp = new DrawingAnd{new logic::And, name, inverted, xx, yy};
      else if (what_el == TypeElement::BUFF)
        temp = new DrawingBuff{new logic::Buff, name, inverted, xx, yy};
      else if (what_el == TypeElement::RES)
        temp = new DrawingRes{new logic::Res, name, inverted, xx, yy};
      sheme.push_back(temp);
    }
    f >> str;
  }
  while (f)
  {
    f >> str;
    int elpos = get_pos(str);
    if (elpos != -1)
    {
      f >> str;
      while (str != ".")
      {
        f >> str;
        if (str == "~")
        {
          f >> str;
          int input_elpos = get_pos(str);
          if (input_elpos != -1)
            *(sheme[input_elpos]->get_element()) >>
                ~*(sheme[elpos]->get_element());
        }
        else
        {
          int input_elpos = get_pos(str);
          if (input_elpos != -1)
            *(sheme[elpos]->get_element())
                << *(sheme[input_elpos]->get_element());
        }
      }
    }
  }
  f.close();
}
catch (const std::exception& e)
{
  std::cerr << e.what() << '\n';
}

void write_file (const string& file_name)
{
  ofstream f{file_name, ios_base::trunc};
  for (size_t i = 0; i < sheme.size(); ++i)
  {
    string name = sheme[i]->get_name();
    if (name[0] == 's')
      f << "src" << ' ';
    else if (name[0] == 'o')
      f << "or" << ' ';
    else if (name[0] == 'a')
      f << "and" << ' ';
    else if (name[0] == 'b')
      f << "buff" << ' ';
    else if (name[0] == 'r')
      f << "res" << ' ';
    f << sheme[i]->get_name() << ' ' << sheme[i]->is_inverted() << ' '
      << sheme[i]->get_x() << ' ' << sheme[i]->get_y() << '\n';
  }
  f << ';' << '\n';
  for (size_t i = 0; i < sheme.size(); ++i)
  {
    if (sheme[i]->get_name()[0] == 's')
      continue;
    vector<logic::spec::Input_element> input_elements =
        sheme[i]->get_input_elems();
    if (input_elements.size() == 0)
      continue;
    f << sheme[i]->get_name() << " <<";
    for (size_t i = 0; i < input_elements.size(); ++i)
    {
      for (size_t j = 0; j < sheme.size(); ++j)
      {
        if (sheme[j]->get_element() == input_elements[i].get_arg())
        {
          f << " ";
          if (input_elements[i].is_inverted())
            f << "~ ";
          f << sheme[j]->get_name();
          if (i + 1 != input_elements.size())
            f << " ,";
          break;
        }
      }
    }
    f << " .";
    if (i + 1 != sheme.size())
      f << "\n";
  }
  f.close();
}

// void Drawing_Or::push(DrawingElement* el)
// {
//   vec_input_elements.push_back(el);
// }

// void Drawing_Or::get_input_elements() { return vec_input_elements; }

// void new_red_file(const string& file_name)
// {
//   map<string, logic::Element&> sheme;
//   map<string, pair<logic::Element&, pair<int, int>>> new_sheme;
//   ifstream f(file_name, ios_base::in);
//   string curr_str;
//   while(curr_str != ";")
//   {

//   }
// }

// void read_file (const string& file_name)
// try
// {
//   map<string, logic::Element&> sheme;
//   ifstream f(file_name, ios_base::in);
//   string str;
//   while (f)
//   {
//     f >> str;
//     if (str == "and")
//     {
//       f >> str;
//       logic::Or* elem = new logic::Or;
//       sheme.insert({str, elem});
//     }
//     else if (str == "or")
//     {
//       f >> str;
//       logic::Or* elem = new logic::Or;
//       sheme.insert({str, elem});
//     }
//     else if (str == "src")
//     {
//       f >> str;
//       logic::Src* elem = new logic::Src;
//       sheme.insert({str, elem});
//     }
//     else if (str == "out")
//     {
//       f >> str;
//       cout << str << " " << sheme[str]->get_value() << "\n";
//     }
//     else if (str == "!")
//     {
//       f >> str;
//       if (sheme.find(str) != sheme.end())
//         !(*(sheme[str]));
//     }
//     else if (str == "out-")
//       cout << "---------\n";
//     else if (sheme.find(str) != sheme.end())
//     {
//       cout << '-' << endl;
//       string name = str;
//       f >> str;
//       bool is_left = str == "<<" ? true : false;
//       while (str != ".")
//       {
//         f >> str;
//         if (str == "!")
//         {
//           f >> str;
//           if (sheme.find(str) != sheme.end())
//           {
//             if (is_left)
//               *(sheme[name]) << !*(sheme[str]);
//             else
//               *(sheme[name]) >> !*(sheme[str]);
//           }
//         }
//         else
//         {
//           if (sheme.find(str) != sheme.end())
//           {
//             if (is_left)
//               *(sheme[name]) << *(sheme[str]);
//             else
//               *(sheme[name]) >> *(sheme[str]);
//           }
//         }
//       }
//     }
//   }
//   f.close();
// }
// catch (const std::exception& e)
// {
//   std::cerr << e.what() << '\n';
// }