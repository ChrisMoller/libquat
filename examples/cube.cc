#include <GLFW/glfw3.h>
#include <vector>
#include <Quat.hh>

#include "plato.hh"

vector<Quat> cube = {
  Quat (0, -0.4,  0.4, -0.4),	// left  lower rear
  Quat (0,  0.4,  0.4, -0.4),	// right lower rear
  Quat (0,  0.4, -0.4, -0.4),	// right upper rear
  Quat (0, -0.4, -0.4, -0.4),	// left  upper rear
  Quat (0, -0.4,  0.4,  0.4),    // left  lower front
  Quat (0,  0.4,  0.4,  0.4),    // right lower front
  Quat (0,  0.4, -0.4,  0.4),    // right upper front
  Quat (0, -0.4, -0.4,  0.4)     // left  upper front
};

enum {
  VTX_LLR,
  VTX_RLR,
  VTX_RUR,
  VTX_LUR,
  VTX_LLF,
  VTX_RLF,
  VTX_RUF,
  VTX_LUF
};

extern double axes[][3];

#if 0
static double
getDir (int leg1, int corner, int leg2)
{
  Quat z_axis (0, 0, 0, 1);
  Quat cpa = cube[leg1] - cube[corner];
  Quat cpb = cube[leg2] - cube[corner];
  Quat cpx = cpa.qcross (cpb);
  return cpx.qdot (z_axis);
}
#endif

/***
                 LUR                    RUR
               /|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯/|
              / |                    / |
             /  |   top             /  |
            /   |                  /   |
       LUF /____|_________________/RUF |
           |    |                 |    |
           |    |        back     |    |
           |left|                 | rgt|
           |    |                 |    |
           |    |_LLR____________ |___ | RLR
           |   /                  |   /
           |  /                   |  /
           | /      bottom        | /
       LLF |/                     |/ RLF
           ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
***/

void
draw_cube (double ang, int axisIndex)
{
#if 0
  cout << "back   " << getDir (VTX_LLR, VTX_LUR, VTX_RUR) << endl;
  cout << "front  " << getDir (VTX_LLF, VTX_RLF, VTX_LUF) << endl;
  cout << "bottom " << getDir (VTX_LLR, VTX_RLR, VTX_RLF) << endl;
  cout << "top    " << getDir (VTX_LUR, VTX_RUR, VTX_RUF) << endl;
  cout << "left   " << getDir (VTX_LUR, VTX_LLR, VTX_LLF) << endl;
  cout << "right  " << getDir (VTX_RLR, VTX_RUR, VTX_RUF) << endl;
#endif

  enum {
    LLR,
    RLR,
    RUR,
    LUR,
    LLF,
    RLF,
    RUF,
    LUF
  };
  
  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (cube);

#if 0
  show_ang (0, rr, LUR, RUR, RLR);		// back
  show_ang (10, rr, RUR, RLR, LLR); 
  
  show_ang (1, rr, RUF, LUF, LLF);		// front
  show_ang (11, rr, LUF, LLF, RLF);

  show_ang (2, rr, RLF, LLF, LLR);		// bottom
  show_ang (12, rr, LLF, LLR, RLR);
  
  show_ang (3, rr, RUF, LUF, LUR);		//top
  show_ang (13, rr, LUF, LUR, RUR);
  
  show_ang (4, rr, LUF, LUR, LLR);		// left
  show_ang (14, rr, LUR, LLR, LLF);
  
  show_ang (5, rr, RUR, RUF, RLF);		// right
  show_ang (15, rr, RUF, RLF, RLR);
#endif

#define LEFT__LOWER_REAR  rr[0].X (),  rr[0].Y (), rr[0].Z ()
#define RIGHT_LOWER_REAR  rr[1].X (),  rr[1].Y (), rr[0].Z ()
#define RIGHT_UPPER_REAR  rr[2].X (),  rr[2].Y (), rr[0].Z ()
#define LEFT__UPPER_REAR  rr[3].X (),  rr[3].Y (), rr[0].Z ()
#define LEFT__LOWER_FRONT rr[4].X (),  rr[4].Y (), rr[4].Z ()
#define RIGHT_LOWER_FRONT rr[5].X (),  rr[5].Y (), rr[5].Z ()  
#define RIGHT_UPPER_FRONT rr[6].X (),  rr[6].Y (), rr[6].Z ()
#define LEFT__UPPER_FRONT rr[7].X (),  rr[7].Y (), rr[7].Z ()

  const float green[]   = {0.0f, 1.0f, 0.0f, 1.0f};
  const float magenta[] = {1.0f, 0.0f, 1.0f, 1.0f};
  const float black[]   = {0.0f, 0.0f, 0.0f, 1.0f};
#if 1
  glBegin (GL_QUADS);			// back
  glColor3f (1.0f, 0.0f, 0.0f);
  glVertex3d (LEFT__UPPER_REAR);
  glVertex3d (RIGHT_UPPER_REAR);
  glVertex3d (RIGHT_LOWER_REAR);
  glVertex3d (LEFT__LOWER_REAR);
  glEnd ();
  
  glBegin (GL_QUADS);			// front
  glColor3f (0.0f, 1.0f, 1.0f);
  glVertex3d (RIGHT_UPPER_FRONT);
  glVertex3d (LEFT__UPPER_FRONT);
  glVertex3d (LEFT__LOWER_FRONT);
  glVertex3d (RIGHT_LOWER_FRONT);
  glEnd ();
#endif

#if 1
  glBegin (GL_QUADS);			// bottom
  glColor3f (0.0f, 1.0f, 0.0f);
  glVertex3d (RIGHT_LOWER_FRONT);
  glVertex3d (LEFT__LOWER_FRONT);
  glVertex3d (LEFT__LOWER_REAR);
  glVertex3d (RIGHT_LOWER_REAR);
  glEnd ();

  glBegin (GL_QUADS);			//  top
  glColor3f (1.0f, 0.0f, 1.0f);
  glVertex3d (RIGHT_UPPER_FRONT);
  glVertex3d (LEFT__UPPER_FRONT);
  glVertex3d (LEFT__UPPER_REAR);
  glVertex3d (RIGHT_UPPER_REAR);
  glEnd ();
#endif

#if 1
  glBegin (GL_QUADS);			//  left
  glColor3f (0.0f, 0.0f, 1.0f);
  glVertex3d (LEFT__UPPER_FRONT);
  glVertex3d (LEFT__UPPER_REAR);
  glVertex3d (LEFT__LOWER_REAR);
  glVertex3d (LEFT__LOWER_FRONT);
  glEnd ();

  glBegin (GL_QUADS);			// right
  glColor3f (1.0f, 1.0f, 0.0f);
  glVertex3d (RIGHT_UPPER_REAR);
  glVertex3d (RIGHT_UPPER_FRONT);
  glVertex3d (RIGHT_LOWER_FRONT);
  glVertex3d (RIGHT_LOWER_REAR);
  glEnd();
#endif
};
