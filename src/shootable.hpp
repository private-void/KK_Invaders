#pragma once

#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Shootable : public Movable
{
public:
  virtual ~Shootable() = default;

  virtual void Shot();

private:
  unsigned int m_ammo = 0;
};

