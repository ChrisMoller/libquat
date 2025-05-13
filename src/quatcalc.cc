// https://www.omnicalculator.com/math/quaternion

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

#define make_idx(a,b) ((4*(a)) + b)

enum {
  WHICH_UU = make_idx (TYPE_UNSET,  TYPE_UNSET),
  WHICH_UD = make_idx (TYPE_UNSET,  TYPE_DOUBLE),
  WHICH_UQ = make_idx (TYPE_UNSET,  TYPE_QUAT),
  WHICH_DU = make_idx (TYPE_DOUBLE, TYPE_UNSET),
  WHICH_DD = make_idx (TYPE_DOUBLE, TYPE_DOUBLE),
  WHICH_DQ = make_idx (TYPE_DOUBLE, TYPE_QUAT),
  WHICH_QU = make_idx (TYPE_QUAT,   TYPE_UNSET),
  WHICH_QD = make_idx (TYPE_QUAT,   TYPE_DOUBLE),
  WHICH_QQ = make_idx (TYPE_QUAT,   TYPE_QUAT)
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

static inline int
which (Value a, Value b)
{
  return  make_idx (a.getType (), b.getType ());
}

static void
do_plus (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << a.getQuat () + b.getQuat () << endl;
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
do_plusequal (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat () += b.getQuat ()) << endl;
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
do_minus (Value a, Value b)
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
do_minusequal (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()-= b.getQuat ()) << endl;
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
do_star (Value a, Value b)
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
do_starequal (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()*= b.getQuat ()) << endl;
    break;
  case WHICH_QD:
    cout << (a.getQuat ()*= b.getDouble ()) << endl;
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
do_slash (Value a, Value b)
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
do_slashequal (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()/= b.getQuat ()) << endl;
    break;
  case WHICH_QD:
    cout << (a.getQuat ()/= b.getDouble ()) << endl;
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
do_tilde (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QU:
    cout << ~a.getQuat () << endl;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_eq (Value a, Value b)
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
do_ne (Value a, Value b)
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
do_dot (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()).qdot (b.getQuat ()) << endl;;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_cross (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()).qcross (b.getQuat ()) << endl;;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_ang (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()).qang (b.getQuat ()) << endl;;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_rot (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QQ:
    cout << (a.getQuat ()).qrot (b.getQuat ()) << endl;;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_scalar (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QU:
    cout << (a.getQuat ()).qscalar () << endl;
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_axis (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QU:
    {
      vector<double> v = (a.getQuat ()).qaxis ();
      for (auto i : v)
        cout << i << " ";
      cout << endl;
    }
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

static void
do_vector (Value a, Value b)
{
  switch(which (a, b)) {
  case WHICH_QU:
    {
      vector<double> v = (a.getQuat ()).qvec ();
      for (auto i : v)
        cout << i << " ";
      cout << endl;
    }
    break;
  default:
    cout << "invalid args\n";
    break;
  }
}

kwd_s kwds[] = {
  {"+",		do_plus},
  {"+=",	do_plusequal},
  {"-",		do_minus},
  {"-=",	do_minusequal},
  {"*",		do_star},
  {"*=",	do_starequal},
  {"/",		do_slash},
  {"/=",	do_slashequal},
  {"~",		do_tilde},
  {"==",	do_eq},
  {"!=",	do_ne},
  {"dot",	do_dot},
  {"cross",	do_cross},
  {"ang",	do_ang},
  {"rot",	do_rot},
  {"scalar",	do_scalar},
  {"axis",	do_axis},
  {"vector",	do_vector}
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
