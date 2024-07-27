#ifndef TOWERDEFENCE_H
#define TOWERDEFENCE_H

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSound>
#include <QtGlobal>

#include "baseattacker.h"
#include "baseattacker3.h"
#include "baseenemy.h"
#include "baseenemy2.h"
#include "buff.h"
#include "bullet.h"
#include "flyer.h"
#include "map.h"
#include "nut.h"
#include "tower.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TowerDefence;
}
QT_END_NAMESPACE

class TowerDefence : public QMainWindow {
  Q_OBJECT

 public:
  TowerDefence(QWidget *parent = nullptr);
  ~TowerDefence();
  void Play();
  void setBlock();
  void paintEvent(QPaintEvent *);
  static int num;
  bool has_base_attacker;
  bool has_tower;
  bool has_nut;
  bool has_base_attacker3;
  bool has_shovel;
  void mousePressEvent(QMouseEvent *);
  vector<bool> decide(Defenders *, Enemy *);

 protected:
  vector<vector<Map *>> main_map;  //主要的路径
  int row;
  int line;
  vector<vector<int>> far_cordinates;  //可放置塔的位置
  int cur_energy;                      //能量条
  vector<Enemy *> enemy_units;         //敌方单位
  vector<Defenders *> defender_units;  //我方单位
  vector<Map *> born_spot;             //出生点
  vector<Map *> base_spot;             //大本营
  vector<Bullet *> bullets;            //子弹类
  QTimer *Energy_Timer;                //计时器

 private slots:

 private:
  Ui::TowerDefence *ui;
};
#endif  // TOWERDEFENCE_H
