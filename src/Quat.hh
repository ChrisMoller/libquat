
/*
    libquat Copyright (C) 2025  C. H. L. Moller under the terms of the
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

#include <stdio.h>

static void set_makeexp ();

using namespace std;

class Quat
{
public:
  Quat ();
  Quat (double ai, double bi, double ci, double di);
  Quat (double ai);
  ~Quat ();
  
  Quat 		operator+(Quat v);	// add
  Quat 		operator+=(Quat &v);	// add-assign

  Quat 		operator-(Quat v);	// subtract
  Quat 		operator-=(Quat &v);	// subtract-assign

  Quat 		operator*(Quat v);	// multiply
  Quat 		operator*=(Quat &v);	// multiply-assign
  Quat 		operator*(double v);	// multiply by double
  Quat 		operator*=(double &v);	// multiply by double assign

  Quat 		operator/(Quat v);	// divide
  Quat 		operator/=(Quat &v);	// divide-assign
  Quat 		operator/(double v);	// divide by double

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
#if 0
  static string	qstr (Quat v);		// stringify
#endif

  
  friend ostream& operator<<(ostream& os, const Quat &v);

#if 0
  static double	qdot (Quat &a, Quat &b);
  static Quat	qcross (Quat &a, Quat &b);
  static double	qang (Quat &a, Quat &b);
#endif

  double	qdot (Quat &v);
  Quat		qcross (Quat &v);
  double	qang (Quat &v);
  Quat		qxform (Quat &v);

  void show ();
  void show (string l);
private:
  double a;
  double b;
  double c;
  double d;
};
