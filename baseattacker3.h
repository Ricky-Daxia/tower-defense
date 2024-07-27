#ifndef BASEATTACKER3_H
#define BASEATTACKER3_H
#include "defenders.h"

class BaseAttacker3 : public Defenders {
 public:
  BaseAttacker3(Map*);
  bool is_attacker();
  bool is_nut();
  bool is_tower();
  bool is_attacker3();
};

#endif  // BASEATTACKER3_H
