#include "bullet.h"

Bullet::Bullet(int x, int y, int dirc, Defenders* launcher) {
  this->x = x;
  this->y = y;
  this->dirc = dirc;
  volume.setRect(x, y, 20, 10);
  pic.load(":/bullet.png");
  this->launcher = launcher;
}

void Bullet::move(int i) {
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
  volume.setRect(x, y, 20, 10);
}

int Bullet::get_dirc() { return dirc; }
QRect Bullet::get_volume() { return volume; }
int Bullet::get_x() { return x; }
int Bullet::get_y() { return y; }
QPixmap Bullet::get_pic() { return pic; }
Defenders* Bullet::get_launcher() { return launcher; }
