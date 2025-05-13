#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

using namespace std;

const char *argfmt = " %lf %lf %lf %lf ";

static Quat
parse_arg (char *arg)
{
  double a;
  double b;
  double c;
  double d;
  int cnt;
  Quat r;
  
  cnt = sscanf (arg, argfmt, &a, &b, &c, &d);
  if (cnt == 4)
    r = Quat (a, b, c, d);
  return r;
}

int
main (int ac, char *av[])
{
  Quat argA (0, 1, 0, 0);
  Quat argB (0, 0, 1, 0);

  {
    int v;


    while (-1 != (v = getopt (ac, av, "a:b:"))) {
      switch (v) {
      case 'a':
	argA = parse_arg (optarg);
	break;
      case 'b':
	argB = parse_arg (optarg);
	break;
      }
    }
  }
  
  int c = (ac > optind) ? atoi (av[optind]) : 4;
  
  
  vector<Quat> res = Quat::qfan (c, argA, argB);

  for (Quat n : res)
    cout << n << endl; 

  return EXIT_SUCCESS;
}
