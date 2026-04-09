#include <GLFW/glfw3.h>
#include <vector>
#include <Quat.hh>

struct Face {
  int verts[5];
  double r;
  double g;
  double b;
  double xc;
  double yc;
  double zc;
};

Face Faces[] = {
  {{0, 14, 19, 15,  1}, 0.261719, 0.386719, 0.843750, 0.0,0.0, 0.0},
  {{0,  9, 15, 11,  2}, 0.566406, 0.117188, 0.703125, 0.0,0.0, 0.0},
  {{1,  3, 10, 14,  8}, 0.996094, 0.878906, 0.097656, 0.0,0.0, 0.0},
  {{2,  3, 15, 18, 14}, 0.273438, 0.597656, 0.562500, 0.0,0.0, 0.0},
  {{4,  5, 13, 17, 12}, 0.500000, 0.500000, 0.000000, 0.0,0.0, 0.0},
  {{4,  6, 11, 13,  9}, 0.898438, 0.097656, 0.292969, 0.0,0.0, 0.0},
  {{5,  8, 12, 10,  7}, 0.261719, 0.386719, 0.843750, 0.0,0.0, 0.0},
  {{0, 16, 17,  2, 12}, 0.957031, 0.507812, 0.191406, 0.0,0.0, 0.0},
  {{0,  8,  9,  1, 16}, 0.257812, 0.828125, 0.953125, 0.0,0.0, 0.0},
  {{1, 13,  3, 17, 16}, 0.746094, 0.933594, 0.269531, 0.0,0.0, 0.0},
  {{2, 17,  3, 11, 10}, 0.996094, 0.976562, 0.781250, 0.0,0.0, 0.0},
  {{4, 14,  6, 19, 18}, 0.000000, 0.000000, 0.457031, 0.0,0.0, 0.0},
  {{4, 18,  5,  9,  8}, 0.660156, 0.660156, 0.660156, 0.0,0.0, 0.0},
  {{5, 18, 19,  7, 15}, 0.234375, 0.703125, 0.292969, 0.0,0.0, 0.0},
  {{6, 10, 11,  7, 19}, 0.957031, 0.507812, 0.191400, 0.0,0.0, 0.0},
  {{6, 12, 16, 13,  7}, 0.976562, 0.742188, 0.828125, 0.0,0.0, 0.0},
  {{0, 17, 11, 19,  4}, 0.976562, 0.742188, 0.828125, 0.0,0.0, 0.0}, //
  {{3, 16,  8, 18,  7}, 0.996094, 0.843750, 0.691406, 0.0,0.0, 0.0}, //
  {{3, 13, 15,  7, 11}, 0.664062, 0.996094, 0.761719, 0.0,0.0, 0.0}, //
  {{1,  9,  5, 15, 13}, 0.859375, 0.742188, 0.996094, 0.0,0.0, 0.0}, //
  {{2, 10,  6, 14, 12}, 0.601562, 0.386719, 0.140625, 0.0,0.0, 0.0}, //
  {{0, 12, 14,  4,  8}, 0.898438, 0.097656, 0.292969, 0.0,0.0, 0.0}, //
  {{0, 12, 14,  4,  8}, 0.234375, 0.703125, 0.292969, 0.0,0.0, 0.0}, //
  {{2,  6, 18,  9, 16}, 0.500000, 0.000000, 0.000000, 0.0,0.0, 0.0}, //
  {{1,  5, 19, 10, 17}, 0.937500, 0.195312, 0.898438, 0.0,0.0, 0.0}, //
};

bool face_ctrs_set = false;
int nr_faces = sizeof(Faces) / sizeof(Face);

#include "plato.hh"

#define  PHI 1.618033989
#define IPHI 0.618033989

#define SCALE 3.0
static bool scale_done = false;

vector<Quat> dodecahedron = {
  Quat (0,   1.0,   1.0,   1.0),	//  0
  Quat (0,   1.0,   1.0,  -1.0),	//  1
  Quat (0,   1.0,  -1.0,   1.0),	//  2
  Quat (0,   1.0,  -1.0,  -1.0),	//  3
  Quat (0,  -1.0,   1.0,   1.0),	//  4
  Quat (0,  -1.0,   1.0,  -1.0),	//  5
  Quat (0,  -1.0,  -1.0,   1.0),	//  6
  Quat (0,  -1.0,  -1.0,  -1.0),	//  7
  Quat (0,   0.0,   PHI,  IPHI),	//  8
  Quat (0,   0.0,   PHI, -IPHI),	//  9
  Quat (0,   0.0,  -PHI,  IPHI),	// 10
  Quat (0,   0.0,  -PHI, -IPHI),	// 11
  Quat (0,  IPHI,   0.0,   PHI),	// 12
  Quat (0,  IPHI,   0.0,  -PHI),	// 13
  Quat (0, -IPHI,   0.0,   PHI),	// 14
  Quat (0, -IPHI,   0.0,  -PHI),	// 15
  Quat (0,   PHI,  IPHI,   0.0),	// 16
  Quat (0,   PHI, -IPHI,   0.0),	// 17
  Quat (0,  -PHI,  IPHI,   0.0),	// 18
  Quat (0,  -PHI, -IPHI,   0.0)		// 19
};

extern double axes[][3];

enum {
  VTX_NR,
  VTX_NL,
  VTX_FT,
  VTX_FB,
};

bool done_it = false;

void
draw_dodecahedron (double ang, int axisIndex)
{
  if (!scale_done) {
    scale_done = true;
    for (int i = 0; i < dodecahedron.size (); i++) {
      dodecahedron[i] /= SCALE;
    }
  }

  if (!face_ctrs_set) {
    face_ctrs_set = true;
    for (int i = 0; i < nr_faces; i++) {
      for (int j = 0; j < 5; j++) {
	Faces[i].xc += dodecahedron[Faces[i].verts[j]].X ();
	Faces[i].yc += dodecahedron[Faces[i].verts[j]].Y ();
	Faces[i].yc += dodecahedron[Faces[i].verts[j]].Z ();
      }
      Faces[i].xc /= 5.0;
      Faces[i].yc /= 5.0;
      Faces[i].zc /= 5.0;
    }
  }

#if 0
  if (!done_it) {
    done_it = true;
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
	for (int k = 0; k < 20; k++) {
	  for (int l = 0; l < 20; l++) {
	    for (int m = 0; m < 20; m++) {
	      if ((j != i) &&
		  (k != i) && (k != j) &&
		  (l != i) && (l != j) && (l != k) &&
		  (m != i) && (m != j) && (m != k) && (m != l)
		  ) {
		analyse_verts (dodecahedron, i, j, k, l, m);
	      }
	    }
	  }
	}
      }
    }
  }
  exit (1);
#endif

#if 0
  static bool shown = false;
  if (!shown) {
    shown = true;
    {
      for (int i = 0; i < 24; i++) {
	show_ang (dodecahedron,
		  Faces[i].verts[0],
		  Faces[i].verts[1],
		  Faces[i].verts[2],
		  Faces[i].verts[3],
		  Faces[i].verts[4]);
      }
    }
  }
#endif

  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (dodecahedron);

  glBegin (GL_TRIANGLE_FAN);
  for (int i = 0; i < 12; i ++) {
    glColor3f (Faces[i].r, Faces[i].g, Faces[i].b);
    glVertex3d (Faces[i].xc, Faces[i].yc, Faces[i].zc);
    for (int j = 0; j < 5; j++) {
      int v = Faces[i].verts[j];
      glVertex3d (rr[v].X (),  rr[v].Y (),  rr[v].Z ());
    }
    int v = Faces[i].verts[0];
    glVertex3d (rr[v].X (),  rr[v].Y (),  rr[v].Z ());
#if 0
    glVertex3d (rr[6].X (),  rr[6].Y (),  rr[6].Z ());
    glVertex3d (rr[12].X (), rr[12].Y (), rr[12].Z ());
    glVertex3d (rr[16].X (), rr[16].Y (), rr[16].Z ());
    glVertex3d (rr[13].X (), rr[13].Y (), rr[13].Z ());
    glVertex3d (rr[7].X (),  rr[7].Y (),  rr[7].Z ());
    glVertex3d (rr[6].X (),  rr[6].Y (),  rr[6].Z ());
#endif
  }
  glEnd ();
  
};
