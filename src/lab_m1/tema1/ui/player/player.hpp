#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace entities { class Player; }
namespace ui {

class Player : public Transformable {
public:
  Player();
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps, int mana);

private:
  std::shared_ptr<sprites::Sprite> manaSprite;
};

} // namespace ui
} // namespace tema1
