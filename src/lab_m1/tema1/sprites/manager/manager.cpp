#include "manager.hpp"

namespace tema1 {
namespace sprites {

std::shared_ptr<SpriteManager> SpriteManager::instance = nullptr;

std::shared_ptr<SpriteManager> SpriteManager::getManager() {
  if (!instance) {
    instance = std::shared_ptr<SpriteManager>(new SpriteManager());
  }

  return instance;
}

std::shared_ptr<Sprite> SpriteManager::getSprite(const std::string &key) {
  return sprites.at(key);
}

void SpriteManager::addSprite(const std::string &key,
                              std::shared_ptr<Sprite> sprite) {
  sprites[key] = sprite;
}

} // namespace sprites
} // namespace tema1
