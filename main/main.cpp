#include "logic_elems/logic_elems.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;
int main ()
try
{
  map<string, logic::Element*> sheme;
  // vector<string> out;
  ifstream f("C:/university projects/logic/Logic-progic/main/sheme.txt",
             ios_base::in);
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
      // out.push_back(str);

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
  // for (size_t i = 0; i < out.size(); i++)
  // {
  //   logic::Value val = sheme[out[i]]->get_value();
  //   string str = "Undef";
  //   if (val == logic::Value::True)
  //     str = "True";
  //   else if (val == logic::Value::False)
  //     str = "False";
  //   cout << i << " " << str << "\n";
  // }
  // for (auto i = sheme.begin(); i != sheme.end(); i++)
  //   delete i->second;
}
catch (exception& e)
{
  cerr << e.what();
}