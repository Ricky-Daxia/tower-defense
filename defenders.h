#ifndef DEFENDERS_H
#define DEFENDERS_H

#include "objects.h"

class Defenders : public Objects {
 public:
  Defenders(int, Map*, int, int);
  void setPic(QString);
  virtual void switch_pic();
  int get_consumption();
  int get_ATK();
  virtual bool is_attacker() = 0;
  virtual bool is_nut() = 0;
  virtual bool is_tower() = 0;
  virtual bool is_attacker3() = 0;

 protected:
  int consumption;
  int ATK;  //攻击力
};

#endif  // DEFENDERS_H
