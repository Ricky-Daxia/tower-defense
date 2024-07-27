#ifndef BASEATTACKER_H
#define BASEATTACKER_H
#include "defenders.h"

class BaseAttacker : public Defenders {
  //继承了maxHP, is_alive, position, pic, rect
 public:
  BaseAttacker(Map*);
  bool is_attacker();
  bool is_nut();
  bool is_tower();
  bool is_attacker3();
  void switch_pic();
  void attacked(int);

 protected:
  int times;
};

#endif  // BASEATTACKER_H
