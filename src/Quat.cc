
/*
    aplquat Copyright (C) 2025  Dr C. H. L. Moller under the terms of the
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
#include <vector>

#include "Quat.hh"

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

Quat::Quat (vector<double> v)
{
  try {
    if (v.size () == 3) {
      a = 0.0;
      b = v[0];
      c = v[1];
      d = v[2];
    }
    else if (v.size () == 4) {
      a = v[0];
      b = v[1];
      c = v[2];
      d = v[3];
    }
    else
      throw 1;
  }
  catch(...) {
    cerr << "invalid vector size in constructor\n";
  }
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
Quat::operator+=(Quat v)	// add-assign
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
Quat::operator-=(Quat v)	// subtract-assign
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
Quat::operator*=(Quat v)	// multiply-assign
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
Quat::operator*(double v)	// multiply by double
{
  Quat s;
  s.a = a * v;
  s.b = b * v;
  s.c = c * v;
  s.d = d * v;
  return s;
}

Quat
Quat::operator*=(double v)	// multiply by double assign
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
Quat::operator/=(Quat v)	// divide-assign
{
  Quat s = ~v;			// invert denominator
  Quat t = *this * s;
  *this = t;
  return t;
}

Quat
Quat::operator/(double v)	// divide by double
{
  Quat s;
  s.a = a / v;
  s.b = b / v;
  s.c = c / v;
  s.d = d / v;
  return s;
}

Quat
Quat::operator/=(double v)	// multiply by double assign
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

vector<double>
Quat::qvec ()			// convert to array
{
  vector<double> v = {0.0, 0.0, 0.0, 0.0};
  v[0] = a;
  v[1] = b;
  v[2] = c;
  v[3] = d;
  return v;
}

vector<double>
Quat::qaxis ()			// extract axis component
{
  vector<double> v = {0.0, 0.0, 0.0};
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
Quat::qdot (Quat v)
{
  return (b * v.b) + (c * v.c) + (d * v.d);
}

Quat
Quat::qcross (Quat v)
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
  double dt = (a * v.a) + (b * v.b) + (c * v.c) + (d * v.d);
  return acos (dt / ((+*this) * +v));
}

Quat
Quat::qrot (Quat v)
{
  Quat q =  (*this) * v * ~(*this);
  return q;
}

#define R2D(r) (180.0 * (r)/M_PI)

vector<Quat>
Quat::qfan (int n, Quat v, Quat w)
{
  vector<Quat> fan;

  double baseAngle =  v.qang (w) / 2.0;
  vector<double> axis = (v.qcross (w)).qvec ();
  
  double magAxis = 0.0;			// get axis magnitude
  for (int i = 1; i < 4; i++)
    magAxis += axis[i] * axis[i];
  magAxis = sqrt (magAxis);

  if (n >= 1 || magAxis > 0.0) {
    for (int i = 1; i < 4; i++)		// normalise axis
      axis[i] /= magAxis;
    for (int i = 0; i <= n; i++) {
      double angle = ((double)i/(double(n))) *  baseAngle;
      double cosAngle = cos (angle);
      double sinAngle = sin (angle);
      
      vector<double> q = {cosAngle, 0.0, 0.0, 0.0};		// initialise q
      for (int i = 1; i < 4; i++)
	q[i] = axis[i] * sinAngle;

      Quat qq (q);
      
      Quat res = qq * v / qq;
      fan.push_back (res);
    }
  }
  else {
    fan.push_back (v);
  }

  return fan;
}

/*  diagnostic stuff */

string
Quat::qstr ()			// stringify
{
  char *s;
  asprintf (&s, "[%#08g [%#08g %#08g %#08g]]", a, b, c, d);
  string t (s);
  free (s);
  return t;
}

void
Quat::show ()
{
  fprintf (stdout, "[ %g %g %g %g ]\n",
	   this->a,
	   this->b,
	   this->c,
	   this->d);
}

void
Quat::show (string l)
{
  fprintf (stdout, "%s = [ %g %g %g %g ]\n",
	   l.c_str (),
	   this->a,
	   this->b,
	   this->c,
	   this->d);
}
