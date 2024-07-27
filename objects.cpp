#include "objects.h"

Objects::Objects(int maxHP, Map* pos) {
  this->maxHP = maxHP;
  this->curHP = maxHP;
  this->is_alive = true;
  this->position = pos;
  this->x = 385 + 60 * pos->get_x();
  this->y = 110 + 65 * pos->get_y();
  this->line = pos->get_y();
  this->row = pos->get_x();
  this->pic_num = 0;
  this->dirc = 0;
  this->show_rect = false;
}

// Objects::~Objects() {}
int Objects::get_x() { return x; }
int Objects::get_y() { return y; }
int Objects::get_line() { return line; }
int Objects::get_row() { return row; }
void Objects::change_line(int line) { this->line = line; }
void Objects::change_row(int row) { this->row = row; }
QPixmap Objects::getPic() { return pic; }
bool Objects::get_alive() { return is_alive; }
QRect Objects::get_volume() { return volume; }
void Objects::attacked(int harm) {
  curHP -= harm;
  if (curHP <= 0) {
    this->is_alive = false;
    qDebug() << "down!";
    this->position->change_occupied();
  }
}
void Objects::add_hp(int i) {
  if (curHP < maxHP) curHP += i;
}
void Objects::set_volume() { volume.setRect(x, y, 60, 60); }
int Objects::get_curHP() { return curHP; }
int Objects::get_maxHP() { return maxHP; }
Map* Objects::get_pos() { return position; }
int Objects::get_width() { return volume.width(); }
int Objects::get_height() { return volume.height(); }
void Objects::set_dirc(int i) { this->dirc = i; }
int Objects::get_dirc() { return dirc; }
void Objects::change_rect() { show_rect = !show_rect; }
bool Objects::is_show() { return show_rect; }
