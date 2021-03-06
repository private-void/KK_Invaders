#include "mainwindow.hpp"
#include "defaultvalues.hpp"
#include <json/json.h>
#include <json/writer.h>
#include <json/reader.h>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  // Изменение размеров окна
  this->resize(800, 800);

  // Глобальная настройка шрифтов
  QApplication::setFont(QFont("Courier", 14, QFont::Bold, false));

  // Центральный виджет
  m_centralWidget = new QWidget(this);
  setCentralWidget(m_centralWidget);

  // Главная таблица
  m_layoutMain = new QGridLayout(m_centralWidget);

  // Выбор режима
  m_labelMode = new QLabel("Настройте вручную или выберите один из режимов", m_centralWidget);
  m_labelMode->setAlignment(Qt::AlignCenter);
  m_labelMode->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelMode->setStyleSheet("QLabel {color : Blue; }");

  // Верхний виджет (выбор режима)
  m_topWidget = new QWidget(m_centralWidget);
  m_radioLayout = new QHBoxLayout(m_topWidget);
  m_group = new QButtonGroup(m_topWidget);
  m_radioButtonNoob = new QRadioButton("NOOB", m_topWidget);
  m_radioButtonNormal = new QRadioButton("NORMAL", m_topWidget);
  m_radioButtonPro = new QRadioButton("PRO", m_topWidget);
  m_radioButtonCustom = new QRadioButton("CUSTOM", m_topWidget);
  m_radioButtonNoob->setStyleSheet("QRadioButton {color : SteelBlue; }");
  m_radioButtonNormal->setStyleSheet("QRadioButton {color : SteelBlue; }");
  m_radioButtonPro->setStyleSheet("QRadioButton {color : SteelBlue; }");
  m_radioButtonCustom->setStyleSheet("QRadioButton {color : SteelBlue; }");

  m_radioButtonCustom->setChecked(true);
  m_group->addButton(m_radioButtonNoob);
  m_group->addButton(m_radioButtonNormal);
  m_group->addButton(m_radioButtonPro);
  m_group->addButton(m_radioButtonCustom);
  m_radioLayout->addWidget(m_radioButtonNoob);
  m_radioLayout->addWidget(m_radioButtonNormal);
  m_radioLayout->addWidget(m_radioButtonPro);
  m_radioLayout->addWidget(m_radioButtonCustom);

  // Настройки пушки
  m_centralWidgetGun = new QWidget(m_centralWidget);
  m_layoutGun = new QGridLayout(m_centralWidgetGun);

  m_labelGun = new QLabel("Настройки пушки", m_centralWidgetGun);
  m_labelGun->setStyleSheet("QLabel {color : DarkOliveGreen; }");
  m_labelGun->setAlignment(Qt::AlignCenter);
  m_labelGunHP = new QLabel("HP:", m_centralWidgetGun);
  m_sliderGunHP = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunHP->setRange(GUN_HP_MIN, GUN_HP_MAX);
  m_labelValueGunHP = new QLabel(std::to_string(m_sliderGunHP->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunHP->setAlignment(Qt::AlignRight);
  connect(m_sliderGunHP, SIGNAL(valueChanged(int)), m_labelValueGunHP, SLOT(setNum(int)));

  m_labelGunFiringRate = new QLabel("Скорость перезарядки:", m_centralWidgetGun);
  m_sliderGunFiringRate = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunFiringRate->setRange(GUN_FIRING_RATE_MIN, GUN_FIRING_RATE_MAX);
  m_labelValueGunFiringRate = new QLabel(std::to_string(m_sliderGunFiringRate->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunFiringRate->setAlignment(Qt::AlignRight);
  connect(m_sliderGunFiringRate, SIGNAL(valueChanged(int)), m_labelValueGunFiringRate, SLOT(setNum(int)));

  m_labelGunSpeed = new QLabel("Скорость:", m_centralWidgetGun);
  m_sliderGunSpeed  = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunSpeed->setRange(GUN_SPEED_MIN, GUN_SPEED_MAX);

  m_labelValueGunSpeed = new QLabel(std::to_string(m_sliderGunSpeed->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunSpeed->setAlignment(Qt::AlignRight);
  connect(m_sliderGunSpeed, SIGNAL(valueChanged(int)), m_labelValueGunSpeed, SLOT(setNum(int)));

  m_labelGunNumberOfLives = new QLabel("Начальное число жизней:", m_centralWidgetGun);
  m_sliderGunNumberOfLives  = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunNumberOfLives->setRange(GUN_NUMBER_OF_LIVES_MIN, GUN_NUMBER_OF_LIVES_MAX);
  m_labelValueGunNumberOfLives = new QLabel(std::to_string(m_sliderGunNumberOfLives->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunNumberOfLives->setAlignment(Qt::AlignRight);
  connect(m_sliderGunNumberOfLives, SIGNAL(valueChanged(int)), m_labelValueGunNumberOfLives, SLOT(setNum(int)));

  m_layoutGun->addWidget(m_labelGun, 0, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunHP, 1, 0);
  m_layoutGun->addWidget(m_labelValueGunHP, 1, 1);
  m_layoutGun->addWidget(m_sliderGunHP, 2, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunFiringRate, 3, 0);
  m_layoutGun->addWidget(m_labelValueGunFiringRate, 3, 1);
  m_layoutGun->addWidget(m_sliderGunFiringRate, 4, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunSpeed, 5, 0);
  m_layoutGun->addWidget(m_labelValueGunSpeed, 5, 1);
  m_layoutGun->addWidget(m_sliderGunSpeed, 6, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunNumberOfLives, 7, 0);
  m_layoutGun->addWidget(m_labelValueGunNumberOfLives, 7, 1);
  m_layoutGun->addWidget(m_sliderGunNumberOfLives, 8, 0, 1, 2);

  // Настройки пришельцев
  m_centralWidgetAlien = new QWidget(m_centralWidget);
  m_layoutAlien = new QGridLayout(m_centralWidgetAlien);

  m_labelAlien = new QLabel("Настройки пришельцов", m_centralWidgetAlien);
  m_labelAlien->setStyleSheet("QLabel {color : DarkOliveGreen; }");
  m_labelAlien->setAlignment(Qt::AlignCenter);
  m_labelAlienHP = new QLabel("HP:", m_centralWidgetAlien);
  m_sliderAlienHP = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienHP->setRange(ALIEN_HP_MIN, ALIEN_HP_MAX);
  m_labelValueAlienHP = new QLabel(std::to_string(m_sliderAlienHP->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienHP->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienHP, SIGNAL(valueChanged(int)), m_labelValueAlienHP, SLOT(setNum(int)));

  m_labelAlienFiringRate = new QLabel("Скорость перезарядки:", m_centralWidgetAlien);
  m_sliderAlienFiringRate = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienFiringRate->setRange(ALIEN_FIRING_RATE_MIN, ALIEN_FIRING_RATE_MAX);
  m_labelValueAlienFiringRate = new QLabel(std::to_string(m_sliderAlienFiringRate->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienFiringRate->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienFiringRate, SIGNAL(valueChanged(int)), m_labelValueAlienFiringRate, SLOT(setNum(int)));

  m_labelAlienSpeed = new QLabel("Скорость:", m_centralWidgetAlien);
  m_sliderAlienSpeed = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienSpeed->setRange(ALIEN_SPEED_MIN, ALIEN_SPEED_MAX);
  m_labelValueAlienSpeed = new QLabel(std::to_string(m_sliderAlienSpeed->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienSpeed->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienSpeed, SIGNAL(valueChanged(int)), m_labelValueAlienSpeed, SLOT(setNum(int)));

  m_labelAlienNumberInLevel = new QLabel("Число пришельцев на уровне:", m_centralWidgetAlien);
  m_sliderAlienNumberInLevel = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienNumberInLevel->setRange(ALIEN_NUMBER_IN_LEVEL_MIN, ALIEN_NUMBER_IN_LEVEL_MAX);
  m_labelValueAlienNumberInLevel = new QLabel(std::to_string(m_sliderAlienNumberInLevel->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienNumberInLevel->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienNumberInLevel, SIGNAL(valueChanged(int)), m_labelValueAlienNumberInLevel, SLOT(setNum(int)));

  m_labelAlienNumberOfLevels = new QLabel("Число уровней:", m_centralWidgetAlien);
  m_sliderAlienNumberOfLevels = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienNumberOfLevels->setRange(ALIEN_NUMBER_OF_LEVELS_MIN, ALIEN_NUMBER_OF_LEVELS_MAX);
  m_labelValueAlienNumberOfLevels = new QLabel(std::to_string(m_sliderAlienNumberOfLevels->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienNumberOfLevels->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienNumberOfLevels, SIGNAL(valueChanged(int)), m_labelValueAlienNumberOfLevels, SLOT(setNum(int)));

  m_layoutAlien->addWidget(m_labelAlien, 0, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienHP, 1, 0);
  m_layoutAlien->addWidget(m_labelValueAlienHP, 1, 1);
  m_layoutAlien->addWidget(m_sliderAlienHP, 2, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienFiringRate, 3, 0);
  m_layoutAlien->addWidget(m_labelValueAlienFiringRate, 3, 1);
  m_layoutAlien->addWidget(m_sliderAlienFiringRate, 4, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienSpeed, 5, 0);
  m_layoutAlien->addWidget(m_labelValueAlienSpeed, 5, 1);
  m_layoutAlien->addWidget(m_sliderAlienSpeed, 6, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienNumberInLevel, 7, 0);
  m_layoutAlien->addWidget(m_labelValueAlienNumberInLevel, 7, 1);
  m_layoutAlien->addWidget(m_sliderAlienNumberInLevel, 8, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienNumberOfLevels, 9, 0);
  m_layoutAlien->addWidget(m_labelValueAlienNumberOfLevels, 9, 1);
  m_layoutAlien->addWidget(m_sliderAlienNumberOfLevels, 10, 0, 1, 2);

  // Настройки пули
  m_centralWidgetBullet = new QWidget(m_centralWidget);
  m_layoutBullet = new QGridLayout(m_centralWidgetBullet);

  m_labelBullet = new QLabel("Настройки пуль", m_centralWidgetBullet);
  m_labelBullet->setStyleSheet("QLabel {color : DarkOliveGreen; }");
  m_labelBullet->setAlignment(Qt::AlignCenter);
  m_labelBulletHP = new QLabel("HP:", m_centralWidgetBullet);
  m_sliderBulletHP = new QSlider(Qt::Horizontal, m_centralWidgetBullet);
  m_sliderBulletHP->setRange(BULLET_HP_MIN, BULLET_HP_MAX);
  m_labelValueBulletHP = new QLabel(std::to_string(m_sliderBulletHP->value()).c_str(), m_centralWidgetBullet);
  m_labelValueBulletHP->setAlignment(Qt::AlignRight);
  connect(m_sliderBulletHP, SIGNAL(valueChanged(int)), m_labelValueBulletHP, SLOT(setNum(int)));

  m_labelBulletSpeed = new QLabel("Скорость:", m_centralWidgetBullet);
  m_sliderBulletSpeed = new QSlider(Qt::Horizontal, m_centralWidgetBullet);
  m_sliderBulletSpeed->setRange(BULLET_SPEED_MIN, BULLET_SPEED_MAX);
  m_labelValueBulletSpeed = new QLabel(std::to_string(m_sliderBulletSpeed->value()).c_str(), m_centralWidgetBullet);
  m_labelValueBulletSpeed->setAlignment(Qt::AlignRight);
  connect(m_sliderBulletSpeed, SIGNAL(valueChanged(int)), m_labelValueBulletSpeed, SLOT(setNum(int)));

  m_labelBulletDamage = new QLabel("Урон:", m_centralWidgetBullet);
  m_sliderBulletDamage = new QSlider(Qt::Horizontal, m_centralWidgetBullet);
  m_sliderBulletDamage->setRange(BULLET_DAMAGE_MIN, BULLET_DAMAGE_MAX);
  m_labelValueBulletDamage = new QLabel(std::to_string(m_sliderBulletDamage->value()).c_str(), m_centralWidgetBullet);
  m_labelValueBulletDamage->setAlignment(Qt::AlignRight);
  connect(m_sliderBulletDamage, SIGNAL(valueChanged(int)), m_labelValueBulletDamage, SLOT(setNum(int)));

  m_layoutBullet->addWidget(m_labelBullet, 0, 0, 1, 2);
  m_layoutBullet->addWidget(m_labelBulletHP, 1, 0);
  m_layoutBullet->addWidget(m_labelValueBulletHP, 1, 1);
  m_layoutBullet->addWidget(m_sliderBulletHP, 2, 0, 1, 2);
  m_layoutBullet->addWidget(m_labelBulletSpeed, 3, 0);
  m_layoutBullet->addWidget(m_labelValueBulletSpeed, 3, 1);
  m_layoutBullet->addWidget(m_sliderBulletSpeed, 4, 0, 1, 2);
  m_layoutBullet->addWidget(m_labelBulletDamage, 5, 0);
  m_layoutBullet->addWidget(m_labelValueBulletDamage, 5, 1);
  m_layoutBullet->addWidget(m_sliderBulletDamage, 6, 0, 1, 2);

  // Настройки препятствий
  m_centralWidgetObstacle = new QWidget(m_centralWidget);
  m_layoutObstacle = new QGridLayout(m_centralWidgetObstacle);

  m_labelObstacle = new QLabel("Настройки препятствий", m_centralWidgetObstacle);
  m_labelObstacle->setStyleSheet("QLabel {color : DarkOliveGreen; }");
  m_labelObstacle->setAlignment(Qt::AlignCenter);
  m_labelObstacleHP = new QLabel("HP:", m_centralWidgetObstacle);
  m_sliderObstacleHP = new QSlider(Qt::Horizontal, m_centralWidgetObstacle);
  m_sliderObstacleHP->setRange(OBSTACLE_HP_MIN, OBSTACLE_HP_MAX);
  m_labelValueObstacleHP = new QLabel(std::to_string(m_sliderObstacleHP->value()).c_str(), m_centralWidgetObstacle);
  m_labelValueObstacleHP->setAlignment(Qt::AlignRight);
  connect(m_sliderObstacleHP, SIGNAL(valueChanged(int)), m_labelValueObstacleHP, SLOT(setNum(int)));

  m_labelObstacleNumberInGroup = new QLabel("Число препятствий в группе:", m_centralWidgetObstacle);
  m_sliderObstacleNumberInGroup  = new QSlider(Qt::Horizontal, m_centralWidgetObstacle);
  m_sliderObstacleNumberInGroup->setRange(OBSTACLE_NUMBER_IN_GROUP_MIN, OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_labelValueObstacleNumberInGroup = new QLabel(std::to_string(m_sliderObstacleNumberInGroup->value()).c_str(), m_centralWidgetObstacle);
  m_labelValueObstacleNumberInGroup->setAlignment(Qt::AlignRight);
  connect(m_sliderObstacleNumberInGroup, SIGNAL(valueChanged(int)), m_labelValueObstacleNumberInGroup, SLOT(setNum(int)));

  m_labelObstacleNumberOfGroups = new QLabel("Число групп:", m_centralWidgetObstacle);
  m_sliderObstacleNumberOfGroups = new QSlider(Qt::Horizontal, m_centralWidgetObstacle);
  m_sliderObstacleNumberOfGroups->setRange(OBSTACLE_NUMBER_OF_GROUPS_MIN, OBSTACLE_NUMBER_OF_GROUPS_MAX);
  m_labelValueObstacleNumberOfGroups = new QLabel(std::to_string(m_sliderObstacleNumberOfGroups->value()).c_str(), m_centralWidgetObstacle);
  m_labelValueObstacleNumberOfGroups->setAlignment(Qt::AlignRight);
  connect(m_sliderObstacleNumberOfGroups, SIGNAL(valueChanged(int)), m_labelValueObstacleNumberOfGroups, SLOT(setNum(int)));

  m_layoutObstacle->addWidget(m_labelObstacle, 0, 0, 1, 2);
  m_layoutObstacle->addWidget(m_labelObstacleHP, 1, 0);
  m_layoutObstacle->addWidget(m_labelValueObstacleHP, 1, 1);
  m_layoutObstacle->addWidget(m_sliderObstacleHP, 2, 0, 1, 2);
  m_layoutObstacle->addWidget(m_labelObstacleNumberInGroup, 3, 0);
  m_layoutObstacle->addWidget(m_labelValueObstacleNumberInGroup, 3, 1);
  m_layoutObstacle->addWidget(m_sliderObstacleNumberInGroup, 4, 0, 1, 2);
  m_layoutObstacle->addWidget(m_labelObstacleNumberOfGroups, 5, 0);
  m_layoutObstacle->addWidget(m_labelValueObstacleNumberOfGroups, 5, 1);
  m_layoutObstacle->addWidget(m_sliderObstacleNumberOfGroups, 6, 0, 1, 2);

  // Нижний виджет
  m_bottomWidget = new QWidget(m_centralWidget);
  m_bottomLayout = new QHBoxLayout(m_bottomWidget);
  m_buttonStart = new QPushButton("Начать");

  //buttonStart->setIcon(QIcon("alien.png"));
  m_bottomLayout->addWidget(m_buttonStart);

  // Размещение в главной таблице
  m_layoutMain->addWidget(m_labelMode, 0, 0, 1, 2);
  m_layoutMain->addWidget(m_topWidget, 1, 0, 1, 2);
  m_layoutMain->addWidget(m_centralWidgetGun, 2, 0);
  m_layoutMain->addWidget(m_centralWidgetAlien, 2, 1);
  m_layoutMain->addWidget(m_centralWidgetBullet, 3, 0);
  m_layoutMain->addWidget(m_centralWidgetObstacle, 3, 1);

  m_layoutMain->addWidget(m_bottomWidget, 4, 0, 1, 2);

  // Настройка режимов
  connect(m_radioButtonNoob, SIGNAL(clicked(bool)), this, SLOT(radioButtonNoobClicked()));
  connect(m_radioButtonNormal, SIGNAL(clicked(bool)), this, SLOT(radioButtonNormalClicked()));
  connect(m_radioButtonPro, SIGNAL(clicked(bool)), this, SLOT(radioButtonProClicked()));

  connect(m_sliderGunHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderGunFiringRate, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderGunSpeed, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderGunNumberOfLives, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_sliderAlienHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienFiringRate, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienSpeed, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienNumberInLevel, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienNumberOfLevels, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_sliderBulletHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderBulletSpeed, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderBulletDamage, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_sliderObstacleHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderObstacleNumberInGroup, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderObstacleNumberOfGroups, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_buttonStart, SIGNAL(clicked(bool)), this, SLOT(WriteJson()));

}
void MainWindow::sliderMovedCustomChecked()
{
  m_radioButtonCustom->setChecked(true);
}

void MainWindow::radioButtonNoobClicked()
{
  m_sliderGunHP->setValue(GUN_HP_MAX);
  m_sliderGunFiringRate->setValue(GUN_FIRING_RATE_MAX);
  m_sliderGunSpeed->setValue(GUN_SPEED_MAX);
  m_sliderGunNumberOfLives->setValue(GUN_NUMBER_OF_LIVES_MAX);

  m_sliderAlienHP->setValue(ALIEN_HP_MIN);
  m_sliderAlienFiringRate->setValue(ALIEN_FIRING_RATE_MIN);
  m_sliderAlienSpeed->setValue(ALIEN_SPEED_MIN);
  m_sliderAlienNumberInLevel->setValue(ALIEN_NUMBER_IN_LEVEL_MIN);
  m_sliderAlienNumberOfLevels->setValue(ALIEN_NUMBER_OF_LEVELS_MIN);

  m_sliderBulletHP->setValue(BULLET_HP_MIN);
  m_sliderBulletSpeed->setValue(BULLET_SPEED_MIN);
  m_sliderBulletDamage->setValue(BULLET_DAMAGE_MIN);

  m_sliderObstacleHP->setValue(OBSTACLE_HP_MAX);
  m_sliderObstacleNumberInGroup->setValue(OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_sliderObstacleNumberOfGroups->setValue(OBSTACLE_NUMBER_OF_GROUPS_MAX);
}

// TODO: Взять настройки из оригнальной игры
void MainWindow::radioButtonNormalClicked()
{
  m_sliderGunHP->setValue(GUN_HP_MIN);
  m_sliderGunFiringRate->setValue(GUN_FIRING_RATE_MIN);
  m_sliderGunSpeed->setValue(GUN_SPEED_MIN);
  m_sliderGunNumberOfLives->setValue(GUN_NUMBER_OF_LIVES_MIN);

  m_sliderAlienHP->setValue(ALIEN_HP_MIN);
  m_sliderAlienFiringRate->setValue(ALIEN_FIRING_RATE_MIN);
  m_sliderAlienSpeed->setValue(ALIEN_SPEED_MIN);
  m_sliderAlienNumberInLevel->setValue(ALIEN_NUMBER_IN_LEVEL_MIN);
  m_sliderAlienNumberOfLevels->setValue(ALIEN_NUMBER_OF_LEVELS_MIN);

  m_sliderBulletHP->setValue(BULLET_HP_MIN);
  m_sliderBulletSpeed->setValue(BULLET_SPEED_MIN);
  m_sliderBulletDamage->setValue(BULLET_DAMAGE_MIN);

  m_sliderObstacleHP->setValue(OBSTACLE_HP_MAX);
  m_sliderObstacleNumberInGroup->setValue(OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_sliderObstacleNumberOfGroups->setValue(OBSTACLE_NUMBER_OF_GROUPS_MAX);
}

void MainWindow::radioButtonProClicked()
{
  m_sliderGunHP->setValue(GUN_HP_MIN);
  m_sliderGunFiringRate->setValue(GUN_FIRING_RATE_MIN);
  m_sliderGunSpeed->setValue(GUN_SPEED_MIN);
  m_sliderGunNumberOfLives->setValue(GUN_NUMBER_OF_LIVES_MIN);

  m_sliderAlienHP->setValue(ALIEN_HP_MAX);
  m_sliderAlienFiringRate->setValue(ALIEN_FIRING_RATE_MAX);
  m_sliderAlienSpeed->setValue(ALIEN_SPEED_MAX);
  m_sliderAlienNumberInLevel->setValue(ALIEN_NUMBER_IN_LEVEL_MAX);
  m_sliderAlienNumberOfLevels->setValue(ALIEN_NUMBER_OF_LEVELS_MAX);

  m_sliderBulletHP->setValue(BULLET_HP_MAX);
  m_sliderBulletSpeed->setValue(BULLET_SPEED_MAX);
  m_sliderBulletDamage->setValue(BULLET_DAMAGE_MAX);

  m_sliderObstacleHP->setValue(OBSTACLE_HP_MAX);
  m_sliderObstacleNumberInGroup->setValue(OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_sliderObstacleNumberOfGroups->setValue(OBSTACLE_NUMBER_OF_GROUPS_MAX);
}

void MainWindow::WriteJson()
{
  Json::Value settings;
  auto & root = settings["settings"];
  root["aliensCount"] = 100;
  //
  root["GunHP"] = m_sliderGunHP->value();
  root["GunFiringRate"] = m_sliderGunFiringRate->value();
  root["GunSpeed"] = m_sliderGunSpeed->value();
  root["GunNumberOfLives"] = m_sliderGunNumberOfLives->value();

  root["AlienHP"] = m_sliderAlienHP->value();
  root["AlienFiringRate"] = m_sliderAlienFiringRate->value();
  root["AlienSpeed"] = m_sliderAlienSpeed->value();
  root["AlienNumberInLevel"] = m_sliderAlienNumberInLevel->value();
  root["AlienNumberOfLevels"] = m_sliderAlienNumberOfLevels->value();

  root["BulletHP"] = m_sliderBulletHP->value();
  root["BulletSpeed"] = m_sliderBulletSpeed->value();
  root["BulletDamage"] = m_sliderBulletDamage->value();

  root["BulletHP"] = m_sliderBulletHP->value();
  root["BulletSpeed"] = m_sliderBulletSpeed->value();
  root["BulletDamage"] = m_sliderBulletDamage->value();

  root["ObstacleHP"] = m_sliderObstacleHP->value();
  root["ObstacleNumberInGroup"] = m_sliderObstacleNumberInGroup->value();
  root["ObstacleNumberOfGroups"] = m_sliderObstacleNumberOfGroups->value();
  //
  root["bulletsCount"] = 200;
  root["entities"]["gun"]["health"] = 50;
  root["entities"]["alien"]["health"] = 20;
  root["entities"]["obstacle"]["health"] = 15;
  std::ofstream settingsFile;
  settingsFile.open("settings.json");
  if (settingsFile.is_open())
  {
    Json::StyledWriter styledWriter;
    settingsFile << styledWriter.write(settings);
    settingsFile.close();
  }
}

void MainWindow::ReadJson()
{
  Json::Value settings;
  std::ifstream file("settings.json");
  if (file.is_open())
  {
    file >> settings;
    file.close();
  }
  std::cout << settings["settings"]["aliensCount"].asInt() << std::endl;
  std::cout << settings["settings"]["GunHP"].asInt() << std::endl;
  std::cout << settings["settings"]["GunFiringRate"].asInt() << std::endl;
  std::cout << settings["settings"]["GunSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["GunNumberOfLives"].asInt() << std::endl;

  std::cout << settings["settings"]["AlienHP"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienFiringRate"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienNumberInLevel"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienNumberOfLevels"].asInt() << std::endl;

  std::cout << settings["settings"]["BulletHP"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletDamage"].asInt() << std::endl;

  std::cout << settings["settings"]["BulletHP"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletDamage"].asInt() << std::endl;

  std::cout << settings["settings"]["ObstacleHP"].asInt() << std::endl;
  std::cout << settings["settings"]["ObstacleNumberInGroup"].asInt() << std::endl;

  std::cout << settings["settings"]["bulletsCount"].asInt() << std::endl;
  std::cout << settings["settings"]["entities"]["gun"]["health"].asInt() << std::endl;
  std::cout << settings["settings"]["entities"]["alien"]["health"].asInt() << std::endl;
  std::cout << settings["settings"]["entities"]["obstacle"]["health"].asInt() << std::endl;
}

MainWindow::~MainWindow()
{

}
