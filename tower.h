#ifndef TOWER_H
#define TOWER_H
#include "defenders.h"

class Tower : public Defenders {
 public:
  Tower(Map*);
  bool is_attacker();
  bool is_nut();
  bool is_tower();
  bool is_attacker3();
  void switch_pic();
  void attacked(int);

 protected:
  int times;
};

#endif  // TOWER_H
