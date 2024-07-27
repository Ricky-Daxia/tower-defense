#include "enemy.h"

Enemy::Enemy(int maxHP, Map* pos, int ATK) : Objects(maxHP, pos) {
  this->ATK = ATK;
  this->volume.setRect(x, y, 60, 60);
  this->dirc = 0;
  this->pic_num = 0;
}

void Enemy::setPic(QString str) { this->pic.load(str); }

void Enemy::move(int i) {
  if (i == 1)  // down
  {
    ++y;
    set_volume();
  }
  if (i == 2)  // up
  {
    --y;
    set_volume();
  }
  if (i == 3)  // left
  {
    --x;
    set_volume();
  }
  if (i == 4)  // right
  {
    ++x;
    set_volume();
  }
}

int Enemy::getHP() { return curHP; }
void Enemy::eraseHP() { is_alive = false; }
int Enemy::get_ATK() { return ATK; }
void Enemy::switch_pic(int i) { return; }
