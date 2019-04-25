//Blake Lockley - 44587643

#import "Wake.h"
#import "Utilities.h"
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#define WAKE_TIME 500.0f

void Wake::draw(void) {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f - (timer / WAKE_TIME));
  drawCircle(0.0f, 0.0f, 1.0f, 20);
}

void Wake::update(int step) {
  Entity::update(step);

  _isGone = timer > WAKE_TIME;
}
