#pragma once

#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <memory>
#include <unordered_map>

namespace tema1 {
namespace sprites {

class SpriteManager {
public:
  static SpriteManager *getManager();

  std::shared_ptr<Sprite> getSprite(globals::SpriteType key);
  void addSprite(globals::SpriteType spriteType, std::shared_ptr<Sprite> sprite);
  void clear();

private:
  SpriteManager() = default;

  static SpriteManager *instance;
  std::unordered_map<globals::SpriteType, std::shared_ptr<Sprite>> sprites;
  void init();
};

} // namespace sprites
} // namespace tema1
