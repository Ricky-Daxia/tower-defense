#include "towerdefence.h"

#include <QDebug>

#include "ui_towerdefence.h"
int TowerDefence::num = 0;

vector<bool> TowerDefence::decide(Defenders* d, Enemy* e) {
  bool defender_atk = false, enemy_atk = false;
  if (d->is_attacker()) {  //我方近战只攻击敌方近战
    defender_atk = true;
    if (!e->is_enemy2() && !e->is_flyer()) enemy_atk = true;
  } else if (d->is_nut())
    defender_atk = true;  //坚果只能挨揍
  else if (d->is_attacker3()) {
    if (!e->is_flyer()) enemy_atk = true;  //远程单位能碰得到的一定会攻击
    if (e->is_enemy2() || e->is_flyer())
      defender_atk = true;     //被敌方远程和飞行单位攻击
  } else if (d->is_tower()) {  //塔只和飞行单位贴贴
    if (e->is_flyer()) {
      defender_atk = true;
      enemy_atk = true;
    }
  }
  return {defender_atk, enemy_atk};
}

vector<int> ReadMap(QWidget* parent, const QString& file_name,
                    vector<vector<Map*>>& maps,
                    vector<vector<int>>& far_cordinates) {
  int row = 0, line = 0;
  QFile map_file(file_name);
  map_file.open(QFile::ReadOnly);
  if (!map_file.isOpen()) {
    emit QMessageBox::warning(parent, "错误!", "打开资源文件失败!");
  } else {
    QByteArray all = map_file.readAll();
    QJsonDocument map_doc = QJsonDocument::fromJson(all);
    QJsonObject map_obj = map_doc.object();
    QStringList map_keys = map_obj.keys();
    //第一次遍历 完善主要路径
    for (const auto& k : map_keys) {
      if (k == "row") {
        row = map_obj.value(k).toString().toInt();
      } else if (k == "line") {
        line = map_obj.value(k).toString().toInt();
      } else if (k == "land_route") {
        if (map_obj.value(k).isArray()) {
          vector<Map*> land_routes;
          QJsonArray land_route = map_obj.value(k).toArray();
          foreach (QJsonValue rs, land_route) {
            // r是qjsonobject类型
            foreach (QJsonValue r, rs.toArray()) {
              land_routes.push_back(
                  new Map(parent, r.toObject().value("x").toString().toInt(),
                          r.toObject().value("y").toString().toInt(), 1, false,
                          false, nullptr));
            }
            maps.push_back(land_routes);
          }
        }
      } else if (k == "air_route") {
        if (map_obj.value(k).isArray()) {
          vector<Map*> air_routes;
          QJsonArray air_route = map_obj.value(k).toArray();
          foreach (QJsonValue rs, air_route) {
            // r是qjsonobject类型
            foreach (QJsonValue r, rs.toArray()) {
              air_routes.push_back(
                  new Map(parent, r.toObject().value("x").toString().toInt(),
                          r.toObject().value("y").toString().toInt(), 2, false,
                          false, nullptr));
            }
            maps.push_back(air_routes);
          }
        }
      } else if (k == "far") {
        if (map_obj.value(k).isArray()) {
          foreach (const auto& c, map_obj.value(k).toArray()) {
            far_cordinates.push_back(
                {c.toObject().value("x").toString().toInt(),
                 c.toObject().value("y").toString().toInt()});
            maps.push_back(
                {new Map(parent, c.toObject().value("x").toString().toInt(),
                         c.toObject().value("y").toString().toInt(), 2, false,
                         false, nullptr)});
          }
        }
      }
    }
    //第二次遍历 完善地图格信息
    for (const auto& k : map_keys) {
      if (k == "base" || k == "born" || k == "far") {
        foreach (const auto& r, map_obj.value(k).toArray()) {
          for (auto& m : maps) {
            for (auto& n : m) {
              if (n->get_x() == r.toObject().value("x").toString().toInt() &&
                  n->get_y() == r.toObject().value("y").toString().toInt()) {
                if (k == "base") n->set_base(true);
                if (k == "born") n->set_born(true);
                if (k == "far") n->set_far(true);
              }
            }
          }
        }
      }
    }
    //设置路线
    for (auto& m : maps) {
      for (int i = 0; i < int(m.size() - 1); ++i) {
        m.at(i)->set_Next(m.at(i + 1));
      }
    }
  }
  map_file.close();
  return {row, line};
}

void TowerDefence::setBlock() {
  cur_energy = 0;
  ui->label->setText(QString::number(0));
  defender_units = {};
  enemy_units = {};

  //基础近战单位
  QImage* baseattacker = new QImage(":/attacker_one0.png");
  ui->label_3->setGeometry(1055, 100, 60, 60);
  baseattacker->scaled(ui->label_3->size(),
                       Qt::KeepAspectRatio);  //缩放填充
  baseattacker->scaled(ui->label_3->size(),
                       Qt::IgnoreAspectRatio);  //饱满填充
  ui->label_3->setScaledContents(true);         //开启图片适应label大小
  ui->label_3->setPixmap(QPixmap::fromImage(*baseattacker));

  ui->label_4->setGeometry(1055, 100 + 65, 100, 30);

  //远程单位
  QImage* baseattacker2 = new QImage(":/tower3.png");
  ui->label_5->setGeometry(1055, 100 + 65 + 50, 60, 60);
  baseattacker2->scaled(ui->label_5->size(),
                        Qt::KeepAspectRatio);  //缩放填充
  baseattacker2->scaled(ui->label_5->size(),
                        Qt::IgnoreAspectRatio);  //饱满填充
  ui->label_5->setScaledContents(true);          //开启图片适应label大小
  ui->label_5->setPixmap(QPixmap::fromImage(*baseattacker2));

  ui->label_6->setGeometry(1055, 100 + 65 + 50 + 65, 100, 30);
  ui->label_6->setText(QString("Energy:3"));

  //阻拦单位
  QImage* nut = new QImage(":/nuts.png");
  ui->label_7->setGeometry(1055, 100 + 65 + 50 + 65 + 50, 60, 60);
  nut->scaled(ui->label_5->size(),
              Qt::KeepAspectRatio);  //缩放填充
  nut->scaled(ui->label_5->size(),
              Qt::IgnoreAspectRatio);    //饱满填充
  ui->label_7->setScaledContents(true);  //开启图片适应label大小
  ui->label_7->setPixmap(QPixmap::fromImage(*nut));

  ui->label_8->setGeometry(1055, 100 + 65 + 50 + 65 + 50 + 65, 100, 30);
  ui->label_8->setText(QString("Energy:2"));

  //基础远程单位
  QImage* baseattacker3 = new QImage(":/tofu.png");
  ui->label_9->setGeometry(1055, 100 + 65 + 50 + 65 + 50 + 65 + 50, 60, 60);
  baseattacker3->scaled(ui->label_9->size(),
                        Qt::KeepAspectRatio);  //缩放填充
  baseattacker3->scaled(ui->label_9->size(),
                        Qt::IgnoreAspectRatio);  //饱满填充
  ui->label_9->setScaledContents(true);          //开启图片适应label大小
  ui->label_9->setPixmap(QPixmap::fromImage(*baseattacker3));

  ui->label_10->setGeometry(1055, 100 + 65 + 50 + 65 + 50 + 65 + 50 + 65, 100,
                            30);
  ui->label_10->setText(QString("Energy:2"));

  //铲子
  QImage* shovel = new QImage(":/shovel.png");
  ui->label_11->setGeometry(1160, 20, 60, 60);
  shovel->scaled(ui->label_11->size(), Qt::KeepAspectRatio);
  shovel->scaled(ui->label_11->size(), Qt::IgnoreAspectRatio);
  ui->label_11->setScaledContents(true);
  ui->label_11->setPixmap(QPixmap::fromImage(*shovel));
}

void TowerDefence::mousePressEvent(QMouseEvent* ev) {
  //判断鼠标点击位置是否在单位卡槽上
  if (ev->pos().x() > ui->label_3->x() &&
      ev->pos().x() < ui->label_3->x() + 60 &&
      ev->pos().y() > ui->label_3->y() + 30 &&
      ev->pos().y() < ui->label_3->y() + 60 + 30) {
    has_base_attacker = true;
    has_tower = false;
    has_nut = false;
    has_base_attacker3 = false;
    has_shovel = false;
  } else if (ev->pos().x() > ui->label_5->x() &&
             ev->pos().x() < ui->label_5->x() + 60 &&
             ev->pos().y() > ui->label_5->y() + 30 &&
             ev->pos().y() < ui->label_5->y() + 60 + 30) {
    has_tower = true;
    has_base_attacker = false;
    has_nut = false;
    has_base_attacker3 = false;
    has_shovel = false;
  } else if (ev->pos().x() > ui->label_7->x() &&
             ev->pos().x() < ui->label_7->x() + 60 &&
             ev->pos().y() > ui->label_7->y() + 30 &&
             ev->pos().y() < ui->label_7->y() + 60 + 30) {
    has_nut = true;
    has_base_attacker = false;
    has_tower = false;
    has_base_attacker3 = false;
    has_shovel = false;
  } else if (ev->pos().x() > ui->label_9->x() &&
             ev->pos().x() < ui->label_9->x() + 60 &&
             ev->pos().y() > ui->label_9->y() + 30 &&
             ev->pos().y() < ui->label_9->y() + 60 + 30) {
    has_base_attacker3 = true;
    has_nut = false;
    has_base_attacker = false;
    has_tower = false;
    has_shovel = false;
  } else if (ev->pos().x() > ui->label_11->x() &&
             ev->pos().x() < ui->label_11->x() + 60 &&
             ev->pos().y() > ui->label_11->y() + 30 &&
             ev->pos().y() < ui->label_11->y() + 60 + 30) {
    has_base_attacker3 = false;
    has_nut = false;
    has_base_attacker = false;
    has_tower = false;
    has_shovel = true;
  } else {  //尝试判定点击位置是否为某个单位 如果是则要画出攻击范围
    int mouse_x = ev->pos().x(), mouse_y = ev->pos().y();
    for (auto& u : defender_units) {
      if (mouse_x >= u->get_x() && mouse_x <= u->get_x() + 60 &&
          mouse_y >= u->get_y() && mouse_y <= u->get_y() + 60)
        u->change_rect();
    }
    for (auto& u : enemy_units) {
      if (mouse_x >= u->get_x() && mouse_x <= u->get_x() + 60 &&
          mouse_y >= u->get_y() && mouse_y <= u->get_y() + 60)
        u->change_rect();
    }
  }
  //部署单位 减少能量+设置朝向+改变当前格子状态
  if (has_base_attacker) {
    for (auto& m : main_map) {
      for (auto& n : m) {
        if (ev->pos().x() > n->get_X() && ev->pos().x() < n->get_X() + 75 &&
            ev->pos().y() > n->get_Y() && ev->pos().y() < n->get_Y() + 75 &&
            !n->get_base() && !n->get_born() && !n->occupied && !n->get_far() &&
            n->get_born_type() == 1) {
          qDebug() << "planted";
          BaseAttacker* unit = new BaseAttacker(n);
          if (cur_energy >= unit->get_consumption()) {
            n->change_occupied();
            if (n->get_next()->get_X() < n->get_X())
              unit->set_dirc(4);
            else
              unit->set_dirc(2);
            has_base_attacker = false;
            cur_energy -= unit->get_consumption();
            defender_units.push_back(unit);
          }
          return;
        }
      }
    }
  } else if (has_tower) {
    for (auto& m : main_map) {
      for (auto& n : m) {
        if (ev->pos().x() > n->get_X() && ev->pos().x() < n->get_X() + 75 &&
            ev->pos().y() > n->get_Y() && ev->pos().y() < n->get_Y() + 75 &&
            !n->get_base() && !n->get_born() && !n->occupied && n->get_far() &&
            n->get_born_type() == 2) {
          qDebug() << "planted";
          Tower* unit = new Tower(n);
          if (cur_energy >= unit->get_consumption()) {
            n->change_occupied();
            unit->set_dirc(0);
            has_tower = false;
            cur_energy -= unit->get_consumption();
            defender_units.push_back(unit);
          }
          return;
        }
      }
    }
  } else if (has_nut) {
    for (auto& m : main_map) {
      for (auto& n : m) {
        if (ev->pos().x() > n->get_X() && ev->pos().x() < n->get_X() + 75 &&
            ev->pos().y() > n->get_Y() && ev->pos().y() < n->get_Y() + 75 &&
            !n->get_base() && !n->get_born() && !n->occupied && !n->get_far() &&
            n->get_born_type() == 1) {
          qDebug() << "planted";
          Nut* unit = new Nut(n);
          if (cur_energy >= unit->get_consumption()) {
            n->change_occupied();
            if (n->get_next()->get_X() < n->get_X())
              unit->set_dirc(4);
            else
              unit->set_dirc(2);
            has_nut = false;
            cur_energy -= unit->get_consumption();
            defender_units.push_back(unit);
          }
          return;
        }
      }
    }
  } else if (has_base_attacker3) {
    for (auto& m : main_map) {
      for (auto& n : m) {
        if (ev->pos().x() > n->get_X() && ev->pos().x() < n->get_X() + 75 &&
            ev->pos().y() > n->get_Y() && ev->pos().y() < n->get_Y() + 75 &&
            !n->get_base() && !n->get_born() && !n->occupied && !n->get_far() &&
            n->get_born_type() == 1) {
          qDebug() << "planted";
          BaseAttacker3* unit = new BaseAttacker3(n);
          if (cur_energy >= unit->get_consumption()) {
            n->change_occupied();
            if (n->get_next()->get_X() < n->get_X())
              unit->set_dirc(4);
            else
              unit->set_dirc(2);
            has_base_attacker3 = false;
            cur_energy -= unit->get_consumption();
            defender_units.push_back(unit);
          }
          return;
        }
      }
    }
  } else if (has_shovel) {
    //移除单位 复用显示攻击距离的代码
    int mouse_x = ev->pos().x(), mouse_y = ev->pos().y();
    for (auto& u : defender_units) {
      if (mouse_x >= u->get_x() && mouse_x <= u->get_x() + 60 &&
          mouse_y >= u->get_y() && mouse_y <= u->get_y() + 60)
        u->attacked(1000);
    }
    for (auto& u : enemy_units) {
      if (mouse_x >= u->get_x() && mouse_x <= u->get_x() + 60 &&
          mouse_y >= u->get_y() && mouse_y <= u->get_y() + 60)
        u->attacked(1000);
    }
  }
}

void TowerDefence::paintEvent(QPaintEvent* ev) {
  QPainter painter(this);
  painter.setPen(QColor(255, 0, 0));
  //设置背景贴图
  for (int i = 0; i < line; ++i) {
    for (int j = 0; j < row; ++j) {
      bool is_empty = true;
      for (auto& m : main_map) {
        for (auto& n : m) {
          if (i == n->get_y() && j == n->get_x()) is_empty = false;
          if (i == n->get_y() && j == n->get_x() && n->get_born()) {
            painter.drawPixmap(QPoint(n->get_X(), n->get_Y()),
                               QPixmap(":/born.png"));
          }
          if (i == n->get_y() && j == n->get_x() && n->get_base()) {
            painter.drawPixmap(QPoint(n->get_X(), n->get_Y()),
                               QPixmap(":/male.png"));
          }
          if (i == n->get_y() && j == n->get_x() && n->get_far()) {
            painter.drawPixmap(QPoint(n->get_X(), n->get_Y()),
                               QPixmap(":/far.png"));
          }
        }
      }
      if (is_empty) {
        painter.drawPixmap(QPoint(385 + 60 * j, 110 + 65 * i),
                           QPixmap(":/no.png"));
      }
    }
  }

  //绘制我方单位

  for (int i = 0; i < int(defender_units.size()); ++i) {
    if (defender_units[i]->get_alive()) {
      painter.drawPixmap(
          QPoint(defender_units[i]->get_x(), defender_units[i]->get_y()),
          defender_units[i]->getPic());
      //绘制血条
      double ratio =
          defender_units[i]->get_curHP() * 1.0 / defender_units[i]->get_maxHP();
      painter.fillRect(QRect(defender_units[i]->get_x(),
                             defender_units[i]->get_y() - 10, ratio * 60, 5),
                       Qt::green);
      if (defender_units[i]->is_show()) {
        painter.drawRect(defender_units[i]->get_volume());
      }
    }
  }

  //绘制敌方单位
  for (int i = 0; i < int(enemy_units.size()); ++i) {
    if (enemy_units[i]->get_alive()) {
      painter.drawPixmap(
          QPoint(enemy_units[i]->get_x(), enemy_units[i]->get_y()),
          enemy_units[i]->getPic());
      //绘制血条
      double ratio2 =
          enemy_units[i]->get_curHP() * 1.0 / enemy_units[i]->get_maxHP();
      painter.fillRect(QRect(enemy_units[i]->get_x(),
                             enemy_units[i]->get_y() - 10, ratio2 * 60, 5),
                       Qt::red);
      if (enemy_units[i]->is_show()) {
        painter.drawRect(enemy_units[i]->get_volume());
      }

      bool done = false;

      for (auto& m : main_map) {
        if (!done)
          for (auto& n : m) {
            if (!done) {
              if (enemy_units[i]->get_row() == n->get_x() &&
                  enemy_units[i]->get_line() == n->get_y()) {
                if (n->get_base()) {
                  enemy_units[i]->eraseHP();
                  qDebug() << "Invasion!";
                  done = true;
                  break;
                }  //在base时
                //互相攻击
                for (const auto& d : defender_units) {
                  if (d->get_alive() && d->get_volume().intersects(
                                            enemy_units[i]->get_volume())) {
                    vector<bool> is_atk = decide(d, enemy_units[i]);
                    if (is_atk[0]) {
                      d->attacked(enemy_units[i]->get_ATK());
                      qDebug() << "defender attacked!"
                               << " curHP:" << d->get_curHP();
                    }
                    if (is_atk[1]) {
                      if (d->is_attacker())
                        d->switch_pic();  //基础近战单位的攻击特效
                      //如果是远程单位攻击 应该射出子弹
                      //子弹碰到敌方单位的时候扣血
                      if (d->is_attacker3()) {
                        bool has_bullet = false;
                        for (int k = 0; k < int(bullets.size()); ++k) {
                          if (bullets[k]->get_launcher() == d)
                            has_bullet = true;
                        }
                        if (!has_bullet)
                          bullets.push_back(new Bullet(
                              d->get_x(), d->get_y(), d->get_dirc(),
                              d));  //当前单位没有射出过子弹的时候 生成一个子弹
                      } else {  //其余情况
                        if (d->is_tower()) {
                          QPen pen(QColor(0, 0, 255));
                          pen.setWidth(5);
                          painter.setPen(pen);
                          painter.drawLine(
                              QPoint(d->get_x(), d->get_y()),
                              QPoint(enemy_units[i]->get_x() + 30,
                                     enemy_units[i]->get_y() + 30));
                        }
                        enemy_units[i]->attacked(d->get_ATK());
                        qDebug() << "enemy attacked!"
                                 << " curHP:" << enemy_units[i]->get_curHP();
                      }
                    }
                    if (d->is_nut()) {
                      done = true;
                      break;
                    }
                  }
                }
                //移动
                if (!done) {
                  if (n->get_next() != nullptr &&
                      n->get_x() > n->get_next()->get_x()) {
                    //当前格x大于下一格x
                    enemy_units[i]->move(3);

                    if (n->get_next() != nullptr &&
                        enemy_units[i]->get_x() == n->get_next()->get_X() &&
                        enemy_units[i]->get_y() == n->get_next()->get_Y()) {
                      enemy_units[i]->change_row(n->get_next()->get_x());
                      enemy_units[i]->change_line(n->get_next()->get_y());
                    }
                    done = true;
                    break;
                  } else if (n->get_next() != nullptr &&
                             n->get_x() < n->get_next()->get_x()) {
                    enemy_units[i]->move(4);

                    if (n->get_next() != nullptr &&
                        enemy_units[i]->get_x() == n->get_next()->get_X() &&
                        enemy_units[i]->get_y() == n->get_next()->get_Y()) {
                      enemy_units[i]->change_row(n->get_next()->get_x());
                      enemy_units[i]->change_line(n->get_next()->get_y());
                    }
                    done = true;
                    break;
                  }
                  // x相等 看y
                  else if (n->get_next() != nullptr &&
                           n->get_y() < n->get_next()->get_y()) {
                    enemy_units[i]->move(1);

                    if (n->get_next() != nullptr &&
                        enemy_units[i]->get_x() == n->get_next()->get_X() &&
                        enemy_units[i]->get_y() == n->get_next()->get_Y()) {
                      enemy_units[i]->change_row(n->get_next()->get_x());
                      enemy_units[i]->change_line(n->get_next()->get_y());
                    }
                    done = true;
                    break;
                  } else {
                    enemy_units[i]->move(2);
                    if (n->get_next() != nullptr &&
                        enemy_units[i]->get_x() == n->get_next()->get_X() &&
                        enemy_units[i]->get_y() == n->get_next()->get_Y()) {
                      enemy_units[i]->change_row(n->get_next()->get_x());
                      enemy_units[i]->change_line(n->get_next()->get_y());
                    }
                    done = true;
                    break;
                  }
                }
              }
            }
          }
      }
    }
  }

  // buff加血
  for (auto& e : enemy_units) {
    if (e->is_buff()) {
      for (auto& ee : enemy_units) {
        if (e->get_volume().intersects(ee->get_volume()) && !ee->is_buff())
          ee->add_hp(1);
      }
    }
  }
  //子弹的逻辑
  for (int i = 0; i < int(bullets.size()); ++i) {
    bullets[i]->move(bullets[i]->get_dirc());

    for (int j = 0; j < int(enemy_units.size()); ++j) {
      if (bullets[i]->get_volume().intersects(enemy_units[j]->get_volume())) {
        enemy_units[j]->attacked(50);
        bullets.erase(bullets.begin() + i);
        if (!enemy_units[j]->get_alive()) {
          enemy_units.erase(enemy_units.begin() + j);
          break;
        }
        break;
      }

      painter.drawPixmap(bullets[i]->get_x(), bullets[i]->get_y(),
                         bullets[i]->get_pic());
    }
  }  //尝试绘图子弹
}

void TowerDefence::Play() {
  QSound* bgm = new QSound(":/music.wav");
  bgm->play();
  bgm->setLoops(-1);
  //能量条计时器

  // QTimer* Energy_Timer = new QTimer(this);
  // 把计时器作为主类的对象，防止暂停时崩溃
  Energy_Timer->start(10);

  connect(ui->Stop, &QPushButton::clicked, this, [&]() {
    if (Energy_Timer->isActive()) {
      Energy_Timer->stop();
      ui->Stop->setStyleSheet(
          "QPushButton{background-image: url(:/start.png);}");
    } else {
      Energy_Timer->start(10);
      ui->Stop->setStyleSheet(
          "QPushButton{background-image: url(:/pause.png);}");
    }
  });

  connect(Energy_Timer, &QTimer::timeout, this, [&]() {
    if (num != 0 && num % 100 == 0) {
      ++cur_energy;
    }
    ui->label->setText(QString::number(cur_energy));
    ++num;
    //生成敌方单位
    if (num == 200) {
      num = 0;
      for (int i = 0; i < int(born_spot.size()); ++i) {
        if (cur_energy % 3 == i) {
          qDebug() << "cur_energy:" << cur_energy;
          if (int(enemy_units.size()) > 0 && cur_energy % 4 == 0 &&
              born_spot[i]->get_born_type() == 2)
            enemy_units.push_back(new Flyer(born_spot[i]));
          else if (int(enemy_units.size()) && int(cur_energy % 2 == 0) &&
                   born_spot[i]->get_born_type() == 1) {
            enemy_units.push_back(new BaseEnemy2(born_spot[i]));
          } else if (cur_energy % 1 == 0 && born_spot[i]->get_born_type() == 1)
            enemy_units.push_back(new buff(born_spot[i]));
          else if (born_spot[i]->get_born_type() == 1)
            enemy_units.push_back(new BaseEnemy(born_spot[i]));
        }
      }
    }
    update();
  });
}

TowerDefence::TowerDefence(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::TowerDefence) {
  ui->setupUi(this);
  ui->Stop->setStyleSheet("QPushButton{background-image: url(:/pause.png);}");
  QPalette background = this->palette();  //设置调色板
  QPixmap background_img(":/beginning.png");
  background.setBrush(QPalette::Window, QBrush(background_img));
  this->setPalette(background);

  main_map = {}, has_base_attacker = false, has_tower = false, has_nut = false,
  has_base_attacker3 = false, bullets = {}, has_shovel = false,
  Energy_Timer = new QTimer(this), far_cordinates = {}, born_spot = {},
  base_spot = {};

  //菜单栏
  QMenuBar* bar = menuBar();
  setMenuBar(bar);
  QMenu* option = bar->addMenu("选项");
  QAction* play_with_map_1 =
      option->addAction("Play with map1!");  //尝试在选项里添加不同的地图选项
  QAction* play_with_map_2 = option->addAction("Play with map2!");
  QAction* exit_action = option->addAction("Exit!");
  option->addSeparator();

  //连接菜单信号
  connect(play_with_map_1, &QAction::triggered, this, [&]() {
    QString path = QFileDialog::getOpenFileName(this, "选取地图文件",
                                                "D:\\Proj2\\phase_1_1");
    vector<int> ret = ReadMap(this, path, main_map, far_cordinates);
    row = ret[0], line = ret[1];

    for (auto& m : main_map) {
      for (auto& n : m) {
        if (n->get_base() && !n->pushed) {
          base_spot.push_back(n);
          n->pushed = true;
        }
        if (n->get_born() && !n->pushed) {
          born_spot.push_back(n);
          n->pushed = true;
        }
      }
    }  //设置出生点和大本营

    //设置背景
    QPalette background = this->palette();  //设置调色板
    QPixmap background_img(":/map1.jpg");
    background.setBrush(QPalette::Window, QBrush(background_img));
    this->setPalette(background);

    setBlock();
    Play();
  });

  connect(play_with_map_2, &QAction::triggered, this, [&]() {
    QString path = QFileDialog::getOpenFileName(this, "选取地图文件",
                                                "D:\\Proj2\\phase_1_1");
    vector<int> ret = ReadMap(this, path, main_map, far_cordinates);
    row = ret[0], line = ret[1];

    for (auto& m : main_map) {
      for (auto& n : m) {
        if (n->get_base() && !n->pushed) {
          base_spot.push_back(n);
          n->pushed = true;
        }
        if (n->get_born() && !n->pushed) {
          born_spot.push_back(n);
          n->pushed = true;
        }
      }
    }  //设置出生点和大本营

    //设置背景
    QPalette background = this->palette();  //设置调色板
    QPixmap background_img(":/map2.jpg");
    background.setBrush(QPalette::Window, QBrush(background_img));
    this->setPalette(background);

    setBlock();
    Play();
  });

  connect(exit_action, &QAction::triggered, this, &TowerDefence::close);
}

TowerDefence::~TowerDefence() { delete ui; }
