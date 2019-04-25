//Blake Lockley - 44587643

#ifndef CLOUD_H
#define CLOUD_H

#import "Entity.h"

class Cloud: public Entity {
  bool _isGone;

  protected:
  void draw(void);

  public:
  Cloud(Point p, float r);

  void update(int step);
  bool isGone(void) { return _isGone; }
  void updateRotation(float r) { rotation += r; };
};

#endif
