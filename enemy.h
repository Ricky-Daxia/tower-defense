#ifndef ENEMY_H
#define ENEMY_H

#include "objects.h"

class Enemy : public Objects {
 public:
  Enemy(int, Map*, int);
  void setPic(QString);
  virtual void move(int);
  virtual void switch_pic(int);
  int getHP();
  void eraseHP();
  int get_ATK();
  virtual bool is_flyer() = 0;
  virtual bool is_enemy2() = 0;
  virtual bool is_buff() = 0;

 protected:
  int ATK;
  int dirc;
};

#endif  // ENEMY_H
