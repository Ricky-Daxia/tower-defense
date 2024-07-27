#ifndef MAP_H
#define MAP_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QWidget>

using std::vector;

enum map_type { Empty, Land, Air };

class Map : public QPushButton {
  Q_OBJECT
 protected:
  int x;          // x坐标
  int y;          // y坐标
  map_type type;  //地图格的类型
  bool is_base;   //大本营
  bool is_born;   //出生点
  bool is_far;    //放塔的位置
  Map* next;      //下一个节点

 public:
  explicit Map(QWidget* parent = nullptr);
  Map(QWidget* parent, int, int, int, bool, bool,
      Map*);  //默认构造 坐标 地图格类型
  void set_Next(Map*);
  void set_base(bool);
  void set_born(bool);
  void set_far(bool);
  int get_x();
  int get_y();
  Map* get_next();
  bool get_base();
  bool get_born();
  int get_born_type();
  bool get_far();
  int get_X();  //大写代表像素坐标
  int get_Y();
  bool pushed;
  bool occupied;
  void change_occupied();
 signals:
};

#endif  // MAP_H
