#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "Vec2f.h"

class Bullet : public Object {
 public:
   Bullet(double x, double y, Vec2f d, Object* whoShotMe, double rad, 
          double red = 0, double green = 0, double blue = 0)
    : Object(x, y, red, green, blue), 
      r_(rad), dir(d), whoShotMe_(whoShotMe)
    {}

  void execute();
  std::string id() { return "bullet"; }
  void setdir(Vec2f);
  void move();
  void draw();

  double radius() { return r_; }

  Object* whoShotMe() { return whoShotMe_; }

 private:
  double r_;
  Vec2f dir;
  Object* whoShotMe_;
};

#endif