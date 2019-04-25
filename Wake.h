//Blake Lockley - 44587643

#ifndef WAKE_H
#define WAKE_H

#include "Entity.h"

class Wake: public Entity {
  bool _isGone;

protected:
  void draw(void);

public:
  Wake(Point centre, float r):
  	Entity(Frame(centre, Rect(10, 10)), 0.02f, r, true), _isGone(false) {}

  void update(int step);
  bool isGone(void) { return _isGone; }
};

#endif
