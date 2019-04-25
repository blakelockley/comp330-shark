//Blake Lockley - 44587643

#ifndef ENTITY_H
#define ENTITY_H

#include "Geometry.h"

class Entity {
protected:
  Frame frame;
  int timer; //lifetime of entity for timing events.
  float rotation, velocity, radius;
  bool _isMoving;

  virtual void draw(void) = 0;

public:
  Entity(Frame f, float v, float r, bool m):
  	frame(f), timer(0), velocity(v), rotation(r), _isMoving(m)
  {
      radius = (frame.rect.width + frame.rect.height) / 4;
  }

  void render(void);
  virtual void update(int step);

  bool collisionWith(Entity& other);
  bool isMoving(void) { return _isMoving; }
  Frame& getFrame(void) { return frame; }
};

#endif
