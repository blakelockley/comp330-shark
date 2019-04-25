//Blake Lockley - 44587643

#ifndef WORLD_H
#define WORLD_H

#include "Ship.h"
#include "Torpedo.h"
#include "Drum.h"
#include "Wake.h"
#include "Cloud.h"
#include <stdlib.h>
#include <list> //a list is used for efficent deletion

class World {
  Frame frame;
  Ship ship;
  std::list<Ship> enemies;
  std::list<Torpedo> torpedos;
  std::list<Drum> drums;
  std::list<Wake> wakes;
  std::list<Cloud> clouds;
  float windDirection;

  void relocate(Entity& entity, Frame _frame);

public:
  World(Frame f);
  void update(int step);
  void render(void);

  Frame& getFrame() { return frame; }
  void updateFrame(Frame _frame);
  void addDrum(void);
  void addEnemy(void);
  Ship& getShip(void) { return ship; }
};

#endif
