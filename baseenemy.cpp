#include "baseenemy.h"

BaseEnemy::BaseEnemy(Map* pos) : Enemy(100, pos, 1) {
  setPic(":/sprite0.png");
  this->pic_num = 0;
  this->times = 0;
}

bool BaseEnemy::is_flyer() { return false; }
bool BaseEnemy::is_enemy2() { return false; }
bool BaseEnemy::is_buff() { return false; }

void BaseEnemy::switch_pic(int i) { setPic(QString(":/sprite%1.png").arg(i)); }

void BaseEnemy::move(int i) {
  ++times;
  if (i == 1)  // down
  {
    ++y;
  } else if (i == 2)  // up
  {
    --y;

  } else if (i == 3)  // left
  {
    --x;

  } else if (i == 4)  // right
  {
    ++x;
  }
  set_dirc(i);        //改变朝向
  if (times == 10) {  // 更换贴图
    times = 0;
    pic_num = (pic_num + 1) % 12;
    switch_pic(pic_num);
  }
  set_volume();
}
