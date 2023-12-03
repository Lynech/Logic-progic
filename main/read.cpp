#include "read.h"

vector<Drawing_Element*> sheme;

int get_pos (const string& el)
{
  for (size_t i = 0; i < sheme.size(); ++i)
  {
    if (sheme[i]->get_name() == el)
      return i;
  }
  return -1;
}

// bool is_valid(Drawing_Element* el)
// {

//     return false;
//   return true;
// }

void read_file (const string& file_name)
try
{
  ifstream f(file_name, ios_base::in);
  string str;
  f >> str;
  while (str != ";")
  {
    if (str == "and" || str == "src" || str == "or")
    {
      int what_el = 0;
      logic::Element* elem = nullptr;
      if (str == "and")
        elem = new logic::And;
      else if (str == "or")
      {
        elem = new logic::Or;
        what_el = 1;
      }
      else
      {
        elem = new logic::Src;
        what_el = 2;
      }
      f >> str;
      string name = str;
      f >> str;
      bool is_inv = stoi(str);
      f >> str;
      int xx = stoi(str);
      f >> str;
      int yy = stoi(str);
      Drawing_Element* temp = nullptr;
      if (what_el == 0)
        temp = new Drawing_And{elem, name, is_inv, xx, yy};
      else if (what_el == 1)
        temp = new Drawing_Or{elem, name, is_inv, xx, yy};
      else
        temp = new Drawing_Source{elem, name, is_inv, xx, yy};
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
          {
            sheme[elpos]->push(sheme[input_elpos]);
            *(sheme[elpos]->get_element())
                << !*(sheme[input_elpos]->get_element());
          }
        }
        else
        {
          int input_elpos = get_pos(str);
          if (input_elpos != -1)
          {
            sheme[elpos]->push(sheme[input_elpos]);
            *(sheme[elpos]->get_element())
                << !*(sheme[input_elpos]->get_element());
          }
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
    vector<Drawing_Element*> input_elements =
        sheme[i]->get_input_elements();
    if (sheme[i]->get_name()[0] == 's' || input_elements.size() == 0)
      continue;
    f << sheme[i]->get_name();
    f << " <<";
    for (size_t i = 0; i < input_elements.size(); ++i)
    {
      if (input_elements[i]->get_element()->is_inverted())
        f << " "
          << "~";
      f << " " << input_elements[i]->get_name();
      if (i + 1 != input_elements.size())
        f << " ,";
    }
    f << " "
      << "." << '\n';
  }
}

const string& Drawing_Element::get_name() { return name; }

logic::Element* Drawing_Element::get_element() { return elem; }

void Drawing_Element::push(Drawing_Element* el)
{
  vec_input_elements.push_back(el);
}

// void Drawing_Or::push(Drawing_Element* el)
// {
//   vec_input_elements.push_back(el);
// }

vector<Drawing_Element*> Drawing_Element::get_input_elements()
{
  return vec_input_elements;
}

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
