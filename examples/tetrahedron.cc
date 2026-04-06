#include <GLFW/glfw3.h>
#include <vector>
#include <Quat.hh>

#include "plato.hh"

#define SCALE 2.0
static bool scale_done = false;

vector<Quat> tetrahedron = {
  Quat (0,  1.0,  0.0, -M_SQRT1_2),	// 0 near right
  Quat (0, -1.0,  0.0, -M_SQRT1_2),	// 1 near left
  Quat (0,  0.0,  1.0,  M_SQRT1_2),	// 2 far top
  Quat (0,  0.0, -1.0,  M_SQRT1_2),	// 3 fat bottom
};

extern double axes[][3];

enum {
  VTX_NR,
  VTX_NL,
  VTX_FT,
  VTX_FB,
};

void
draw_tetrahedron (double ang, int axisIndex)
{

  if (!scale_done) {
    scale_done = true;
    for (int i = 0; i < tetrahedron.size (); i++) {
      tetrahedron[i] /= SCALE;
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
  vector<Quat> rr = rotator.qrot (tetrahedron);

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
