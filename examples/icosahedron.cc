#include <GLFW/glfw3.h>
#ifdef USE_FTGL
#include <FTGL/ftgl.h>
#include <glm/glm.hpp>
#endif
#include <vector>
#include <Quat.hh>

#include "plato.hh"

#ifdef USE_FTGL
using namespace FTGL;
#endif

extern GLdouble axes[][3];

#ifdef USE_FTGL
extern double x_off;
extern double y_off;
extern double z_off;
#endif

#define PHI  1.618033989

#define SCALE 3.0
static bool scale_done = false;


vector<Quat> icosahedron = {
  Quat (0.0,  0.0,  1.0,  PHI),		//  0
  Quat (0.0,  0.0,  1.0, -PHI),		//  1
  Quat (0.0,  0.0, -1.0,  PHI),		//  2
  Quat (0.0,  0.0, -1.0, -PHI),		//  3
  Quat (0.0,  1.0,  PHI,  0.0),		//  4
  Quat (0.0,  1.0, -PHI,  0.0),		//  5
  Quat (0.0, -1.0,  PHI,  0.0),		//  6
  Quat (0.0, -1.0, -PHI,  0.0),		//  7
  Quat (0.0,  PHI,  0.0,  1.0),		//  8
  Quat (0.0, -PHI,  0.0,  1.0),		//  9
  Quat (0.0,  PHI,  0.0, -1.0),		// 10
  Quat (0.0, -PHI,  0.0, -1.0),		// 11
};

#define VERT_00  rr[0].X (),   rr[0].Y (),  rr[0].Z ()
#define VERT_01  rr[1].X (),   rr[1].Y (),  rr[1].Z ()
#define VERT_02  rr[2].X (),   rr[2].Y (),  rr[2].Z ()
#define VERT_03  rr[3].X (),   rr[3].Y (),  rr[3].Z ()
#define VERT_04  rr[4].X (),   rr[4].Y (),  rr[4].Z ()
#define VERT_05  rr[5].X (),   rr[5].Y (),  rr[5].Z ()
#define VERT_06  rr[6].X (),   rr[6].Y (),  rr[6].Z ()
#define VERT_07  rr[7].X (),   rr[7].Y (),  rr[7].Z ()
#define VERT_08  rr[8].X (),   rr[8].Y (),  rr[8].Z ()
#define VERT_09  rr[9].X (),   rr[9].Y (),  rr[9].Z ()
#define VERT_10  rr[10].X (),  rr[10].Y (), rr[10].Z ()
#define VERT_11  rr[11].X (),  rr[11].Y (), rr[11].Z ()

#if 0
bool done_it = false;
#endif
void
draw_icosahedron (GLdouble ang, int axisIndex)
{

  if (!scale_done) {
    scale_done = true;
    for (int i = 0; i < icosahedron.size (); i++) {
      icosahedron[i] /= SCALE;
    }
  }
#if 0
  if (!done_it) {
    done_it = true;
    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 12; j++) {
	for (int k = 0; k < 12; k++) {
	  if ((j != i) && (k != i) && (k != j)) {
	    show_ang (i, j, k, icosahedron, i, j, k);
	  }
	}
      }
    }
  }
  exit (1);
#endif
 
  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (icosahedron);

#ifdef USE_FTGL
  FTGLPixmapFont font("/usr/share/fonts/truetype/freefont/FreeSerif.ttf");
  if (font.Error())
    cerr << "font fuck\n";
  else {
    font.FaceSize(12);
    glm::vec3 worldPos = glm::vec3(0.0f, .0f, 0.0f);
    glm::vec3 camera   = glm::vec3(0.0f, .0f, (float)z_off);

    glm::mat4 view = camera.getViewMatrix();
    glPushMatrix();
    glTranslatef(5, 5, 0);
    font.Render("Hello World!");
    glPopMatrix();
  }
#endif
  

#if 0	// okay
  show_ang (icosahedron, 0, 4, 8);		// 0
  show_ang (icosahedron, 4, 8, 0);
  show_ang (icosahedron, 8, 0, 4);
  show_ang (icosahedron, 3, 1, 0);
  
  show_ang (0, icosahedron, 1, 6, 10);		// 0
  show_ang (1, icosahedron, 6, 10, 1);		// 0
  show_ang (2, icosahedron, 10, 1, 6);		// 0

  show_ang (icosahedron, 0, 2,  5);		// 0
  show_ang (icosahedron, 2, 5, 0);		// 0
  show_ang (icosahedron, 5, 0, 2);		// 0


  show_ang (icosahedron, 1, 0, 3);
  show_ang (icosahedron, 0, 3, 1);
  show_ang (icosahedron, 0, 8, 2);		// 1
  show_ang (icosahedron, 8, 2, 0);
  show_ang (icosahedron, 2, 0, 8);

  show_ang (icosahedron, 0, 5, 9);		// 2
  show_ang (icosahedron, 5, 9, 0);
  show_ang (icosahedron, 9, 0, 5);
  
  show_ang (icosahedron, 0, 9, 4);		// 3
  show_ang (icosahedron, 9, 4, 0);	
  show_ang (icosahedron, 4, 0, 9);	

  show_ang (icosahedron, 1, 11, 7);	// 6
  show_ang (icosahedron, 11, 7, 1);
  show_ang (icosahedron, 7, 1, 11);
  
  show_ang (icosahedron, 1, 3, 11);	// 5
  show_ang (icosahedron, 3, 11, 1);	// 5
  show_ang (icosahedron, 11, 1, 3);	// 5
  
  show_ang (icosahedron, 1, 7, 6);	// 5
  show_ang (icosahedron, 7, 6, 1);	// 5
  show_ang (icosahedron, 6, 1, 7);	// 5
  
  show_ang (icosahedron, 5, 2, 10);	// 5
  show_ang (icosahedron, 2, 10, 5);	// 5
  show_ang (icosahedron, 10, 5, 2);	// 5
#endif


  

  glBegin (GL_TRIANGLES); // t 1
    glColor3d (0.898438, 0.0976562, 0.292969);	// red
    glVertex3d (VERT_00);
    glVertex3d (VERT_02);
    glVertex3d (VERT_08);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 2
    glColor3d (0.234375, 0.703125, 0.292969);	// green
    glVertex3d (VERT_00);
    glVertex3d (VERT_02);
    glVertex3d (VERT_09);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 3		// blue
    glColor3d (0.261719, 0.386719, 0.84375);
    glVertex3d (VERT_00);
    glVertex3d (VERT_04);
    glVertex3d (VERT_06);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 4
    glColor3d (0.957031, 0.507812, 0.191406);	// orange
    glVertex3d (VERT_00);
    glVertex3d (VERT_04);
    glVertex3d (VERT_08);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 5
    glColor3d (0.976562, 0.742188, 0.828125);	// skin
    glVertex3d (VERT_00);
    glVertex3d (VERT_06);
    glVertex3d (VERT_09);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 6
  glColor3d (0.257812, 0.828125, 0.953125);	// cyan
    glVertex3d (VERT_01);
    glVertex3d (VERT_03);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 7
  glColor3d (0.566406, 0.117188, 0.703125);	// purple
    glVertex3d (VERT_01);
    glVertex3d (VERT_03);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 8
  glColor3d (0.746094, 0.933594, 0.269531);	// greenish yellow
    glVertex3d (VERT_01);
    glVertex3d (VERT_04);
    glVertex3d (VERT_06);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 9		// yellow
    glColor3d (0.996094, 0.878906, 0.0976562);
    glVertex3d (VERT_01);
    glVertex3d (VERT_04);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 10
  glColor3d (0.9375, 0.195312, 0.898438);	// cot pink
    glVertex3d (VERT_01);
    glVertex3d (VERT_06);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 11
  glColor3d (0.859375, 0.742188, 0.996094);	// pale pink
    glVertex3d (VERT_02);
    glVertex3d (VERT_05);
    glVertex3d (VERT_07);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 12
  glColor3d (0.601562, 0.386719, 0.140625);	// pale yellow
    glVertex3d (VERT_02);
    glVertex3d (VERT_05);
    glVertex3d (VERT_08);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 13
  glColor3d (0.996094, 0.976562, 0.78125);	//brown
    glVertex3d (VERT_02);
    glVertex3d (VERT_07);
    glVertex3d (VERT_09);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 14
  glColor3d (0.273438, 0.597656, 0.5625);	// sage
    glVertex3d (VERT_03);
    glVertex3d (VERT_05);
    glVertex3d (VERT_07);
  glEnd ();
  
  glBegin (GL_TRIANGLES); // t 15
  glColor3d (0.5, 0, 0);		// dark red
    glVertex3d (VERT_03);
    glVertex3d (VERT_05);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 16
  glColor3d (0.664062, 0.996094, 0.761719);	// light green
    glVertex3d (VERT_03);
    glVertex3d (VERT_07);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 17
  glColor3d (0.996094, 0.84375, 0.691406);	// yellowish
    glVertex3d (VERT_04);
    glVertex3d (VERT_08);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 18
  glColor3d (0, 0, 0.457031);		// dark blue
    glVertex3d (VERT_05);
    glVertex3d (VERT_08);
    glVertex3d (VERT_10);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 19
  glColor3d (0.660156, 0.660156, 0.660156); // grey
    glVertex3d (VERT_06);
    glVertex3d (VERT_09);
    glVertex3d (VERT_11);
  glEnd ();

  glBegin (GL_TRIANGLES); // t 20
  glColor3d (0.5, 0.5, 0);	// yellowish green
    glVertex3d (VERT_07);
    glVertex3d (VERT_09);
    glVertex3d (VERT_11);
  glEnd ();
}
