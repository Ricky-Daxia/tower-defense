#include "tower.h"

Tower::Tower(Map* pos) : Defenders(150, pos, 3, 2) {
  this->setPic(":/tower3.png");
  volume.setRect(x - 25, y - 25, 60 + 25 + 25, 60 + 25 + 25);
  this->times = 0;
}
bool Tower::is_attacker() { return false; }
bool Tower::is_nut() { return false; }
bool Tower::is_tower() { return true; }
bool Tower::is_attacker3() { return false; }
void Tower::switch_pic() {
  ++times;
  if (times == 5) {
    times = 0;
    pic_num = (pic_num + 1) % 5;
    pic.load(QString(":/tower%1.png").arg(pic_num));
  }
}
void Tower::attacked(int harm) {
  Objects::attacked(harm);
  switch_pic();
}
