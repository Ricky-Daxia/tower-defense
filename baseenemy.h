#ifndef BASEENEMY_H
#define BASEENEMY_H

#include "enemy.h"
class BaseEnemy : public Enemy {
 public:
  BaseEnemy(Map*);
  bool is_flyer();
  bool is_enemy2();
  bool is_buff();
  void switch_pic(int);
  void move(int);

 protected:
  int times;
};

#endif  // BASEENEMY_H
