#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Quat.hh>
#include <iostream>

#include "cube.hh"
#include "icosahedron.hh"

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
GLdouble ang = 0.0;

enum {
  STOPPED,
  RUN,
  STEP_FORWARD,
  STEP_BACKWARD
};
int state = RUN;

double z_off = 3.0;

void
key_callback (GLFWwindow* window, int key, int scancode,
	      int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE ||
       key ==  GLFW_KEY_Q) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    if (state == RUN) state = STOPPED;
  }
  else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
    z_off += (mods & GLFW_MOD_SHIFT) ? -0.1 : 0.1;
    glLoadIdentity();
    gluLookAt(0.0, 0.0, z_off,	// eye
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
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return;
  }

  GLFWwindow* window = glfwCreateWindow(800, 600, "3D Cube", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

#if 1
  glfwSetKeyCallback(window, key_callback);
#endif

  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  gluPerspective(30.0, (double)width / (double)height, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);

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
    
    //    draw_cube (ang, axisIndex);
    draw_icosahedron (ang, axisIndex);

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
  render ();
}
