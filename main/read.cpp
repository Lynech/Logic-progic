#include "read.h"

void read_file (const string& file_name)
try
{
  map<string, logic::Element*> sheme;
  ifstream f(file_name, ios_base::in);
  string str;
  while (f)
  {
    f >> str;
    if (str == "and")
    {
      f >> str;
      logic::And* temp = new logic::And;
      sheme[str] = temp;
    }
    else if (str == "or")
    {
      f >> str;
      logic::Or* temp = new logic::Or;
      sheme[str] = temp;
    }
    else if (str == "src")
    {
      f >> str;
      logic::Src* temp = new logic::Src;
      sheme[str] = temp;
    }
    else if (str == "out")
    {
      f >> str;
      cout << str << " " << sheme[str]->get_value() << "\n";
    }
    else if (str == "out-")
    {
      cout << "---------\n";
    }
    else if (sheme.find(str) != sheme.end())
    {
      string name = str;
      f >> str;
      if (str == ">>")
      {
        f >> str;
        if (sheme.find(str) != sheme.end())
        {
          logic::Element* p = sheme[name];
          logic::Element* p2 = sheme[str];
          *(p) >> *(p2);
        }
        f >> str;
        while (str == "," && f)
        {
          f >> str;
          if (sheme.find(str) != sheme.end())
            *(sheme[name]) >> *(sheme[str]);
          f >> str;
        }
      }
      else if (str == "<<")
      {
        f >> str;
        if (sheme.find(str) != sheme.end())
          *(sheme[name]) << *(sheme[str]);
        f >> str;
        while (str == "," && f)
        {
          f >> str;
          if (sheme.find(str) != sheme.end())
            *(sheme[name]) << *(sheme[str]);
          f >> str;
        }
      }
    }
    else if (str == "!")
    {
      f >> str;
      if (sheme.find(str) != sheme.end())
        !(*(sheme[str]));
    }
  }
  f.close();
}
catch (const std::exception& e)
{
  std::cerr << e.what() << '\n';
}
