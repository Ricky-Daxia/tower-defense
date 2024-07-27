#ifndef FLYER_H
#define FLYER_H
#include "enemy.h"

class Flyer : public Enemy {
 public:
  Flyer(Map*);
  bool is_flyer();
  bool is_enemy2();
  bool is_buff();
  void switch_pic(int);
  void attacked(int);
  void move(int);

 protected:
  bool is_attacked;
  int times;
};

#endif  // FLYER_H
