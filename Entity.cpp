//Blake Lockley - 44587643

#include "Entity.h"
#include "Utilities.h"
#include <math.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

void Entity::update(int step) {
  timer += step;

  if (!_isMoving)
  	return;

  float distance = velocity * step;

  frame.centre.x += cos(rotation * M_PI / 180) * distance;
  frame.centre.y += sin(rotation * M_PI / 180) * distance;
}

void Entity::render(void) {
  glPushMatrix();
  glLoadIdentity();

  //show hitbox
#ifdef DEBUG
  glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
  drawCircle(frame.centre.x, frame.centre.y, radius, 30);
#endif

  glTranslatef(frame.centre.x, frame.centre.y, 0.0f);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  glScalef(frame.rect.height / 2.0f, frame.rect.width / 2.0f, 1.0);

  draw();

  glPopMatrix();
}

bool Entity::collisionWith(Entity& other) {
  float dist = sqrt(pow(frame.centre.x - other.frame.centre.x, 2)
                    + pow(frame.centre.y - other.frame.centre.y, 2));

  return dist < radius + other.radius;

  //frame.intersects(other.frame);
}
