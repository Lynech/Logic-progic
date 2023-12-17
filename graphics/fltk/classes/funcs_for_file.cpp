graph::Element* get_graph_elem (Fl_Widget* elem)
{
  graph::Src0* src_0 = dynamic_cast<graph::Src0*>(elem);
  if (src_0)
    return src_0;
  graph::Src1* src_1 = dynamic_cast<graph::Src1*>(elem);
  if (src_1)
    return src_1;
  graph::And* and_ = dynamic_cast<graph::And*>(elem);
  if (and_)
    return and_;
  graph::Or* or_ = dynamic_cast<graph::Or*>(elem);
  if (or_)
    return or_;
  graph::Buff* buff_ = dynamic_cast<graph::Buff*>(elem);
  if (buff_)
    return buff_;
  return nullptr;
}

bool is_number (const std::string& num)
{
  for (size_t i = 0; i < num.size(); ++i)
    if (!isdigit(num[i]))
      return false;
  return num.size() != 0 ? true : false;
}

bool is_valid_logic_elem (std::string str)
{
  return str == "and" || str == "src0" || str == "src1" || str == "or" ||
         str == "buff";
}

// Функция, которая проверяет, принадлежит ли файл нашей грамматике
std::string is_valid_file (const std::string& file_name)
try
{
  bool is_inicialization = true;
  std::ifstream f(file_name, std::ios_base::in);
  std::vector<std::string> logic_elems;
  std::string str;
  f >> str;
  while (!f.eof())
  {
    if (is_inicialization)
    {
      if (is_valid_logic_elem(str))
      {
        logic_elems.push_back(str);
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
      if (!is_number(str))
        return "invalid logic element";
      int n = stoi(str);
      if (n >= 1 && n <= logic_elems.size())
      {
        if (logic_elems[n - 1] == "src0" || logic_elems[n - 1] == "src1")
          return "src has no input elements";
        f >> str;
        if (str != "<<")
          return "invalid syntax";
        while (true)
        {
          f >> str;
          if (str == "~")
            f >> str;
          if (!(stoi(str) >= 1 && stoi(str) <= logic_elems.size()))
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
        return "invalid logic elem";
    }
  }
  return "";
}
catch (const std::exception& e)
{
  return "syntax error";
}

void read_file (const std::string& file_name, LogicMap* map)
{
  std::string what_err = is_valid_file(file_name);
  if (what_err != "")
    throw std::runtime_error(what_err);
  std::ifstream f(file_name, std::ios_base::in);
  std::string str;
  f >> str;
  std::vector<graph::Element*> graph_elems;
  while (str != ";")
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
    graph_elems.push_back(map->map()->add_el(what_el, inverted, xx, yy));
    f >> str;
  }
  while (!f.eof())
  {
    f >> str;
    int ind = stoi(str) - 1;
    f >> str;
    while (str != ".")
    {
      f >> str;
      if (str == "~")
      {
        f >> str;
        add_inverted_input(graph_elems[ind], graph_elems[stoi(str) - 1]);
      }
      else
      {
        add_input(graph_elems[ind], graph_elems[stoi(str) - 1]);
      }
      f >> str;
    }
  }
  f.close();
}

void write_file (const std::string& file_name, LogicMap* map)
{
  std::ofstream f{file_name, std::ios_base::trunc};

  std::vector<graph::Element*> graph_elems;
  std::vector<std::vector<int>> params;

  for (int i = 0; i < map->map()->children(); ++i)
  {
    Fl_Widget* elem = map->map()->child(i);
    graph::Element* graph_elem = get_graph_elem(elem);
    if (graph_elem)
    {
      graph_elems.push_back(graph_elem);
      params.push_back(
          {graph_elem->get_draw_elem()->get_logic_elem()->is_inverted(),
           elem->x() - map->map()->x(), elem->y() - map->map()->y()});
    }
  }
  for (size_t i = 0; i < params.size(); ++i)
  {
    f << graph_elems[i]->get_type() << ' ';
    f << params[i][0] << ' ' << params[i][1] << ' ' << params[i][2] << '\n';
  }
  f << ';';
  for (size_t i = 0; i < graph_elems.size(); ++i)
  {
    if (graph_elems[i]->get_type() == "src1" ||
        graph_elems[i]->get_type() == "src0")
      continue;
    logic::Logic* logic_el = dynamic_cast<logic::Logic*>(
        graph_elems[i]->get_draw_elem()->get_logic_elem());
    std::vector<logic::spec::Input_element> input_elements =
        logic_el->get_input_elements();

    if (input_elements.size() > 0)
    {
      f << '\n';
      f << i + 1 << " << ";
      for (size_t j = 0; j < input_elements.size(); j++)
        for (size_t k = 0; k < graph_elems.size(); k++)
        {
          logic::spec::Input_element* input_elem = &(input_elements[j]);
          if (input_elem->get_arg() ==
              graph_elems[k]->get_draw_elem()->get_logic_elem())
          {
            if (input_elem->is_inverted())
              f << "~ ";
            f << k + 1 << ' ';
            if (j + 1 != input_elements.size())
              f << ", ";
            else
              f << ".";
          }
        }
    }
  }
  f.close();
}