#include <QApplication>

#include "towerdefence.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TowerDefence w;
  w.show();
  //  GameScene mainscene(w);
  //  mainscene.show();
  return a.exec();
}
