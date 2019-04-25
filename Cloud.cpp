//Blake Lockley - 44587643

#import "Cloud.h"
#import "Utilities.h"
#import <stdlib.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#define CLOUD_TIME 4000.0f

Cloud::Cloud(Point p, float r):
	Entity(Frame(p, Rect(30, 30)), 0.1f, 0.0f, true), _isGone(false)
{
  frame.centre.x += ((rand() % 20) - 10);
  frame.centre.y += ((rand() % 20) - 10);

  rotation = r + (rand() % 20) - 10;
}

void Cloud::draw(void) {
  float alpha = 1.0f;
  if (timer < 1000)
  	alpha = timer / 1000.0f;
  else if (timer > CLOUD_TIME - 1000.0f)
  	alpha = (CLOUD_TIME - timer) / 1000.0f;

  glColor4f(0.2f, 0.2f, 0.2f, alpha);
  drawCircle(0.0f, 0.0f, 1.0f, 20);
}

void Cloud::update(int step) {
  Entity::update(step);

  _isGone = timer > CLOUD_TIME;
}
