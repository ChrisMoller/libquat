
/*
    libquat Copyright (C) 2025 C. H. L. Moller under the terms of the
    GNU General Public License Version 3.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <cmath>

#include "Quat.hh"
#include "eigens.hh"

Quat::Quat ()
{
  a = NAN;
  b = NAN;
  c = NAN;
  d = NAN;
}

Quat::Quat (double ai, double bi, double ci, double di)
{
  a = ai;
  b = bi;
  c = ci;
  d = di;
}

Quat::Quat (double ai)
{
  a = ai;
  b = 0;
  c = 0;
  d = 0;
}

Quat::Quat (double *v)
{
  a = v[0];
  b = v[1];
  c = v[2];
  d = v[3];
}

Quat::Quat (double theta, double *v)
{
  a = cos (theta/2.0);
  double sintheta = sin (theta/2.0);
  b = sintheta * v[0];
  c = sintheta * v[1];
  d = sintheta * v[2];
}

Quat::~Quat ()
{
}

Quat
Quat::operator+(Quat v)	// add
{
  Quat s;
  s.a = a + v.a;
  s.b = b + v.b;
  s.c = c + v.c;
  s.d = d + v.d;
  return s;
}

Quat
Quat::operator+=(Quat &v)	// add-assign
{
  Quat s;
  a += v.a;
  b += v.b;
  c += v.c;
  d += v.d;
  return *this;
}

Quat
Quat::operator-(Quat v)	// subtract
{
  Quat s;
  s.a = a - v.a;
  s.b = b - v.b;
  s.c = c - v.c;
  s.d = d - v.d;
  return s;
}

Quat
Quat::operator-=(Quat &v)	// subtract-assign
{
  Quat s;
  a -= v.a;
  b -= v.b;
  c -= v.c;
  d -= v.d;
  return *this;
}

Quat
Quat::operator*(Quat v)	// multiply / product
{
  Quat s;
  s.a = (a * v.a) - ((b * v.b) + (c * v.c) + (d * v.d));
  s.b = ((a * v.b) + (b * v.a) + (c * v.d)) - (d * v.c);
  s.c = ((a * v.c) + (c * v.a) + (d * v.b)) - (b * v.d);
  s.d = ((a * v.d) + (b * v.c) + (d * v.a)) - (c * v.b);
  return s;
}

Quat
Quat::operator*=(Quat &v)	// multiply-assign
{
  Quat s;
  s.a = (a * v.a) - ((b * v.b) + (c * v.c) + (d * v.d));
  s.b = ((a * v.b) + (b * v.a) + (c * v.d)) - (d * v.c);
  s.c = ((a * v.c) + (c * v.a) + (d * v.b)) - (b * v.d);
  s.d = ((a * v.d) + (b * v.c) + (d * v.a)) - (c * v.b);
  a = s.a;
  b = s.b;
  c = s.c;
  d = s.d;
  return *this;
}

Quat
Quat::operator*(const double v)	// multiply by double
{
  Quat s;
  s.a = a * v;
  s.b = b * v;
  s.c = c * v;
  s.d = d * v;
  return s;
}

Quat
Quat::operator*=(const double v)	// multiply by double assign
{
  a = a * v;
  b = b * v;
  c = c * v;
  d = d * v;
  return *this;
}

Quat
Quat::operator/(Quat v)	// divide
{
  Quat s = ~v;			// invert denominator
  Quat t = *this * s;
  return t;
}

Quat
Quat::operator/=(Quat &v)	// divide-assign
{
  Quat s = ~v;			// invert denominator
  Quat t = *this * s;
  *this = t;
  return t;
}

Quat
Quat::operator/(double v)	// divide by double
{
#if 1
  a = a / v;
  b = b / v;
  c = c / v;
  d = d / v;
  return *this;
#else
  Quat s;
  s.a = a / v;
  s.b = b / v;
  s.c = c / v;
  s.d = d / v;
  return s;
#endif
}

Quat
Quat::operator/=(const double v)	// multiply by double assign
{
  a = a / v;
  b = b / v;
  c = c / v;
  d = d / v;
  return *this;
}

// I'm using monadic * because quaternions have no use for
// a dereference operator
Quat
Quat::operator*()		// conjugation
{
  Quat s;
  s.a = a;
  s.b = -b;
  s.c = -c;
  s.d = -d;
  return s;
}

double
Quat::operator+()		// norm
{
  double s = sqrt ((a * a) + (b * b) + (c * c) + (d * d));
  return s;
}

Quat
Quat::operator-()		// negation
{
  Quat s;
  s.a = -a;
  s.b = -b;
  s.c = -c;
  s.d = -d;
  return s;
}

// Note that c++ doesn't support monadic / which would
// have made more sense, so I'm using monadic tilde (~)
// because quaternions have no use for a complement operator
Quat
Quat::operator~()		// reciprocal / invert
{
  Quat s;
  double m2 = (a * a) + (b * b) + (c * c) + (d * d);
  s.a =  a/m2;
  s.b = -b/m2;
  s.c = -c/m2;
  s.d = -d/m2;
  return s;
}

bool
Quat::operator==(Quat v)	// eq
{
  bool s = (a == v.a) && (b == v.b) && (c == v.c) && (d == v.d);
  return s;
}

bool
Quat::operator!=(Quat v)	// neq
{
  bool s = (a != v.a) || (b != v.b) || (c != v.c) || (d != v.d);
  return s;
}

string
Quat::qstr ()			// stringify
{
  char *s;
  asprintf (&s, "[%#08g [%#08g %#08g %#08g]]", a, b, c, d);
  string t (s);
  free (s);
  return t;
}

double *
Quat::qvec ()			// convert to array
{
  double *v = new double[4];
  v[0] = a;
  v[1] = b;
  v[2] = c;
  v[3] = d;
  return v;
}

double *
Quat::qaxis ()			// extract axis component
{
  double *v = new double[3];
  v[0] = b;
  v[1] = c;
  v[2] = d;
  return v;
}

double
Quat::qscalar ()		// extract scalar component
{
  return a;
}

ostream&
operator<<(ostream& os, const Quat &v)
{
  os << "[ " << v.a << " " << v.b << " " << v.c << " " << v.d << " ]";
    return os;
}

double
Quat::qdot (Quat &v)
{
  return (b * v.b) + (c * v.c) + (d * v.d);
}

Quat
Quat::qrot (const Quat v)
{
  Quat q =  (*this) * v * ~(*this);
  return q;
}

vector<Quat>
Quat::qrot (vector<Quat> &v)
{
  vector<Quat> rc;
  for (const Quat q : v) {
    Quat r =  (*this) * q * ~(*this);
    rc.emplace_back (r);
  }
  return rc;
}

Quat
Quat::qcross (Quat &v)
{
  Quat s;
  s.a = 0.0;
  s.b = (c * v.d) - (d * v.c);
  s.c = (d * v.b) - (b * v.d);
  s.d = (b * v.c) - (c * v.b);
  return s;
}

double
Quat::qang (Quat v)
{
  double dt = (b * v.b) + (c * v.c) + (d * v.d);
  double m1 = sqrt (pow (b, 2.0) + pow (c, 2.0) + pow (d, 2.0));
  double m2 = sqrt (pow (v.b, 2.0) + pow (v.c, 2.0) + pow (v.d, 2.0));
  return acos (dt / (m1 * m2));
}

Rotation *
Quat::toRotation ()
{
  Rotation *h = new Rotation;

  Quat q = *this;
  q/=+q;			//normalise;
  
  double q0 = q.a;		//w r
  double q02 = q0 * q0;
  
  double q1 = q.b;		//x i
  double q12 = q1 * q1;

  double q2 = q.c;		//y j
  double q22 = q2 * q2;

  double q3 = q.d;		//z k
  double q32 = q3 * q3;
  
  h->mtx[0][0] = 1.0 - (2.0 * (q22 + q32));
  h->mtx[0][1] =  2.0 * (q1 * q2  -  q0 * q3);
  h->mtx[0][2] =  2.0 * (q1 * q3  +  q0 * q2);

  h->mtx[1][0] =  2.0 * (q1 * q2  +  q0 * q3);
  h->mtx[1][1] = 1.0 - (2.0 * (q12 + q32));
  h->mtx[1][2] =  2.0 * (q2 * q3  -  q0 * q1);
  
  h->mtx[2][0] =  2.0 * (q1 * q3  -  q0 * q2);
  h->mtx[2][1] =  2.0 * (q2 * q3  +  q0 * q1);
  h->mtx[2][2] = 1.0 - (2.0 * (q12 + q22));

  return h;
}

void
Rotation::show (ostream& os, const Rotation *obj)
{
  double q00 = obj->mtx[0][0];
  double q01 = obj->mtx[0][1];
  double q02 = obj->mtx[0][2];
  double q10 = obj->mtx[1][0];
  double q11 = obj->mtx[1][1];
  double q12 = obj->mtx[1][2];
  double q20 = obj->mtx[2][0];
  double q21 = obj->mtx[2][1];
  double q22 = obj->mtx[2][2];

  os << "[[" << q00 << " " << q01 << "  " << q02 << "]  "
     <<  "[" << q10 << " " << q11 << "  " << q12 << "]  "
     <<  "[" << q20 << " " << q21 << "  " << q22 << "]]";
}

void
Rotation::show ()
{
  fprintf (stdout, "[[ %g %g %g]  ",
	   this->mtx[0][0], this->mtx[0][1], this->mtx[0][2]);
  fprintf (stdout, " [ %g %g %g]  ",
	   this->mtx[1][0], this->mtx[1][1], this->mtx[1][2]);
  fprintf (stdout, " [ %g %g %g]]\n",
	   this->mtx[2][0], this->mtx[2][1], this->mtx[2][2]);
}

Quat
Rotation:: toQuaternion ()
{
  return getEigens (this);
}

Quat
Quat::round (double e)
{
  Quat r;
  r.a = (fabs(a) < e) ? 0.0 : a;
  r.b = (fabs(b) < e) ? 0.0 : b;
  r.c = (fabs(c) < e) ? 0.0 : c;
  r.d = (fabs(d) < e) ? 0.0 : d;

  return r;
}

Quat
Quat::round ()
{
  return this->round (1e-9);
}

Quat
Quat::qexp ()
{
  double vmag = sqrt (pow (b, 2.0) + pow (c, 2.0) + pow (d, 2.0));
  double K = exp (a);
  double A = K * cos (vmag);
  double B, C, D;
  if (vmag != 0.0) {
    double svmag = sin (vmag) / vmag;
    B = K * svmag * b;
    C = K * svmag * c;
    D = K * svmag * d;
  }
  else B = C = D = 0.0;

  Quat s (A, B, C, D);
  return s;
}

Quat
Quat::qln ()
{
  double qmag = sqrt (pow (a, 2.0) + pow (b, 2.0) +
		      pow (c, 2.0) + pow (d, 2.0));
  double A = NAN;
  double B = NAN;
  double C = NAN;
  double D = NAN;
  if (qmag != 0.0) {
    double vmag = sqrt (pow (b, 2.0) + pow (c, 2.0) + pow (d, 2.0));
    if (vmag != 0.0) {
      double K = acos (a / qmag) / vmag;
      A = log (qmag);
      B = K * b;
      C = K * c;
      D = K * d;
    }
    else {
      A = log (a);
      B = 0.0;
      C = 0.0;
      D = 0.0;
    }
  }
  Quat s (A, B, C, D);
  return s;
}

Quat
Quat::qpow (double x)
{
  double A = NAN;
  double B = NAN;
  double C = NAN;
  double D = NAN;
  double qmag = sqrt (pow (a, 2.0) + pow (b, 2.0) +
		      pow (c, 2.0) + pow (d, 2.0));
  if (qmag != 0.0) {
    double phi = acos (a/qmag);
    double K = qmag * sin (phi);
    double K2 = pow (qmag, x);
    double cxp = cos (x * phi);
    double sxp = sin (x * phi);
    A  = K2 * cxp;
    if (K != 0.0) {
      B  = K2 * (b / K) * sxp;
      C  = K2 * (c / K) * sxp;
      D  = K2 * (d / K) * sxp;
    }
    else B = C = D = 0.0;
  }
  else A = B = C = D = 1.0;
  Quat s (A, B, C, D);
  return s;
}

void
Quat::show ()
{
  fprintf (stdout, "[ %g %g %g %g ]\n", a, b, c, d);
}

void
Quat::show (string l)
{
  fprintf (stdout, "%s = [ %g %g %g %g ]\n",
	   l.c_str (), a, b, c, d);
}
