#include "drawing_elems.h"

// using namespace std;

int main ()
{
  string way = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
               "Logic-progic/main/sheme.txt";
  string way2 = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
                "Logic-progic/main/temp.txt";
  string way3 = "C:/Users/MrWh1teF0x/OneDrive/Engineering_workshop/"
                "Logic-progic/main/sheme2.txt";
  read_file(way);
  write_file(way2);
  read_file(way3);
  write_file(way2);
  return 0;
}