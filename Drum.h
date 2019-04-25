//Blake Lockley - 44587643

#ifndef DRUM_H
#define DRUM_H

#import "Entity.h"
#import "Cloud.h"
#import <stdlib.h>

class Drum: public Entity {
  bool _isHit, _isGone;
  int hitTime, rotationTime;

protected:
  void draw(void);

public:
  Drum(Point p): Entity(Frame(p, Rect(30, 30)),
                        0.01f, (rand() % 360) - 180.0f, true),
    _isHit(false), _isGone(false), hitTime(0.0f), rotationTime(0.0f) {}

  void update(int step);
  void wasHit(void);
  bool isHit(void) { return _isHit; }
  bool isGone(void) { return _isGone; }
  void turn(void) { velocity *= -1; }
  Cloud produceSmoke(float windDirection);
};

#endif
