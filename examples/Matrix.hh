#ifndef MATRIX_HH
#define MATRIX_HH

#include <stdio.h>
#include<cmath>
#include<math.h>
#include<values.h>
#include<vector>

using namespace std;

class Matrix
{
public:
  Matrix (int r, int c);
  ~Matrix ();
  double val (int r, int c);
  void val (int r, int c, double v);
  int  rows ();
  int  cols ();
  void show ();
  double det ();
  Matrix *cofactor (int r, int c);

private:
  int krows;
  int kcols;
  vector<double> *vals;
};

#endif  // MATRIX_HH
