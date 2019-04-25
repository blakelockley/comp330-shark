//Blake Lockley - 44587643

#include "Torpedo.h"
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

void Torpedo::draw(void) {
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(1.0f, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex2f(-1.0f, -1.0);
  glVertex2f(-1.0, 1.0f);
  glEnd();
}
