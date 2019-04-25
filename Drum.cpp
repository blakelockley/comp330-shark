//Blake Lockley - 44587643

#include "Drum.h"
#include "Utilities.h"
#include <math.h>
#include <stdlib.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

void Drum::draw(void) {

  if (!_isHit) {
  	glColor3f(0.7f, 0.7f, 0.7f);
  	drawCircle(0.0f, 0.0f, 1.0f, 20);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawCircle(0.5f, 0.0f, 0.2f, 20);
    return;
  }

  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
    else 						glColor3f(1.0f, 0.5f, 0.0f);

    float x = ((rand() % 200) - 100) / 200.0f;
    float y = ((rand() % 200) - 100) / 200.0f;
    drawCircle(x, y, 0.3f, 20);
  }

}

void Drum::update(int step) {
  Entity::update(step);

  if (rotationTime == 0 || rotationTime + 5000 < timer) {
  	rotation += (rand() % 10) - 5;
    if (rotation > 180) rotation -= 360.0f;
    if (rotation < -180) rotation += 360.0f;
    rotationTime = timer;
  }

  _isGone = _isHit && hitTime + 2500 < timer;
}

Cloud Drum::produceSmoke(float windDirection) {
  return Cloud(frame.centre, windDirection);
}

void Drum::wasHit(void) {
  if (_isHit)
  	return;

  _isMoving = false;
  _isHit = true;
  hitTime = timer;
}
