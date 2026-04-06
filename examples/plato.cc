#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Quat.hh>
#include <getopt.h>
#include <string.h>
#include <iostream>

#include "plato.hh"
#include "tetrahedron.hh"
#include "cube.hh"
#include "octahedron.hh"
#include "icosahedron.hh"

#define EYE_RADIUS 3.0

GLFWwindow* window;

#define DEFAULT_WIDTH  500
int width  = DEFAULT_WIDTH;
#define DEFAULT_HEIGHT 500
int height = DEFAULT_HEIGHT;

GLdouble axes[][3] = {
  {0, 0, 1},
#define Z_AXIS 0
  {0, 1, 1},
  {0, 0.5, 0.5},
#define Y_AXIS 2
  {1, 1, 0},
  {1, 1, 1},
#define MAIN_DIAG_AXIS 4
  {1, 0, 1},
  {1, 0, 0}
#define X_AXIS 6
};
int axisIndex = MAIN_DIAG_AXIS;
bool axisLocked = false;

GLdouble ang = 0.0;
#define FAST D2R (5.0)
#define SLOW D2R (30.0)
GLdouble inc = FAST;

const char* cmd = "ffmpeg -r 10 -f rawvideo -pix_fmt rgba -s %dx%d \
 -i - -threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip %s";
char *vidout = nullptr;
FILE* ffmpeg = nullptr;

typedef void (*drawit) (GLdouble ang, int axisIndex);
drawit func = draw_cube;

enum {
  STOPPED,
  RUN,
  STEP_FORWARD,
  STEP_BACKWARD
};
int state = RUN;

double x_off = 0.0;
double y_off = 0.0;
double z_off = EYE_RADIUS;

void
show_ang (int ix, vector<Quat> rr, int v0, int v1, int v2)
{
  double rang  = (rr[v0] - rr[v1]).qang (rr[v2] - rr[v1]);
  Quat   cross = (rr[v0] - rr[v1]).qcross (rr[v2] - rr[v1]);
  cout << ix << " " << v0 << " " << v1 << " " << v2 << " "
       << R2D (rang) << " " << cross << endl;
}

void
cursor_position_callback (GLFWwindow* window, double x, double y)
{
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    // cout << x << " " << y << endl;
    double lng = M_PI * ((double)(x - width/2))  / (double)(width/2);
    double lat = M_PI * ((double)(y - height/2)) / (double)(height/2);
    //    cout << R2D (lat) << " " << R2D (lng) << endl;
    double z_off = EYE_RADIUS * cos (lat) * cos (lng);
    double x_off = EYE_RADIUS * cos (lat) * sin (lng);
    double y_off = EYE_RADIUS * sin (lat);
    //    cout << x_off << " " << y_off << " " << z_off << endl;
    glLoadIdentity();
    gluLookAt(x_off, y_off, z_off,	// eye
	      0.0, 0.0, 0.0,	// lookat
	      0.0, 1.0, 0.0);	// up
  }
}

void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
#if 0
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    double lat = M_PI * ((double)(xpos - width/2))  / (double)(width/2);
    double lng = M_PI * ((double)(ypos - height/2)) / (double)(height/2);
    cout << R2D (lat) << " " << R2D (lng) << endl;
    x_off = EYE_RADIUS * cos (lat) * cos (lng);
    z_off = EYE_RADIUS * cos (lat) * sin (lng);
    y_off = EYE_RADIUS             * sin (lng);
    cout << x_off << " " << y_off << " " << z_off << endl;
    glLoadIdentity();
    gluLookAt(x_off, y_off, z_off,	// eye
	      0.0, 0.0, 0.0,	// lookat
	      0.0, 1.0, 0.0);	// up
  }
#endif
}

void
key_callback (GLFWwindow* window, int key, int scancode,
	      int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE ||
       key ==  GLFW_KEY_Q) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    switch (state) {
    case STOPPED:
      state = RUN;
      break;
    case RUN:
    case STEP_FORWARD:
    case STEP_BACKWARD:
      state = STOPPED;
      break;
    }
  }
  else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
    z_off += (mods & GLFW_MOD_SHIFT) ? -0.1 : 0.1;
    glLoadIdentity();
    gluLookAt(x_off, y_off, z_off,	// eye
	      0.0, 0.0, 0.0,	// lookat
	      0.0, 1.0, 0.0);	// up
  }
  else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    state = STEP_FORWARD;
  }
  else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    state = STEP_BACKWARD;
  }
}

void render()
{
  glLoadIdentity();
  gluLookAt(0.0, 0.0, z_off,	// eye
	    0.0, 0.0, 0.0,	// lookat
	    0.0, 1.0, 0.0);	// up


  while (!glfwWindowShouldClose(window)) {
    if (state != STOPPED) {
      ang += (state == STEP_BACKWARD) ? -0.01 : 0.01;
      if (ang > 2.0 * M_PI) ang -= 2.0 * M_PI;
      else if (ang < 0.0) ang += 2.0 * M_PI;
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    (*func) (ang, axisIndex);

    if (state == STEP_BACKWARD ||
	state == STEP_FORWARD) state = STOPPED;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}

int
main (int ac, char *av[])
{
  int x_pos = 300;
  int y_pos = 300;
  {
    static struct option long_options[] = {
      {"width",     required_argument, 0,  'w' },
      {"height",    required_argument, 0,  'h' },
      {"video",     required_argument, 0,  'v' },
      {"axis",      required_argument, 0,  'a' },
      {"shape",     required_argument, 0,  's' },
      {"xpos",      required_argument, 0,  'y' },
      {"ypos",      required_argument, 0,  'x' },
      {0,           0,                 0,   0 }
    };

    int c;
    int option_index = 0;
    while (-1 != (c = getopt_long (ac, av, "w:h:v:a:s:x:y:",
				   long_options, &option_index))) {
      switch (c) {
      case 'x': x_pos  = atoi (optarg); break;
      case 'y': y_pos  = atoi (optarg); break;
      case 'w': width  = atoi (optarg); break;
      case 'h': height = atoi (optarg); break;
      case 'v': vidout = strdup (optarg); break;
      case 'a':
	switch (*optarg) {
	case 'x':
	  axisIndex = X_AXIS;
	  axisLocked = true;
	  break;
	case 'y':
	  axisIndex = Y_AXIS;
	  axisLocked = true;
	  break;
	case 'z':
	  axisIndex = Z_AXIS;
	  axisLocked = true;
	  break;
	case 'm':
	  axisIndex = MAIN_DIAG_AXIS;
	  axisLocked = true;
	  break;
	}
	break;
      case 's':
	switch (*optarg) {
	case 't':
	  func = draw_tetrahedron;
	  break;
	case 'c':
	  func = draw_cube;
	  break;
	case 'o':
	  func = draw_octahedron;
	  break;
	case 'i':
	  func = draw_icosahedron;
	  break;
	}
	break;
      }
    }
  
    if (vidout) {
      char *cmdstring = nullptr;
      asprintf (&cmdstring, cmd, width, height, vidout);
      fprintf (stderr, "vid = \"%s\"\n", cmdstring);
      ffmpeg = popen(cmdstring, "w");
      free (cmdstring);
      inc = SLOW;
    }
  }
  
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  window = glfwCreateWindow (width, height, "Platonic shapes",
			     nullptr, nullptr);
  glfwSetWindowPos(window, x_pos, y_pos);
  glfwShowWindow(window);

  if (!window) {
    std::cerr << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  
  int iwidth, iheight;
  glfwGetFramebufferSize(window, &iwidth, &iheight);
  glViewport(0, 0, iwidth, iheight);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  gluPerspective(30.0, (double)iwidth / (double)iheight, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);


  render ();

  return EXIT_SUCCESS;
}
