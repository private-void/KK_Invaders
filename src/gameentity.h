#pragma once

#include <point2d.hpp>
#include <box2d.hpp>
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class GameEntity
{
public:
  virtual ~GameEntity() = 0;
  virtual toString() = 0;

private:
  Point2D m_coordinate = {0.0f, 0.0f};
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
};