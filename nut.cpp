#include "nut.h"

Nut::Nut(Map* pos) : Defenders(200, pos, 2, 0) { this->setPic(":/nuts.png"); }
bool Nut::is_attacker() { return false; }
bool Nut::is_nut() { return true; }
bool Nut::is_tower() { return false; }
bool Nut::is_attacker3() { return false; }
void Nut::attacked(int harm) {
  Objects::attacked(harm);
  if (curHP < maxHP * 0.5) setPic(":/nuts1.png");
}
