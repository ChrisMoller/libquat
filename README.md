# libquat
libquat is a small library that implements quaternion algebra.

A quaternion is a four-element vector that encodes a scalar value and a
3-space directional vector in the form of

&nbsp;&nbsp;&nbsp;&nbsp;[s $a_0$**i** $a_1$**j** $a_2$**k**]

where the elements of the vector are real.  Quaternions have a fair number of
applications, but my use of them are in 3-space rotations in computer graphics.

For the most part this library just overloads all the applicable C++ operators
such that quaternion + quaternion yields a quaternion, and so on.

### Constructors

| Constructor |     |construction |
| ----------- | --- |------------ |
| Quat () | $\Rightarrow$ | null quaternion [0 0 0 0] |
| Quat (double s) | $\Rightarrow$ | scalar quaternion [s 0 0 0] |
| Quat (double s, double a0, double a1, double a2) | $\Rightarrow$ | mplete quaternion [s a0 a1 a2] |

### Simple arithmetic

| operation |     | effect |
| --------- | --- | ------ |
| Quat operator+(Quat v);   | $\Rightarrow$ | Quat + Quat $\rightarrow$ Quat |
| Quat operator-(Quat v);   | $\Rightarrow$ | Quat - Quat $\rightarrow$ Quat |
| Quat operator*(Quat v);   | $\Rightarrow$ | Quat * Quat $\rightarrow$ Quat |
| Quat operator*(double v); | $\Rightarrow$ | Quat * double $\rightarrow$ Quat |
| Quat operator/(Quat v);   | $\Rightarrow$ | Quat / Quat $\rightarrow$ Quat |
| Quat operator/(double v); | $\Rightarrow$ | Quat / double $\rightarrow$ Quat |

### Assignment

| operation |     | effect |
| --------- | --- | ------ |
| Quat operator+=(Quat &v);   | $\Rightarrow$ | Quat += Quat $\rightarrow$ Quat |
| Quat operator-=(Quat &v);   | $\Rightarrow$ | Quat -= Quat $\rightarrow$ Quat |
| Quat operator*=(Quat &v);   | $\Rightarrow$ | Quat *= Quat $\rightarrow$ Quat |
| Quat operator*=(double &v); | $\Rightarrow$ | Quat *= double $\rightarrow$ Quat |
| Quat operator/=(Quat &v);   | $\Rightarrow$ | Quat /= Quat $\rightarrow$ Quat |
| Quat operator/=(double &v); | $\Rightarrow$ | Quat /= double $\rightarrow$ Quat |

## Simple monadics

| operation |     | effect |
| --------- | --- | ------ |
| Quat          operator*();   | $\Rightarrow$ | conjugation: [s $-a_0$ $-a_1$ $-a_2$] |
| Quat          operator+();   | $\Rightarrow$ | norm: \|\| q \|\| |
| Quat          operator-();   | $\Rightarrow$ | negation: [-s $-a_0$ $-a_1$ $-a_2$] |
| Quat          operator~();   | $\Rightarrow$ | inversion: $q^{-1}$ |

These operators don't follow standard C++ significance.  C++ has no
conjugation operator--but quaternions don't need a dereferencing operator, so
I've mapped '*' to conjugation.  Similarly, C++ has no monadic '|', which
might have been good as a magnitude operator, but monadic '+' isn't relevant
to quaternions so is mappped to magnitude.  Similarly, '~' (tilde) is mapped
to invert.

## Simple comparisons

| operation |     | effect |
| --------- | --- | ------ |
| bool          operator==(Quat v); | $\Rightarrow$ | equal |
| bool          operator!=(Quat v); | $\Rightarrow$ | not equal |

The above are just what I've found I need, so far, for graphics work, but if anyone needs
anything else, I'll be glad to add it.

## Miscellaneous

| operation |     | effect |
| --------- | --- | ------ |
| double qdot (Quat &a);; | $\Rightarrow$ | dot-product |
| double qang (Quat &a);; | $\Rightarrow$ | angle subtended by the argument quats |
| Quat qcross (Quat &a);; | $\Rightarrow$ | cross-product |
| Quat qxform (Quat &a);; | $\Rightarrow$ | transform* |

* qxform returns a transform Quat that, applied to *this will yield Quat a.  Among the
uses of this is looping the transform with the scalar component incremented from 0.0 to
the returned scalar value results in a smooth transition from *this to Quat a;

## Examples

quattest.cc tests all of the above and can be used as boilerplate for usage.
./quattest -a dumps all the tests.  (That was the basis for the "make check" expects
file.)  rot.cc is a testcase for 3-space rotation.

## Installation

./autogen.sh

make

sudo make install



