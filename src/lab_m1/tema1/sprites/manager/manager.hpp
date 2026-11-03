#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace tema1 {
namespace sprites {

class SpriteManager {
public:
  static std::shared_ptr<SpriteManager> getManager();

  std::shared_ptr<Sprite> getSprite(const std::string &key);
  void addSprite(const std::string &key, std::shared_ptr<Sprite> sprite);

private:
  SpriteManager() = default;

  static std::shared_ptr<SpriteManager> instance;
  std::unordered_map<std::string, std::shared_ptr<Sprite>> sprites;
};

} // namespace sprites
} // namespace tema1
