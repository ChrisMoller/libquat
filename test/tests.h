

/********* DON'T MODIFY THIS FILE! ********/
/**** Make all changes in tests.m4. ****/

#ifndef TESTS_H
#define TESTS_H

void test_0001 () {cout << r << endl;}
void test_2 () {cout << s << endl;}

void test_3 () {cout << r + s << endl;}
void test_4 () {{Quat t = r; t += s; cout << t << endl;}}

void test_5 () {cout << r - s << endl;}
void test_6 () {{Quat t = r; t -= s; cout << t << endl;}}

void test_7 () {cout << r * s << endl;}
void test_8 () {cout << s * r << endl;}
void test_9 () {cout << r * 2.0 << endl;}
void test_10 () {{Quat t = r; t *= s; cout << t << endl;}}
void test_11 () {{Quat t = r; t *= 2.0; cout << t << endl;}}

void test_12 () {cout << r / s << endl;}
void test_13 () {cout << r / 2.0 << endl;}
void test_14 () {{Quat t = r; cout << (t /= s) << endl;}}
void test_15 () {{Quat t = r; cout << (t /= 2.0) << endl;}}

void test_16 () {cout << *r << endl;}

void test_17 () {cout << (r*s == s*r)  << endl;}
void test_18 () {cout << (r*s != s*r)  << endl;}

void test_19 () {cout << *(r*s) << endl;}

void test_20 () {cout << *r * *s << endl;}
void test_21 () {cout << *s * *r << endl;}

void test_22 () {cout << +r << endl;}          // norm
void test_23 () {cout << -r << endl;}
void test_24 () {cout << r * ~r << endl;}

void test_25 () {cout << r.qdot (s) << endl;}
void test_26 () {cout << r.qdot (r) << endl;}
void test_27 () {cout << r.qcross (s) << endl;}
void test_28 () {cout << r.qcross (r) << endl;}
void test_29 () {cout << R2D (r.qang (s)) << endl;}
void test_30 () {cout << R2D (r.qang (r)) << endl;}
void test_31 () {cout << r.qstr () << endl;}

void test_32 () {cout << r/+r << endl;}        // unit
void test_33 () {cout << +r/+r << endl;}       // norm of unit

void test_34 () {cout << x << endl;}

void test_35 () {Rotation *v = x.toRotation (); v->show ();}
void test_36 () {Rotation *v = x.toRotation (); cout << v << endl;}
void test_37 () {Rotation *v = d.toRotation ();
      Quat w = v->toQuaternion ();
      cout << (d/w).round(1e-9) << endl;}
void test_38 () {Rotation *v = d.toRotation ();
      Quat w = v->toQuaternion ();
      cout << (d/w).round() << endl;}
void test_39 () {cout << u.qexp() << endl;}

void test_40 () {cout << u.qln() << endl;}
void test_41 () {cout << r.qln() << endl;}
void test_42 () {cout << (r.qln()).qexp() << endl;}
void test_43 () {cout << r.qpow(1.0) << endl;}
void test_44 () {cout << r * r << " " << r.qpow(2.0) << endl;}
void test_45 () {cout << r * r << " " << (r.qpow(2.0)).qpow(.5) << endl;}
void test_46 () {cout << r.qpow(3.5) << endl;}
void test_47 () {cout << u.qpow(3) << endl;}

typedef void (*fcn_t)();

fcn_t fcns[] {
  NULL,
  test_0001  ,
  test_2  ,
  test_3  ,
  test_4  ,
  test_5  ,
  test_6  ,
  test_7  ,
  test_8  ,
  test_9  ,
  test_10  ,
  test_11  ,
  test_12  ,
  test_13  ,
  test_14  ,
  test_15  ,
  test_16  ,
  test_17  ,
  test_18  ,
  test_19  ,
  test_20  ,
  test_21  ,
  test_22  ,
  test_23  ,
  test_24  ,
  test_25  ,
  test_26  ,
  test_27  ,
  test_28  ,
  test_29  ,
  test_30  ,
  test_31  ,
  test_32  ,
  test_33  ,
  test_34  ,
  test_35  ,
  test_36  ,
  test_37  ,
  test_38  ,
  test_39  ,
  test_40  ,
  test_41  ,
  test_42  ,
  test_43  ,
  test_44  ,
  test_45  ,
  test_46  ,
  test_47  ,

};

int nr_tests = 48;

#endif /* TESTS_H*/

