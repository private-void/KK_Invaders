#pragma once

#include <gameentity.h>
#include <movable.h>
#include <point2d.hpp>
#include <box2d.hpp>
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Obstacle : public GameEntity
{
public:
  Obstacle() = default;

  void Damage(int amount);

private:
  unsigned int hp = 100;
  Point2D m_coordinate = {0.0f, 0.0f};
};

