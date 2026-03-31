#include <GLFW/glfw3.h>
#include <vector>
#include <Quat.hh>

extern GLdouble axes[][3];
void
draw_icosahedron (GLdouble ang, int axisIndex)
{
vector<Quat> icosahedron = {
  Quat (0.0, 1, 0.323607, 0),
  Quat (0.0, -1, 0.323607, 0),
  Quat (0.0, 1, -0.323607, 0),
  Quat (0.0, -1, -0.323607, 0),
  Quat (0.0, 0, 1, 0.323607),
  Quat (0.0, 0, -1, 0.323607),
  Quat (0.0, 0, 1, -0.323607),
  Quat (0.0, 0, -1, -0.323607),
  Quat (0.0, 0.323607, 0, 1),
  Quat (0.0, -0.323607, 0, 1),
  Quat (0.0, 0.323607, 0, -1),
  Quat (0.0, -0.323607, 0, -1),
};
  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (icosahedron);
#define VERT_00  rr[0].X (),  rr[0].Y (), rr[0].Z ()
#define VERT_01  rr[1].X (),  rr[1].Y (), rr[1].Z ()
#define VERT_02  rr[2].X (),  rr[2].Y (), rr[2].Z ()
#define VERT_03  rr[3].X (),  rr[3].Y (), rr[3].Z ()
#define VERT_04  rr[4].X (),  rr[4].Y (), rr[4].Z ()
#define VERT_05  rr[5].X (),  rr[5].Y (), rr[5].Z ()
#define VERT_06  rr[6].X (),  rr[6].Y (), rr[6].Z ()
#define VERT_07  rr[7].X (),  rr[7].Y (), rr[7].Z ()
#define VERT_08  rr[8].X (),  rr[8].Y (), rr[8].Z ()
#define VERT_09  rr[9].X (),  rr[9].Y (), rr[9].Z ()
#define VERT_10  rr[10].X (),  rr[10].Y (), rr[10].Z ()
#define VERT_11  rr[11].X (),  rr[11].Y (), rr[11].Z ()

  glBegin (GL_TRIANGLES); // t 0
    glColor3d (0.898438, 0.0976562, 0.292969);
    glVertex3d (VERT_04);
    glVertex3d (VERT_00);
    glVertex3d (VERT_08);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 1
    glColor3d (0.234375, 0.703125, 0.292969);
    glVertex3d (VERT_08);
    glVertex3d (VERT_00);
    glVertex3d (VERT_02);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 2
    glColor3d (0.996094, 0.878906, 0.0976562);
    glVertex3d (VERT_00);
    glVertex3d (VERT_02);
    glVertex3d (VERT_05);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 3
    glColor3d (0.261719, 0.386719, 0.84375);
    glVertex3d (VERT_00);
    glVertex3d (VERT_05);
    glVertex3d (VERT_09);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 4
    glColor3d (0.957031, 0.507812, 0.191406);
    glVertex3d (VERT_00);
    glVertex3d (VERT_09);
    glVertex3d (VERT_04);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 5
    glColor3d (0.566406, 0.117188, 0.703125);
    glVertex3d (VERT_01);
    glVertex3d (VERT_03);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 6
    glColor3d (0.257812, 0.828125, 0.953125);
    glVertex3d (VERT_11);
    glVertex3d (VERT_01);
    glVertex3d (VERT_07);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 7
    glColor3d (0.9375, 0.195312, 0.898438);
    glVertex3d (VERT_01);
    glVertex3d (VERT_07);
    glVertex3d (VERT_06);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 8
    glColor3d (0.746094, 0.933594, 0.269531);
    glVertex3d (VERT_06);
    glVertex3d (VERT_01);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 9
    glColor3d (0.976562, 0.742188, 0.828125);
    glVertex3d (VERT_10);
    glVertex3d (VERT_01);
    glVertex3d (VERT_03);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 10
    glColor3d (0.273438, 0.597656, 0.5625);
    glVertex3d (VERT_08);
    glVertex3d (VERT_02);
    glVertex3d (VERT_05);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 11
    glColor3d (0.859375, 0.742188, 0.996094);
    glVertex3d (VERT_05);
    glVertex3d (VERT_02);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 12
    glColor3d (0.601562, 0.386719, 0.140625);
    glVertex3d (VERT_10);
    glVertex3d (VERT_05);
    glVertex3d (VERT_09);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 13
    glColor3d (0.996094, 0.976562, 0.78125);
    glVertex3d (VERT_05);
    glVertex3d (VERT_09);
    glVertex3d (VERT_08);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 14
    glColor3d (0.5, 0, 0);
    glVertex3d (VERT_11);
    glVertex3d (VERT_03);
    glVertex3d (VERT_07);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 15
    glColor3d (0.664062, 0.996094, 0.761719);
    glVertex3d (VERT_03);
    glVertex3d (VERT_07);
    glVertex3d (VERT_06);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 16
    glColor3d (0.5, 0.5, 0);
    glVertex3d (VERT_06);
    glVertex3d (VERT_03);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 17
    glColor3d (0.996094, 0.84375, 0.691406);
    glVertex3d (VERT_03);
    glVertex3d (VERT_10);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 18
    glColor3d (0, 0, 0.457031);
    glVertex3d (VERT_04);
    glVertex3d (VERT_08);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 19
    glColor3d (0.660156, 0.660156, 0.660156);
    glVertex3d (VERT_04);
    glVertex3d (VERT_11);
    glVertex3d (VERT_07);
  glEnd ();
}
