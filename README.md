# Quaternions
Quaternions is a small library that implements quaternion algebra.

A quaternion is a four-element vector that encodes a scalar value and a
3-space directional vector in the form of

&nbsp;&nbsp;&nbsp;&nbsp;[s $a_0$**i** $a_1$**j** $a_2$**k**]

where the elements of vector $a$ are real.  Quaternions have a fair number of
applications, but my use of them are in 3-space rotations in computer graphics.

For the most part this library just overloads all the applicable C++ operators
such that quaternion + quaternion yields a quaternion, and so on.

### Constructors

| Constructor |     |construction |
| ----------- | --- |------------ |
| Quat () | $\Rightarrow$ | null quaternion [0 0 0 0] |
| Quat (double s) | $\Rightarrow$ | scalar quaternion [s 0 0 0] |
| Quat (double s, double a0, double a1, double a2) | $\Rightarrow$ | complete quaternion [s a0 a1 a2] |

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
| Quat operator*=(Quat &v);   | $\Rightarrow$ | Quat *= Quat $\rightarrow$ Quat |
| Quat operator*=(double &v); | $\Rightarrow$ | Quat *= double $\rightarrow$ Quat |
| Quat operator/=(Quat &v);   | $\Rightarrow$ | Quat /= Quat $\rightarrow$ Quat |
| Quat operator/=(double &v); | $\Rightarrow$ | Quat /= double $\rightarrow$ Quat |

## Simple monadics

| operation |     | effect |
| --------- | --- | ------ |
| Quat          operator*();   | $\Rightarrow$ | conjugation: [s $-a_0$ $-a_1$ $-a_2$] |
| Quat          operator+();   | $\Rightarrow$ | norm: (magnitide) |
| Quat          operator-();   | $\Rightarrow$ | negation: [-s $-a_0$ $-a_1$ $-a_2$] |
| Quat          operator~();   | $\Rightarrow$ | invertion: $q^{-1}$ |

These operators don't follow standard C++ significance.  C++ has no conjugation operator--but
quaternions don't need a dereferencing operator, so I've mapped '*' to conjugation.  Similarly,
C++ has no monadic '|', which might have been good as a magnitude operator, but monadic
'+' isn't relevant to quaternions so is mappped to magnitude.  Similarly, '~' is mapped to
invert. 

## Simple comparisons

| operation |     | effect |
| --------- | --- | ------ |
| bool          operator==(Quat v); | $\Rightarrow$ | equal |
| bool          operator!=(Quat v); | $\Rightarrow$ | not equal |

The above are just what I've found I need, so far, for graphics work, but if anyone needs
anything else, I'll be glad to add it.

## Simple comparisons

| operation |     | effect |
| --------- | --- | ------ |
| double Quat::qdot (Quat &a, Quat &b);; | $\Rightarrow$ | dot-product |
| double Quat::qang (Quat &a, Quat &b);; | $\Rightarrow$ | angle subtended by the argument quats |
| Quat Quat::qcross (Quat &a, Quat &b);; | $\Rightarrow$ | cross-product |

## Examples

test.cc tests all of the above and can be used as boilerplate for usage.  rot.cc is a testcase
for 3-space rotation.


