//Blake Lockley - 44587643

#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include "Torpedo.h"
#include "Wake.h"

enum Skin { ship, shark };

class Torpedo;

class Ship: public Entity {
  Point destination;
  int lastShootTime;
  float speed, health;
  bool shooting;
  Skin skin;

protected:
  void draw(void);

public:
  Ship(Point p): Entity(Frame(p, Rect(40, 80)), 0.0f, 0.0f, false), skin(ship),
  	destination(Point(0,0)), lastShootTime(0), speed(0.2f), health(1.0f), shooting(false) {}

  void update(int step);

  void move(Point destination);
  void setShooting(bool s) { shooting = s; }
  bool canShoot(void) { return shooting && lastShootTime + 200 < timer; }
  void setSkin(Skin s) { skin = s; }
  void wasHit(void) { health -= 0.1f; }
  bool isDead(void) { return health <= 0.0f; }
  Torpedo shoot(void);
  Wake leftWake(void);
  Wake rightWake(void);
};

#endif
