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
      sheme.insert({str, temp});
    }
    else if (str == "or")
    {
      f >> str;
      logic::Or* temp = new logic::Or;
      sheme.insert({str, temp});
    }
    else if (str == "src")
    {
      f >> str;
      logic::Src* temp = new logic::Src;
      sheme.insert({str, temp});
    }
    else if (str == "out")
    {
      f >> str;
      cout << str << " " << sheme[str]->get_value() << "\n";
    }
    else if (str == "!")
    {
      f >> str;
      if (sheme.find(str) != sheme.end())
        !(*(sheme[str]));
    }
    else if (str == "out-")
      cout << "---------\n";
    else if (sheme.find(str) != sheme.end())
    {
      cout << '-' << endl;
      string name = str;
      f >> str;
      bool is_left = str == "<<" ? true : false;
      while (str != ".")
      {
        f >> str;
        if (str == "!")
        {
          f >> str;
          if (sheme.find(str) != sheme.end())
          {
            if (is_left)
              *(sheme[name]) << !*(sheme[str]);
            else
              *(sheme[name]) >> !*(sheme[str]);
          }
        }
        else
        {
          if (sheme.find(str) != sheme.end())
          {
            if (is_left)
              *(sheme[name]) << *(sheme[str]);
            else
              *(sheme[name]) >> *(sheme[str]);
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