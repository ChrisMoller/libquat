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

#if 0
bool done_it = false;
#endif

void
draw_octahedron (double ang, int axisIndex)
{

  if (!scale_done) {
    scale_done = true;
    for (int i = 0; i < octahedron.size (); i++) {
      octahedron[i] /= SCALE;
    }
  }
#if 0
  if (!done_it) {
    done_it = true;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
	for (int k = 0; k < 6; k++) {
	  if ((j != i) && (k != i) && (k != j)) {
	    show_ang (i, j, k, octahedron, i, j, k);
	  }
	}
      }
    }
  }
  exit (1);
#endif
  
  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (octahedron);
  
#define VERT_00 rr[0].X (),  rr[0].Y (), rr[0].Z ()
#define VERT_01 rr[1].X (),  rr[1].Y (), rr[0].Z ()
#define VERT_02 rr[2].X (),  rr[2].Y (), rr[0].Z ()
#define VERT_03 rr[3].X (),  rr[3].Y (), rr[0].Z ()
#define VERT_04 rr[4].X (),  rr[4].Y (), rr[4].Z ()
#define VERT_05 rr[5].X (),  rr[5].Y (), rr[5].Z ()  

  glBegin (GL_TRIANGLES); 	// 1 top left front
    glColor3d (1.0, 0.0, 0.0);	// red
    glVertex3d (VERT_00);
    glVertex3d (VERT_02);
    glVertex3d (VERT_04);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 2 top left front
  glColor3d (0.0, 1.0, 0.0);	// green
    glVertex3d (VERT_00);
    glVertex3d (VERT_02);
    glVertex3d (VERT_05);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 3 top left front
  glColor3d (0.0, 0.0, 1.0);	// blue
    glVertex3d (VERT_00);
    glVertex3d (VERT_03);
    glVertex3d (VERT_04);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 4 top left front
  glColor3d (1.0, 1.0, 0.0);	// yellow
    glVertex3d (VERT_00);
    glVertex3d (VERT_03);
    glVertex3d (VERT_05);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 5 top left front
  glColor3d (1.0, 0.0, 1.0);	// magenta
    glVertex3d (VERT_01);
    glVertex3d (VERT_02);
    glVertex3d (VERT_04);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 6 top left front
  glColor3d (1.0, 0.5, 0.5);	// pink
    glVertex3d (VERT_01);
    glVertex3d (VERT_02);
    glVertex3d (VERT_05);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 7 top left front
  glColor3d (0.5, 0.5, 0.5);	// grey
    glVertex3d (VERT_01);
    glVertex3d (VERT_03);
    glVertex3d (VERT_04);
  glEnd ();

  glBegin (GL_TRIANGLES); 	// 7 top left front
  glColor3d (0.5, 0.0, 0.0);	// brown
    glVertex3d (VERT_01);
    glVertex3d (VERT_03);
    glVertex3d (VERT_05);
  glEnd ();

};
