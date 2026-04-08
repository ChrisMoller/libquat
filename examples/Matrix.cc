
#include "Matrix.hh"

Matrix::Matrix (int r, int c)
{
  krows = r;
  kcols = c;
  vals = new vector<double>(r * c);
}

Matrix::~Matrix ()
{
  delete vals;
}

double
Matrix::val (int r, int c)
{
  double rc = 0.0;
  rc = (*vals)[c + r * kcols];
  return rc;
}

void
Matrix::val (int r, int c, double v)
{
  (*vals)[c + r * kcols] = v;
}

int
Matrix::rows ()
{
  return krows;
}


int
Matrix::cols ()
{
  return kcols;
}

Matrix *
Matrix::cofactor (int r, int c)
{     
  Matrix *cf = new Matrix (this->rows ()-1, this->cols ()-1);

  int rx = 0;
  for (int rr = 0; rr < this->rows (); rr++) {
    if (rr != r) {
      int cx = 0;
      for (int cc = 0; cc < this->cols (); cc++) {
        if (cc != c) {
          cf->val (rx, cx++, this->val (rr, cc));
        }
      }
      rx++;
    }   
  }
  
  return cf;
} 
  
double
Matrix::det ()
{
  double v = NAN;

  if (this->rows () == 2)
    v = (this->val (0, 0) * this->val (1,1)) -
           (this->val (0, 1) * this->val (1,0));
  else {
    for (int k = 0; k < this->rows (); k++) {
      double sign = pow (-1.0, (double)(k));
      Matrix *cf = this->cofactor (0, k);
      double id = cf->det ();
      delete cf;
      v += sign * this->val (0, k) * id;
    }
  }
  
  return v;
}

void
Matrix::show ()
{
  for (int r = 0; r < krows; r++) {
    for (int c = 0; c < kcols; c++) {
      fprintf (stderr, "%g ", this->val (r, c));
    }
    fprintf (stderr, "\n");
  }
}
   
