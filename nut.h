#ifndef NUT_H
#define NUT_H

#include "defenders.h"

class Nut : public Defenders {
 public:
  Nut(Map*);
  bool is_attacker();
  bool is_nut();
  bool is_tower();
  bool is_attacker3();
  void attacked(int);
};

#endif  // NUT_H
