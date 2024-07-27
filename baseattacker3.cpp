#include "baseattacker3.h"

BaseAttacker3::BaseAttacker3(Map* pos)
    : Defenders(200, pos, 2, 2) {  //设置单位的矩形
  this->setPic(":/tofu.png");
  if (pos->get_x() > pos->get_next()->get_x()) {
    volume.setRect(x, y, 60 + 80, 60);
  } else
    volume.setRect(x, y - 80, 60, 60 + 80);
}
bool BaseAttacker3::is_attacker() { return false; }
bool BaseAttacker3::is_nut() { return false; }
bool BaseAttacker3::is_tower() { return false; }
bool BaseAttacker3::is_attacker3() { return true; }
