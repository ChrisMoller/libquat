dnl generator for quat tests
define(`RQ',`changequote(<,>)dnl`
'changequote`'')
dnl start at 1000 just so we don't have to with a null pointer
define(`offset', 0001)dnl
define(`cnt',    offset)dnl
define(`xinc', `define(`$1',incr($1))')dnl
define(`upcase', `translit($1, `a-z', `A-Z')')dnl
define(`entry', `void `test_'cnt () {$1}dnl
divert(1)  `test_'cnt xinc(`cnt') `,'
divert(0)'dnl
)dnl

`/********* DON'RQ()`T MODIFY THIS FILE! ********/'
`/**** Make all changes in tests.m4. ****/'

#ifndef TESTS_H
#define TESTS_H

entry(cout << r << endl;)
entry(cout << s << endl;)

entry(cout << r + s << endl;)
entry({Quat t = r; t += s; cout << t << endl;})

entry(cout << r - s << endl;)
entry({Quat t = r; t -= s; cout << t << endl;})

entry(cout << r * s << endl;)
entry(cout << s * r << endl;)
entry(cout << r * 2.0 << endl;)
entry({Quat t = r; t *= s; cout << t << endl;})
entry({Quat t = r; t *= 2.0; cout << t << endl;})

entry(cout << r / s << endl;)
entry(cout << r / 2.0 << endl;)
entry({Quat t = r; cout << (t /= s) << endl;})
entry({Quat t = r; cout << (t /= 2.0) << endl;})

entry(cout << *r << endl;)

entry(cout << (r*s == s*r)  << endl;)
entry(cout << (r*s != s*r)  << endl;)

entry(cout << *(r*s) << endl;)

entry(cout << *r * *s << endl;)
entry(cout << *s * *r << endl;)

entry(cout << +r << endl;)          // norm
entry(cout << -r << endl;)
entry(cout << r * ~r << endl;)

entry(cout << r.qdot (s) << endl;)
entry(cout << r.qdot (r) << endl;)
entry(cout << r.qcross (s) << endl;)
entry(cout << r.qcross (r) << endl;)
entry(cout << R2D (r.qang (s)) << endl;)
entry(cout << R2D (r.qang (r)) << endl;)
entry(cout << r.qstr () << endl;)

entry(cout << r/+r << endl;)        // unit
entry(cout << +r/+r << endl;)       // norm of unit

entry(cout << x << endl;)

entry(Rotation *v = x.toRotation (); v->show ();)
entry(Rotation *v = x.toRotation (); cout << v << endl;)
entry(Rotation *v = d.toRotation ();
      Quat w = v->toQuaternion ();
      cout << (d/w).round(1e-9) << endl;)
entry(Rotation *v = d.toRotation ();
      Quat w = v->toQuaternion ();
      cout << (d/w).round() << endl;)
entry(cout << u.qexp() << endl;)

entry(cout << u.qln() << endl;)
entry(cout << r.qln() << endl;)
entry(cout << (r.qln()).qexp() << endl;)
entry(cout << r.qpow(1.0) << endl;)
entry(cout << r * r << " " << r.qpow(2.0) << endl;)
entry(cout << r * r << " " << (r.qpow(2.0)).qpow(.5) << endl;)
entry(cout << r.qpow(3.5) << endl;)
entry(cout << u.qpow(3) << endl;)

typedef void (*fcn_t)();

fcn_t fcns[] {
  NULL,
undivert
`};

int nr_tests =' eval(1 + cnt - offset)`;'

#endif /* TESTS_H*/

