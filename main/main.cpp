#include "logic_elems/logic_elems.h"
#include <fstream>
#include <iostream>

using namespace std;
int main ()
try
{
  ifstream f("sheme.txt");
}
catch (exception& e)
{
  cerr << e.what();
}