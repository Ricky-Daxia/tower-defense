#ifndef BASEENEMY2_H
#define BASEENEMY2_H
#include "enemy.h"

#define PIC1 ":/female1.png"
#define PIC2 ":/female2.png"

class BaseEnemy2 : public Enemy {
 public:
  BaseEnemy2(Map*);
  bool is_flyer();
  bool is_enemy2();
  bool is_buff();
  void switch_pic(int);
  void move(int);

 protected:
  int times;
};

#endif  // BASEENEMY2_H
