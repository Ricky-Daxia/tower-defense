#include "flyer.h"

Flyer::Flyer(Map* pos) : Enemy(80, pos, 1) {
  this->setPic(":/flyer0.png");
  volume.setRect(x - 25, y - 25, 60 + 25 + 25, 60 + 25 + 25);
  this->is_attacked = false;
  this->times = 0;
}

bool Flyer::is_flyer() { return true; }
bool Flyer::is_enemy2() { return false; }
bool Flyer::is_buff() { return false; }
void Flyer::switch_pic(int i) { setPic(QString(":/flyer%1.png").arg(i)); }
void Flyer::move(int i) {
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
  if (times == 10) {
    times = 0;
    if (!is_attacked) {
      pic_num = (pic_num + 1) % 3;
      switch_pic(pic_num);
    } else
      switch_pic(3);
  }
  volume.setRect(x - 25, y - 25, 60 + 25 + 25, 60 + 25 + 25);
  is_attacked = false;
}
void Flyer::attacked(int harm) {
  Objects::attacked(harm);
  is_attacked = true;
}
