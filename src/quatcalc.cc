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



typedef enum {
  TYPE_UNSET,
  TYPE_DOUBLE,
  TYPE_QUAT
} vtype_t;

enum {
  WHICH_UU = (4 * TYPE_UNSET)  + TYPE_UNSET,
  WHICH_UD = (4 * TYPE_UNSET)  + TYPE_DOUBLE,
  WHICH_UQ = (4 * TYPE_UNSET)  + TYPE_QUAT,
  WHICH_DU = (4 * TYPE_DOUBLE) + TYPE_UNSET,
  WHICH_DD = (4 * TYPE_DOUBLE) + TYPE_DOUBLE,
  WHICH_DQ = (4 * TYPE_DOUBLE) + TYPE_QUAT,
  WHICH_QU = (4 * TYPE_QUAT)   + TYPE_UNSET,
  WHICH_QD = (4 * TYPE_QUAT)   + TYPE_DOUBLE,
  WHICH_QQ = (4 * TYPE_QUAT)   + TYPE_QUAT
} which_e;

class Value
{
public:
  Value () {d = NAN;}
  Value (double v) {
    d = v; vtype = TYPE_DOUBLE;
  }
  Value (double v, double w, double x, double y) {
    q = Quat (v, w, x, y); vtype = TYPE_QUAT;
  }
  Quat   getQuat ()   {return q;}
  double getDouble () {return d;}
  bool   isDouble ()  {return vtype == TYPE_DOUBLE;}
  bool   isQuat ()    {return vtype == TYPE_QUAT;}
  bool   isSet ()     {return vtype != TYPE_UNSET;}
  int    getType ()   {return vtype;}
private:
  vtype_t vtype = TYPE_UNSET;
  Quat q;
  double d;;
};

typedef void (*operation)(Value, Value);

typedef struct {
  const char *kwd;
  operation fcn;
} kwd_s;

#define opt_kwd(i) kwds[i].kwdx
#define opt_fcn(i) kwds[i].fcnx

static int
which (Value a, Value b)
{
  return  4 * a.getType () + b.getType ();
}

static void
do_plus_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << a.getQuat () + b.getQuat () << endl;;
    break;
  case WHICH_QU:
    cout << +a.getQuat () << endl;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_minus_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << a.getQuat () - b.getQuat () << endl;;
    break;
  case WHICH_QU:
    cout << -a.getQuat () << endl;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_star_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << a.getQuat () * b.getQuat () << endl;;
    break;
  case WHICH_QD:
    cout << a.getQuat () * b.getDouble () << endl;;
    break;
  case WHICH_QU:
    cout << *a.getQuat () << endl;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_slash_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << a.getQuat () / b.getQuat () << endl;;
    break;
  case WHICH_QD:
    cout << a.getQuat () / b.getDouble () << endl;;
    break;
  case WHICH_QU:
    cout << ~a.getQuat () << endl;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_eq_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat () == b.getQuat ()) << endl;;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_ne_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat () != b.getQuat ()) << endl;;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_dot_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    {
      Quat bv = b.getQuat ();
      cout << (a.getQuat ()).qdot (bv) << endl;;
    }
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_cross_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    {
      Quat bv = b.getQuat ();
      cout << (a.getQuat ()).qcross (bv) << endl;;
    }
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_ang_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    {
      Quat bv = b.getQuat ();
      cout << (a.getQuat ()).qang (bv) << endl;;
    }
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_rot_qq (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    {
      Quat bv = b.getQuat ();
      cout << (a.getQuat ()).qrot (bv) << endl;;
    }
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

kwd_s kwds[] = {
  {"+",		do_plus_qq},
  {"-",		do_minus_qq},
  {"*",		do_star_qq},
  {"/",		do_slash_qq},
  {"==",	do_eq_qq},
  {"!=",	do_ne_qq},
  {"dot",	do_dot_qq},
  {"cross",	do_cross_qq},
  {"ang",	do_ang_qq},
  {"rot",	do_rot_qq}
};

int nr_kwds = sizeof (kwds) / sizeof (kwd_s);

static int
sort_compare (const void *a, const void *b)
{
  return strcmp ((*(kwd_s *)a).kwd, (*(kwd_s *)b).kwd);
}

static int
search_compare (const void *a, const void *b)
{
  const char *ax = reinterpret_cast<const char *>(a);
  return strcmp (ax, (*(kwd_s *)b).kwd);
}

static Value
getArg (char *v)
{
  Value r;
  double a = NAN;
  double b = NAN;
  double c = NAN;
  double d = NAN;
  int cnt;

  const char *numeric = " %lf ";
  const char *quat = " [ %lf %lf %lf %lf ] ";

  cnt = sscanf (v, quat, &a, &b, &c, &d);
  if (cnt > 0) 
    r = Value (a, b, c, d);
  else {
    cnt = sscanf (v, numeric, &a);
    if (cnt > 0)
      r = Value (a);
  }
  return r;
}

int
main (int ac, char *av[])
{
  if (ac < 3) {
    cout << "too few tokens\n";
    return EXIT_FAILURE;
  }

  qsort (kwds, nr_kwds, sizeof(kwd_s), sort_compare);

  operation op = nullptr;
  Value argA;
  Value argB;
  
  {
    void *fnd = bsearch (av[1], kwds, nr_kwds, sizeof(kwd_s), search_compare);
    if (fnd) {
      kwd_s *ety = reinterpret_cast<kwd_s *>(fnd);
      if (ety->fcn) op = ety->fcn;
    }
    else {
      cout << "invalid op\n";
      return EXIT_FAILURE;
    }
  }

  argA = getArg (av[2]);
  if (ac > 3) argB = getArg (av[3]);

  (op)(argA, argB);

  return EXIT_SUCCESS;
}
