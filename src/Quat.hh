
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

#pragma once

#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <complex>
using namespace std;

#include <stdio.h>


// quat <> mx conversion
// https://www.johndcook.com/blog/2025/05/07/quaternions-and-rotation-matrices/
// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
// https://math.stackexchange.com/questions/893984/conversion-of-rotation-matrix-to-quaternion

// https://en.wikipedia.org/wiki/Quaternion

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

class Quat;

class Rotation
{
public:
  double mtx[3][3];
  void show ();
  Quat	toQuaternion ();
  static void show (ostream& os, const Rotation *obj);
  friend ostream& operator<<(ostream& os, const Rotation *obj) {
    Rotation::show (os, obj);
    return os; // Enable chaining
  }
};

class Quat
{
public:
  Quat ();
  Quat (double ai, double bi, double ci, double di);
  Quat (double ai);
  Quat (double *v);
  Quat (double theta, double *v);

  double scalar () {return a;}
  double W () {return a;}
  double X () {return b;}
  double Y () {return c;}
  double Z () {return d;}
  ~Quat ();

  Quat 		operator+(Quat v);	// add
  Quat 		operator+=(Quat &v);	// add-assign

  Quat 		operator-(Quat v);	// subtract
  Quat 		operator-=(Quat &v);	// subtract-assign

  Quat 		operator*(Quat v);	// multiply
  Quat 		operator*=(Quat &v);	// multiply-assign
  Quat 		operator*(const double v);	// multiply by double
  Quat		operator*=(const double v);  // multiply by double assign

  Quat 		operator/(Quat v);	// divide
  Quat 		operator/=(Quat &v);	// divide-assign
  Quat 		operator/(double v);	// divide by double
  Quat		operator/=(const double v);  // divide double assign

  // I'm using monadic * because quaternions have no use for
  // a dereference operator
  Quat		operator*();		// conjugation

  double	operator+();		// norm

  Quat		operator-();		// negation

  // Note that c++ doesn't support monadic / which would have made more sense,
  // so I'm using monadic tilde (~) because quaternions have no use for a
  // complement operator
  Quat		operator~();		// reciprocal

  bool		operator==(Quat v);	// eq

  bool		operator!=(Quat v);	// neq

  string	qstr ();		// stringify
  double *      qvec ();		// convert to array
  double *      qaxis ();		// extract axis component
  double        qscalar ();		// extract scalar component

  double	qdot (Quat &v);
  Quat		qcross (Quat &v);
  double	qang (Quat &v);
  Quat		qrot (const Quat v);		// v.qrot (w) rotate v by w
  vector<Quat>	qrot (vector<Quat> &v);	// v.qrot (w) rotate v by w
  
  Rotation	*toRotation ();

  Quat		round (double e);	// basically, floor
  Quat		round ();		// basically, floor

  Quat		qexp ();
  Quat		qln ();
  Quat		qpow (double x);

  friend ostream& operator<<(ostream& os, const Quat &v);

  void show ();
  void show (string l);

private:
  double a;
  double b;
  double c;
  double d;
};
