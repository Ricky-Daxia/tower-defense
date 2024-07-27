#include "defenders.h"

Defenders::Defenders(int maxHP, Map* pos, int consumption, int ATK)
    : Objects(maxHP, pos) {
  this->consumption = consumption;
  this->ATK = ATK;
}

void Defenders::setPic(QString str) {
  volume.setRect(x, y, 60, 60);
  pic.load(str);
}

int Defenders::get_consumption() { return consumption; }
int Defenders::get_ATK() { return ATK; }
void Defenders::switch_pic() { return; }
