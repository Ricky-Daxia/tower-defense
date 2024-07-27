#include "baseenemy2.h"

BaseEnemy2::BaseEnemy2(Map* pos) : Enemy(75, pos, 1) {
  this->setPic(PIC1);
  this->pic_num = 0;
  this->times = 0;
}

bool BaseEnemy2::is_flyer() { return false; }
bool BaseEnemy2::is_enemy2() { return true; }
bool BaseEnemy2::is_buff() { return false; }

void BaseEnemy2::switch_pic(int i) {
  switch (i) {
    case 0:
      setPic(PIC1);
      break;
    case 1:
      setPic(PIC2);
      break;
  }
}

void BaseEnemy2::move(int i) {
  ++times;
  if (i == 1)  // down
  {
    ++y;
    volume.setRect(x, y, 60, 60 + 120);
  } else if (i == 2)  // up
  {
    --y;
    volume.setRect(x, y - 120, 60, 60 + 120);
  } else if (i == 3)  // left
  {
    --x;
    volume.setRect(x - 80, y, 60 + 80, 60);
  } else if (i == 4)  // right
  {
    ++x;
    volume.setRect(x, y, 60 + 80, 60);
  }
  set_dirc(i);
  if (times == 50) {
    ++pic_num;
    times = 0;
    pic_num = pic_num % 2;
    switch_pic(pic_num);
  }
}
