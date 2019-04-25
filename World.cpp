//Blake Lockley - 44587643

#include "World.h"
#include <stdlib.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#define DRUMS 10
#define ENEMIES 1

typedef std::list<Torpedo>::iterator t_itr;
typedef std::list<Drum>::iterator d_itr;
typedef std::list<Wake>::iterator w_itr;
typedef std::list<Cloud>::iterator c_itr;
typedef std::list<Ship>::iterator e_itr;

World::World(Frame f): frame(f), ship(Ship(f.centre)) {
  windDirection = (rand() % 360) - 180.0f;

  for (int i = 0; i < DRUMS; i++)
    addDrum();

  for (int i = 0; i < ENEMIES; i++)
    addEnemy();
}

void World::update(int step) {

  //randomly update wind direction
  float windDelta = 0;
  if (rand() % 10 == 0) {
    windDelta = (rand() % 20) - 10.0f;
    windDirection += windDelta; //TODO: check in range
  }

  //update ship
  ship.update(step);
  if (ship.isMoving()) {
    wakes.push_back(ship.leftWake());
    wakes.push_back(ship.rightWake());
  }
  if (ship.canShoot())
    torpedos.push_back(ship.shoot());
  
  //update enemies
  for (e_itr enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
    enemy->update(step);
    if (enemy->isMoving()) {
      wakes.push_back(enemy->leftWake());
      wakes.push_back(enemy->rightWake());
    }

    if (rand() % 100 == 0) {
      enemy->move(Point(rand() % (int) frame.rect.width,
                       rand() % (int) frame.rect.height));
    }
    if (enemy->canShoot() && rand() % 10 == 0) {
      torpedos.push_back(enemy->shoot());
    }

    if (enemy->isDead()) {
      enemies.erase(enemy);
      Drum d = Drum(enemy->getFrame().centre);
      d.wasHit();
      drums.push_back(d);
    }
  }

  //update torpedos
  for (t_itr torpedo = torpedos.begin(); torpedo != torpedos.end(); torpedo++) {
    torpedo->update(step);
    bool destoryed = false;

    if (!frame.intersects(torpedo->getFrame())) {
      torpedos.erase(torpedo);
      continue;
    }

    if (!torpedo->belongsTo(&ship) && torpedo->collisionWith(ship)) {
      ship.wasHit();
      torpedos.erase(torpedo);
      continue;
    }

    for (e_itr enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
      if (torpedo->belongsTo(&ship) && torpedo->collisionWith(*enemy)) {
        enemy->wasHit();
        torpedos.erase(torpedo);
        destoryed = true;
        break;
      }
    }

    if (destoryed) break;

    for (d_itr drum = drums.begin(); drum != drums.end(); drum++) {
      if (torpedo->collisionWith(*drum) && !drum->isHit()) {
        drum->wasHit();
        torpedos.erase(torpedo);
        break;
      }
    }
  }

  //update drums
  for (d_itr drum = drums.begin(); drum != drums.end(); drum++) {
  		drum->update(step);
    if (ship.collisionWith(*drum))
      drum->wasHit();
    if (drum->isHit())
      clouds.push_back(drum->produceSmoke(windDirection));
    if (frame.doesNotFullyContain(drum->getFrame()))
      drum->turn();
    for (d_itr drum2 = drums.begin(); drum2 != drums.end(); drum2++)
      if (drum != drum2 && drum->collisionWith(*drum2))
        drum->turn(); //only turn this drum the other will turn next time
    if (drum->isGone())
      drums.erase(drum);
  }

  //update wake
  for (w_itr wake = wakes.begin(); wake != wakes.end(); wake++) {
    wake->update(step);
    if (wake->isGone())
      wakes.erase(wake);
  }

  //update clouds
  for (c_itr cloud = clouds.begin(); cloud != clouds.end(); cloud++) {
    cloud->update(step);
    cloud->updateRotation(windDelta);
    if (cloud->isGone())
      clouds.erase(cloud);
  }
}

void World::render(void) {
  for (t_itr itr = torpedos.begin(); itr != torpedos.end(); itr++)
    itr->render();

  for (d_itr itr = drums.begin(); itr != drums.end(); itr++)
    itr->render();

  for (w_itr wake = wakes.begin(); wake != wakes.end(); wake++)
    wake->render();

  ship.render();

  for (e_itr enemy = enemies.begin(); enemy != enemies.end(); enemy++)
    enemy->render();

  for (c_itr cloud = clouds.begin(); cloud != clouds.end(); cloud++)
    cloud->render();
}

void World::relocate(Entity& entity, Frame _frame) {
  if (_frame.rect.width < frame.rect.width || _frame.rect.height < frame.rect.height) {
    float x = entity.getFrame().centre.x / frame.rect.width;
    float y = entity.getFrame().centre.y / frame.rect.height;

    entity.getFrame().centre.x = x * _frame.rect.width;
    entity.getFrame().centre.y = y * _frame.rect.height;
  }
}

void World::updateFrame(Frame _frame) {
  for (t_itr itr = torpedos.begin(); itr != torpedos.end(); itr++)
    relocate(*itr, _frame);

  for (d_itr itr = drums.begin(); itr != drums.end(); itr++)
    relocate(*itr, _frame);

  for (w_itr wake = wakes.begin(); wake != wakes.end(); wake++)
    relocate(*wake, _frame);

  for (c_itr cloud = clouds.begin(); cloud != clouds.end(); cloud++)
    relocate(*cloud, _frame);

  relocate(ship, _frame);

  for (e_itr enemy = enemies.begin(); enemy != enemies.end(); enemy++)
  	relocate(*enemy, _frame);

  frame = _frame;
}

void World::addEnemy(void) {
  if (enemies.size() >= 5)
    return;

  float x = rand() % ((int) frame.rect.width);
  float y = rand() % ((int) frame.rect.height);

  Ship enemy(Ship(Point(x, y)));

  enemy.setSkin(shark);
  enemy.setShooting(true);
  enemies.push_back(enemy);
}

void World::addDrum(void) {
  if (drums.size() >= 50)
    return;

  Drum d(Point(0,0));
  float w = d.getFrame().rect.width;
  float h = d.getFrame().rect.height;
  bool occupied;

  do {
    float x = rand() % ((int) (frame.rect.width - w)) + w / 2;
    float y = rand() % ((int) (frame.rect.height - h)) + h / 2;
    d = Drum(Point(x, y));

    occupied = false;
    for (d_itr drum = drums.begin(); drum != drums.end(); drum++)
      if (drum->collisionWith(d)) {
        occupied = true;
        break;
      }
  } while (occupied);
  
  drums.push_back(d);
}

