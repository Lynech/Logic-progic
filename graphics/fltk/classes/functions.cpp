#include "add_elem_impl.h"
#include "drawing_elems.h"
#include "mapgroup.h"

std::vector<DrawingElement*> sheme;

void write_elem (std::string elem, int is_inverted, int x, int y,
                 std::ofstream file)
{
  file << elem << ' ';
  file << is_inverted << ' ';
  file << x << ' ';
  file << y;
}

int get_pos (const std::string& el)
{
  for (size_t i = 0; i < sheme.size(); ++i)
  {
    if (sheme[i]->get_name() == el)
      return i;
  }
  return -1;
}

bool is_number (const std::string& num)
{
  for (size_t i = 0; i < num.size(); ++i)
    if (!isdigit(num[i]))
      return false;
  return num.size() != 0 ? true : false;
}

bool is_valid_name (std::string name)
{
  if (name[0] != 'a' && name[0] != 'o' && name[0] != 's' &&
      name[0] != 'r' && name[0] != 'b')
    return false;
  name.erase(0, 1);
  return is_number(name);
}

std::string is_valid_logic_elem (std::string str)
{
  if (str[0] == 's')
    return "src has no input elements";
  if (!is_valid_name(str))
    return "invalid logic element";
  return "";
}

// Функция, которая проверяет, принадлежит ли файл нашей грамматике
std::string is_valid_file (const std::string& file_name)
try
{
  bool is_inicialization = true;
  std::ifstream f(file_name, std::ios_base::in);
  std::vector<std::string> names_of_elems;
  std::string str;
  f >> str;
  while (!f.eof())
  {
    if (is_inicialization)
    {
      if (str == "and" || str == "src" || str == "or" || str == "buff" ||
          str == "res")
      {
        f >> str;
        if (!is_valid_name(str))
          return "invalid name of element";
        names_of_elems.push_back(str);
        f >> str;
        if (str != "0" && str != "1")
          return "invalid value of inversion";
        f >> str;
        if (!is_number(str))
          return "invalid x-position";
        f >> str;
        if (!is_number(str))
          return "invalid y-position";
        f >> str;
        if (str == ";")
        {
          is_inicialization = false;
          f >> str;
        }
      }
      else
        return "invalid element";
    }
    else
    {
      std::string what_error = is_valid_logic_elem(str);
      if (what_error == "")
      {
        f >> str;
        if (str != "<<")
          return "invalid syntax";
        while (true)
        {
          f >> str;
          if (str == "~")
            f >> str;
          if (std::find(names_of_elems.begin(), names_of_elems.end(),
                        str) == names_of_elems.end())
            return "invalid input element";
          f >> str;
          if (str == ",")
            continue;
          else if (str == ".")
          {
            f >> str;
            break;
          }
          else
            return "invalid syntax";
        }
      }
      else
        return what_error;
    }
  }
  return "";
}
catch (const std::exception& e)
{
  return "syntax error";
}

std::vector<DrawingElement*> read_file (const std::string& file_name,
                                        LogicMap* map)
{
  std::string what_err = is_valid_file(file_name);
  if (what_err != "")
    throw std::runtime_error(what_err);
  std::ifstream f(file_name, std::ios_base::in);
  std::string str;
  f >> str;
  while (str != ";")
  {
    if (str == "and" || str == "src" || str == "or" || str == "buff")
    {
      TypeElement what_el;
      if (str == "src0")
        what_el = TypeElement::SRC0;
      else if (str == "src1")
        what_el = TypeElement::SRC1;
      else if (str == "or")
        what_el = TypeElement::OR;
      else if (str == "and")
        what_el = TypeElement::AND;
      else if (str == "buff")
        what_el = TypeElement::BUFF;
      f >> str;
      bool inverted = stoi(str);
      f >> str;
      int xx = stoi(str);
      f >> str;
      int yy = stoi(str);
      // map->map()->add_el(what_el, xx, yy);
      // std::string name = map->map()->
    }
    f >> str;
  }
  // while (f)
  // {
  //   f >> str;
  //   int elpos = get_pos(str);
  //   if (elpos != -1)
  //   {
  //     f >> str;
  //     while (str != ".")
  //     {
  //       f >> str;
  //       if (str == "~")
  //       {
  //         f >> str;
  //         int input_elpos = get_pos(str);
  //         if (input_elpos != -1)
  //           *(sheme[input_elpos]->get_element()) >>
  //               ~*(sheme[elpos]->get_element());
  //       }
  //       else
  //       {
  //         int input_elpos = get_pos(str);
  //         if (input_elpos != -1)
  //           *(sheme[elpos]->get_element())
  //               << *(sheme[input_elpos]->get_element());
  //       }
  //     }
  //   }
  // }
  f.close();
  return sheme;
}

void write_file (const std::string& file_name, LogicMap* map)
{
  std::ofstream f{file_name, std::ios_base::trunc};
  // for (size_t i = 0; i < sheme.size(); ++i)
  // {
  //   std::string name = sheme[i]->get_name();
  //   if (name[0] == 's')
  //     f << "src" << ' ';
  //   else if (name[0] == 'o')
  //     f << "or" << ' ';
  //   else if (name[0] == 'a')
  //     f << "and" << ' ';
  //   else if (name[0] == 'b')
  //     f << "buff" << ' ';
  //   else if (name[0] == 'r')
  //     f << "res" << ' ';
  //   f << sheme[i]->get_name() << ' ' << sheme[i]->is_inverted() << ' '
  //     << sheme[i]->get_x() << ' ' << sheme[i]->get_y() << '\n';
  // }

  for (size_t i = 0; i < map->map()->children(); ++i)
  {
    auto* graph_elem = map->map()->child(i);
  }

  f << ';' << '\n';
  for (size_t i = 0; i < sheme.size(); ++i)
  {
    if (sheme[i]->get_name()[0] == 's')
      continue;
    std::vector<logic::spec::Input_element> input_elements =
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