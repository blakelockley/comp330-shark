//Blake Lockley - 44587643

#include "Ship.h"
#include "Utilities.h"

#include <stdlib.h>
#include <math.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

void drawShip(void), drawShark(void);

void Ship::draw(void) {
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(frame.centre.x, frame.centre.y - 60.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glRectf(-40, 0, -40 + (80 * health), 10);
  glColor3f(1.0f, 0.0f, 0.0f);
  glRectf(-40 + (80 * health), 0, 40, 10);
  glPopMatrix();

  if (skin == ship)
  	drawShip();
  else if (skin == shark)
  	drawShark();
}

void Ship::update(int step) {
  _isMoving = !frame.contains(destination);
  if (!_isMoving)
  	velocity = 0.0f;

  Entity::update(step);

  float dx = destination.x - frame.centre.x;
  float dy = destination.y - frame.centre.y;
  float angle = atan2(dy, dx) * 180 / M_PI;
  float diff = rotation - angle;

  if (fabs(diff) > 5.0f) {
    if ((0.0f < diff && diff < 180.0f) || diff < -180.0f)
    rotation -= 5.0f;
    else
    rotation += 5.0f;

    if (rotation > 180) 			rotation -= 360.0f;
    else if (rotation < -180)	rotation += 360.0f;
  }
}

void Ship::move(Point location) {
  destination = location;
  velocity = speed;
  _isMoving = true;
}

Torpedo Ship::shoot(void) {
  lastShootTime = timer;
  return Torpedo(frame.centre, rotation, this);
}

Wake Ship::leftWake(void) {
  float r = rotation + 270;
  if (r >= 180) r -= 360.0f;

  return Wake(frame.centre, r);
}

Wake Ship::rightWake(void) {
  float r = rotation + 90;
  if (r >= 180) r -= 360.0f;

  return Wake(frame.centre, r);
}

void drawShip(void) {
  //draw boat
  glBegin(GL_POLYGON);
  glColor3f(0.7f, 0.7f, 0.7f);
  glVertex2f(1.0f, -0.1f);
  glVertex2f(1.0f, 0.1f);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex2f(0.8f, 0.3f);
  glVertex2f(0.5f, 0.7f);
  glVertex2f(-1.0f, 0.7f);
  glVertex2f(-1.0f, -0.7f);
  glVertex2f(0.5f, -0.7f);
  glVertex2f(0.8f, -0.3f);
  glEnd();

  //draw windscreen
  glBegin(GL_QUADS);
  glColor3f(0.5f, 0.7f, 1.0f);
  glVertex2f(0.2f, 0.6f);
  glVertex2f(0.2f, -0.6f);
  glColor3f(0.7f, 0.9f, 1.0f);
  glVertex2f(-0.2f, -0.6f);
  glVertex2f(-0.2f, 0.6f);
  glEnd();
}

void drawShark(void) {
  //draw body
  glBegin(GL_POLYGON);
  glColor3f(0.8f, 0.8f, 0.8f);
  glVertex2f(1.0f, -0.1f);
  glVertex2f(1.0f, 0.1f);
  glColor3f(0.5f, 0.5f, 0.8f);
  glVertex2f(0.6f, 0.5f);
  glVertex2f(0.0f, 0.5f);
  glVertex2f(-0.7f, 0.2f);
  glVertex2f(-0.7f, -0.2f);
  glVertex2f(0.0f, -0.5f);
  glVertex2f(0.6f, -0.5f);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3f(0.5f, 0.5f, 0.8f);
  //right fin
  glVertex2f(0.4f, 0.5f);
  glColor3f(0.8f, 0.8f, 0.8f);
  glVertex2f(0.0f, 1.0f);
  glColor3f(0.5f, 0.5f, 0.8f);
  glVertex2f(0.1f, 0.5f);
  //left fin
  glVertex2f(0.4f, -0.5f);
  glColor3f(0.8f, 0.8f, 0.8f);
  glVertex2f(0.0f, -1.0f);
  glColor3f(0.5f, 0.5f, 0.8f);
  glVertex2f(0.1f, -0.5f);
  //tail
  glVertex2f(-0.5f, 0.0f);
  glColor3f(0.8f, 0.8f, 0.8f);
  glVertex2f(-1.0f, 0.7f);
  glVertex2f(-1.0f, -0.7f);
  glEnd();

  //dorsal fin
  glBegin(GL_LINES);
  glColor3f(0.5f, 0.5f, 0.8f);
  glVertex2f(0.4f, 0.0f);
  glVertex2f(0.0f, 0.0f);
  glEnd();

  //eyes
  glPushMatrix();
  glScalef(0.5f, 1.0f, 1.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  drawCircle(1.3f, 0.3f, 0.1f, 10);
  drawCircle(1.3f, -0.3f, 0.1f, 10);
  glPopMatrix();
}

