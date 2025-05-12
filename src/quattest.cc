#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//#include <libquat/Quat.hh>
#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)


Quat r (1, 2, 3, 4);
Quat s (2, 3, 4, 5);

#define TEST(n,f) void test##n () {f}
#define DOTEST(n) test##n ();

TEST (01, cout << r;)
TEST (02, cout << s;)
TEST (03, cout << r + s;)
TEST (04, {Quat t = r; cout << (t += s);})
TEST (05, {Quat t = r; cout << (t -= s);})
TEST (06, cout << r * s;)
TEST (07, cout << s * r;)
TEST (08, cout << (r*s == s*r) ;)
TEST (09, cout << (r*s != s*r) ;)
TEST (10, cout << r/s;)
TEST (11, cout << *(r*s);)
TEST (12, cout << *r * *s;)
TEST (13, cout << *s * *r;)
TEST (14, cout << +r;)
TEST (15, cout << -r;)
TEST (16, cout << ~r;)
TEST (17, cout << r * ~r;)
TEST (18, cout <<  r * 7;)
TEST (19, cout <<  r / 7;)
TEST (20, {Quat x = r; cout << (x *= s);})
TEST (21, {Quat x = r; cout << (x /= s);})
TEST (22, cout << r.qdot (s);)
TEST (23, cout << r.qdot (r);)
TEST (24, cout << r.qcross (s);)
TEST (25, cout << r.qcross (r);)
//TEST (26, cout << r.qrot (s);)
TEST (27, cout << R2D (r.qang (s));)
TEST (28, cout << R2D (r.qang (r));)
TEST (29, cout << r.qstr ();)

typedef void (*fcn_t)();

fcn_t fcns[] = {
  NULL,
  test01,
  test02,
  test03,
  test04,
  test05,
  test06,
  test07,
  test08,
  test09,
  test10,
  test11,
  test12,
  test13,
  test14,
  test15,
  test16,
  test17,
  test18,
  test19,
  test20,
  test21,
  test22,
  test23,
  test24,
  test25,
//  test26,
  test27,
  test28,
  test29
};
      
int nr_opts = sizeof(fcns) / sizeof(fcn_t);
            
int
main (int ac, char *av[])
{
  int opt;
  bool do_all = false;
  while ((opt = getopt(ac, av, "na")) != -1) {
    switch(opt) {
    case 'n':
      cout << nr_opts << endl;
      return 0;
      break;
    case 'a':
      do_all = true;
      break;
    }
  }

  if (do_all) {
    for (int i = 1; i < nr_opts; i++) {
      fprintf (stdout, "    {\"%d\" \"", i);
      (*fcns[i])();
      fprintf (stdout, "\" }\n");
    }
  }
  else {
    if (optind >= ac) return 0;

    long int wch = strtol (av[optind], nullptr, 10);
    if (wch < 1 || wch > nr_opts) return 1;

    (*fcns[wch])();
  }

  return 0;
}
