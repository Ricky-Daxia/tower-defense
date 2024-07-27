#include "map.h"

Map::Map(QWidget* parent) : QPushButton{parent} {}

Map::Map(QWidget* parent, int x, int y, int type, bool base, bool born,
         Map* next)
    : QPushButton{parent} {
  this->x = x;
  this->y = y;
  this->type = map_type(type);
  this->is_base = base;
  this->is_born = born;
  this->next = next;
  this->is_far = false;
  pushed = false;
  occupied = false;
}

void Map::set_Next(Map* next) { this->next = next; }

void Map::set_base(bool b) { this->is_base = b; }
void Map::set_born(bool b) { this->is_born = b; }
void Map::set_far(bool b) { this->is_far = b; }
int Map::get_x() { return x; }
int Map::get_y() { return y; }
Map* Map::get_next() { return next; }
int Map::get_born_type() { return int(type); }
bool Map::get_base() { return is_base; }
bool Map::get_born() { return is_born; }
bool Map::get_far() { return is_far; }
int Map::get_X() { return 385 + 60 * x; }
int Map::get_Y() { return 110 + 65 * y; }
void Map::change_occupied() { occupied = !occupied; }
