#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <vector>

namespace tema1 {
namespace entities {

class Renderable {
protected:
  virtual void getSpriteProperties(std::vector<tema1::sprites::SpriteProperties> &spriteProps) = 0;
  virtual void update(float deltaTime) = 0;
};

}
}
