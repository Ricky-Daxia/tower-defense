#ifndef BUFF_H
#define BUFF_H
#include "enemy.h"

class buff : public Enemy {
 public:
  buff(Map*);
  bool is_flyer();
  bool is_enemy2();
  bool is_buff();
  void switch_pic(int);
  void move(int);

 protected:
  int times;
};

#endif  // BUFF_H
