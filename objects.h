#ifndef OBJECTS_H
#define OBJECTS_H

#include <QObject>

#include "map.h"

class Objects {
 public:
  Objects(int, Map*);
  // virtual ~Objects();
  virtual void setPic(QString) = 0;
  int get_x();
  int get_y();
  int get_line();
  int get_row();
  void change_line(int);
  void change_row(int);
  QPixmap getPic();
  bool get_alive();
  QRect get_volume();
  void set_volume();
  virtual void attacked(int);
  void add_hp(int);
  int get_curHP();
  int get_maxHP();
  Map* get_pos();
  int get_width();
  int get_height();
  void set_dirc(int);
  int get_dirc();
  void change_rect();
  bool is_show();

 protected:
  int maxHP;
  bool is_alive;
  Map* position;
  int curHP;
  QRect volume;
  int x;
  int y;
  int line;
  int row;
  QPixmap pic;
  int pic_num;
  int dirc;
  bool show_rect;
};

#endif  // OBJECTS_H
