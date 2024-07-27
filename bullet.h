#ifndef BULLET_H
#define BULLET_H

#include "baseattacker3.h"

class Bullet {
 public:
  Bullet(int, int, int, Defenders*);
  void move(int);  //移动
  int get_dirc();
  QRect get_volume();
  int get_x();
  int get_y();
  QPixmap get_pic();
  Defenders* get_launcher();

 protected:
  int dirc;      //子弹有朝向
  QRect volume;  //子弹体积
  int x;         //坐标
  int y;
  QPixmap pic;          //贴图
  Defenders* launcher;  //子弹的发射者
};

#endif  // BULLET_H
