#include <iostream>
#include <iomanip>
#include <ios>
#include <math.h>
#include <stdlib.h>


#include <libquat/Quat.hh>

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

int
main (int ac, char *av[])
{
  Quat initial   (0, 1, 0, 0);
  Quat rotation (D2R (atof (av[1])), 0, 0, 1);
  Quat final = initial.qrot (rotation);
  cout << rotation << endl;
  cout << initial << endl;
  cout << final << endl;
  return 0;
}

