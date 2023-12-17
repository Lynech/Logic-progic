#include "logic_elems/logic_elems.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include "drawing_elems.h"

using namespace std;
int main ()
{
  string way = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
               "Logic-progic/main/sheme.txt";
  string way2 = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
                "Logic-progic/main/temp.txt";
  read_file(way);
  write_file(way2);
  return 0;
  
  map<string, logic::Element*> sheme;
  // vector<string> out;
  ifstream f("C:/Users/Niyaz/git_projects/Logic-progic/main/sheme.txt",
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
  ///////////////////////////////////////////////////////
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

  // logic::Src s1;
  // logic::Src s2{1};
  // logic::Src s3;
  // logic::Src s4{1};
  // logic::And a1;
  // s4 >> a1;
  // s1 >> ~a1;
  // s1 >> ~a1;
  // s2 >> a1;
  // s3 >> ~a1;
  // s4 >> ~a1;
  // s4 >> ~a1;

  // for (int i = 0; i < a1.arg_vec.size(); i++)
  //   printf("%p    ", a1.arg_vec[i]);
  // cout << endl;
  // cout << a1.get_value() << endl;

  // a1.remove_sorse(&s4, 1);
  // for (int i = 0; i < a1.arg_vec.size(); i++)
  //   printf("%p    ", a1.arg_vec[i]);
  // cout << endl;
  // cout << a1.get_value() << endl;

  // a1.invert_sorse(&s4, 1);
  // for (int i = 0; i < a1.arg_vec.size(); i++)
  //   printf("%p    ", a1.arg_vec[i]);
  // cout << endl;
  // cout << a1.get_value() << endl;

  // a1.remove_occurences_sourses(&s4);
  // for (int i = 0; i < a1.arg_vec.size(); i++)
  //   printf("%p    ", a1.arg_vec[i]);
  // cout << endl;
  // cout << a1.get_value() << endl;

  // // a1.remove_occurences_sourses(&s3);
  // a1.invert();
  // for (int i = 0; i < a1.arg_vec.size(); i++)
  //   printf("%p    ", a1.arg_vec[i]);
  // cout << endl;
  // cout << a1.get_value() << endl;

  // s2.invert();

  // a1.reset_sorses();
  // for (int i = 0; i < a1.arg_vec.size(); i++)
  //   printf("%p    ", a1.arg_vec[i]);
  // cout << a1.get_value() << endl;
}
catch (exception& e)
{
  cerr << e.what();

}