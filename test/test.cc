#include <iostream>
#include <complex>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <Quat.hh>

using namespace std;

//#define D2R(d) (M_PI * (d)/180.0)
//#define R2D(r) (180.0 * (r)/M_PI)

/***
    pca =? least squares/linear regression
 ***/

Quat r (1, 2, 3, 4);
Quat s (2, 3, 4, 5);
Quat u (1, 0, 0, 0);
double axis[3] = { 0.0, 0.0, 1.0};		// x axis
double diag[3] = { 1.0, 1.0, 1.0};		// x axis
Quat x (M_PI/4.0, axis);
Quat d (M_PI/4.0, diag);
complex<double> c1(1,0);
complex<double> c2(2,0);
complex<double> c25(2.5,0);

#include "tests.h"
            
int
main (int ac, char *av[])
{
  int opt;
  bool do_all = false;
  while ((opt = getopt(ac, av, "an")) != -1) {
    switch(opt) {
    case 'a':
      do_all = true;
      break;
    case 'n':
      cout << nr_tests - 1 << endl;
      return 0;
      break;
    }
  }

  if (optind >= ac) do_all = true;

  //  if (optind >= ac) return 0;

  if (do_all) {
    for (int i = 1; i < nr_tests; i++) {
      (*fcns[i])();
    }
  }
  else {
    long int wch = strtol (av[optind], nullptr, 10);
    if (wch < 1 || wch > nr_tests) return 1;

    (*fcns[wch])();
  }

  return 0;
}
