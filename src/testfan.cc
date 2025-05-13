#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <unistd.h>
#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

using namespace std;

int
main (int ac, char *av[])
{
  Quat argA (0, 1, 0, 0);
  Quat argB (0, 0, 1, 0);
  
  vector<Quat> res = Quat::qfan (3, argA, argB);

  for (Quat n : res)
    cout << n << endl; 

  return EXIT_SUCCESS;
}
