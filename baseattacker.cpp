#include "baseattacker.h"

BaseAttacker::BaseAttacker(Map* pos) : Defenders(200, pos, 1, 2) {
  this->setPic(":/attacker_one0.png");
  this->times = 0;
}
bool BaseAttacker::is_attacker() { return true; }
bool BaseAttacker::is_nut() { return false; }
bool BaseAttacker::is_tower() { return false; }
bool BaseAttacker::is_attacker3() { return false; }
void BaseAttacker::switch_pic() {
  ++times;
  if (times == 5) {
    times = 0;
    pic_num = (pic_num + 1) % 5;
    setPic(QString(":/attacker_one%1.png").arg(pic_num));
  }
}
void BaseAttacker::attacked(int harm) {
  Objects::attacked(harm);
  switch_pic();
}
