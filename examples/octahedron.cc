#include <GLFW/glfw3.h>
#include <vector>
#include <Quat.hh>
#include "plato.hh"

#define SCALE 2.0
static bool scale_done = false;

vector<Quat> octahedron = {
  Quat (0.0,  1.0,  0.0,  0.0),	// 0
  Quat (0.0, -1.0,  0.0,  0.0),	// 1
  Quat (0.0,  0.0,  1.0,  0.0),	// 2
  Quat (0.0,  0.0, -1.0,  0.0), // 3
  Quat (0.0,  0.0,  0.0,  1.0), // 4
  Quat (0.0,  0.0,  0.0, -1.0), // 5
};

enum {
  VPX,
  VMX,
  VPY,
  VMY,
  VPZ,
  VMZ
};
  

extern double axes[][3];

void
draw_octahedron (double ang, int axisIndex)
{

  if (!scale_done) {
    scale_done = true;
    for (int i = 0; i < octahedron.size (); i++) {
      octahedron[i] /= SCALE;
    }
  }
  
  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (octahedron);
  
#define LEFT    rr[0].X (),  rr[0].Y (), rr[0].Z ()
#define RIGHT   rr[1].X (),  rr[1].Y (), rr[0].Z ()
#define TOP     rr[2].X (),  rr[2].Y (), rr[0].Z ()
#define BOTTOM  rr[3].X (),  rr[3].Y (), rr[0].Z ()
#define NEAR    rr[4].X (),  rr[4].Y (), rr[4].Z ()
#define FAR     rr[5].X (),  rr[5].Y (), rr[5].Z ()  

  glBegin (GL_TRIANGLES); 	// top left front
    glColor3d (1.0, 0.0, 0.0);	// red
    glVertex3d (TOP);
    glVertex3d (NEAR);
    glVertex3d (LEFT);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// top left back
  glColor3d (0.0, 1.0, 0.0);	// green
    glVertex3d (TOP);
    glVertex3d (LEFT);
    glVertex3d (FAR);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// top right back
  glColor3d (0.0, 0.0, 1.0);	// blue
    glVertex3d (TOP);
    glVertex3d (FAR);
    glVertex3d (RIGHT);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// top right front
  glColor3d (1.0, 1.0, 0.0);	// yellow
    glVertex3d (TOP);
    glVertex3d (RIGHT);
    glVertex3d (NEAR);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// bottom left front
  glColor3d (1.0, 0.0, 1.0);	// magenta
    glVertex3d (BOTTOM);
    glVertex3d (LEFT);
    glVertex3d (NEAR);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// bottom left back
  glColor3d (1.0, 0.5, 0.5);	// pink
    glVertex3d (BOTTOM);
    glVertex3d (LEFT);
    glVertex3d (FAR);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// bottom right back
  glColor3d (0.5, 0.5, 0.5);	// pink
    glVertex3d (BOTTOM);
    glVertex3d (FAR);
    glVertex3d (RIGHT);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// bottom right front
  glColor3d (0.5, 0.0, 0.0);	// brown
    glVertex3d (BOTTOM);
    glVertex3d (RIGHT);
    glVertex3d (NEAR);
  glEnd ();
  
};
