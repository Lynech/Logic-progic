#include "fltk.h"

int choise (int a, int b, int c)
{
  if (b > c)
    return c;
  if (b < a)
    return a;
  return b;
}
