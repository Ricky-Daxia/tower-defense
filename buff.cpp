#include "buff.h"

buff::buff(Map* pos) : Enemy(100, pos, 0) {
  setPic(":/buff0.png");
  this->times = 0;
  this->pic_num = 0;
}

bool buff::is_flyer() { return false; }
bool buff::is_enemy2() { return false; }
bool buff::is_buff() { return true; }
void buff::switch_pic(int i) { setPic(QString(":/buff%1.png").arg(i)); }

void buff::move(int i) {
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
  set_dirc(i);
  if (times == 8) {
    times = 0;
    pic_num = (pic_num + 1) % 3;
    switch_pic(pic_num);
  }
  volume.setRect(x - 30, y - 30, 120, 120);
}
