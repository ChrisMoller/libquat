#include <GLFW/glfw3.h>
#include <vector>
#include <Quat.hh>

#include "plato.hh"

#define  PHI 1.618033989
#define IPHI 0.618033989

#define SCALE 2.0
static bool scale_done = false;

vector<Quat> dodecahedron = {
  Quat (0,  1.0,  1.0,  1.0),	// 0
  Quat (0,  1.0,  1.0, -1.0),	// 1
  Quat (0,  1.0, -1.0,  1.0),	// 2
  Quat (0,  1.0, -1.0, -1.0),	// 3
  Quat (0, -1.0,  1.0,  1.0),	// 4
  Quat (0, -1.0,  1.0, -1.0),	// 5
  Quat (0, -1.0, -1.0,  1.0),	// 6
  Quat (0, -1.0, -1.0, -1.0),	// 7
};

extern double axes[][3];

enum {
  VTX_NR,
  VTX_NL,
  VTX_FT,
  VTX_FB,
};

void
draw_dodecahedron (double ang, int axisIndex)
{

  if (!scale_done) {
    scale_done = true;
    for (int i = 0; i < dodecahedron.size (); i++) {
      dodecahedron[i] /= SCALE;
    }
  }
  
#if 0
  show_ang (0, rr, LUR, RUR, RLR);		// back
  show_ang (10, rr, RUR, RLR, LLR); 
  
  show_ang (1, rr, RUF, LUF, LLF);		// front
  show_ang (11, rr, LUF, LLF, RLF);

  show_ang (2, rr, RLF, LLF, LLR);		// bottom
  show_ang (12, rr, LLF, LLR, RLR);
  
  show_ang (3, rr, RUF, LUF, LUR);		// top
  show_ang (13, rr, LUF, LUR, RUR);
  
  show_ang (4, rr, LUF, LUR, LLR);		// left
  show_ang (14, rr, LUR, LLR, LLF);
  
  show_ang (5, rr, RUR, RUF, RLF);		// right
  show_ang (15, rr, RUF, RLF, RLR);
#endif

  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (dodecahedron);

#define NEAR_RIGHT  rr[VTX_NR].X (),  rr[VTX_NR].Y (), rr[VTX_NR].Z ()
#define NEAR_LEFT   rr[VTX_NL].X (),  rr[VTX_NL].Y (),  rr[VTX_NL].Z ()
#define FAR_TOP     rr[VTX_FT].X (),  rr[VTX_FT].Y (),  rr[VTX_FT].Z ()
#define FAR_BOTTOM  rr[VTX_FB].X (),  rr[VTX_FB].Y (),  rr[VTX_FB].Z ()

  glBegin (GL_TRIANGLES);			// front
  glColor3f (1.0f, 0.0f, 0.0f);
  glVertex3d (FAR_TOP);
  glVertex3d (NEAR_LEFT);
  glVertex3d (NEAR_RIGHT);
  glEnd ();
  
  glBegin (GL_TRIANGLES);			// left
  glColor3f (0.0f, 1.0f, 1.0f);
  glVertex3d (FAR_TOP);
  glVertex3d (FAR_BOTTOM);
  glVertex3d (NEAR_LEFT);
  glEnd ();

  glBegin (GL_TRIANGLES);			// right
  glColor3f (0.0f, 1.0f, 0.0f);
  glVertex3d (FAR_TOP);
  glVertex3d (NEAR_RIGHT);
  glVertex3d (FAR_BOTTOM);
  glEnd ();

  glBegin (GL_TRIANGLES);			// bottom
  glColor3f (1.0f, 0.0f, 1.0f);
  glVertex3d (NEAR_RIGHT);
  glVertex3d (NEAR_LEFT);
  glVertex3d (FAR_BOTTOM);
  glEnd ();

};
