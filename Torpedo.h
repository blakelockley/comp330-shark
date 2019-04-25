//Blake Lockley - 44587643

#ifndef TORPEDO_H
#define TORPEDO_H

#include "Entity.h"
#include "Ship.h"

#include <iostream>

class Ship;

class Torpedo: public Entity {
  Ship *owner;

protected:
  void draw(void);

public:
  Torpedo(Point c, float r, Ship *_owner): owner(_owner),
  	Entity(Frame(c, Rect(10, 20)), 0.5f, r, true) {}

  bool belongsTo(Ship* ship) { return ship == owner; }
};

#endif
