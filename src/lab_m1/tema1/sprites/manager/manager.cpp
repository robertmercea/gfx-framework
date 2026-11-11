#include "manager.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/sprites/card/card.hpp"
#include "tema1/sprites/shape/heart/heart.hpp"
#include "tema1/sprites/shape/mana/mana.hpp"
#include "tema1/sprites/shape/square/square.hpp"
#include "tema1/sprites/shape/sword/sword.hpp"
#include <memory>

namespace tema1 {
namespace sprites {

SpriteManager *SpriteManager::instance = nullptr;

SpriteManager *SpriteManager::getManager() {
  if (!instance) {
    instance = new SpriteManager();
    instance->init();
  }

  return instance;
}

std::shared_ptr<Sprite> SpriteManager::getSprite(globals::SpriteType key) {
  return sprites.at(key);
}

void SpriteManager::addSprite(globals::SpriteType spriteType,
                              std::shared_ptr<Sprite> sprite) {
  sprites[spriteType] = sprite;
}

void SpriteManager::init() {
  using SpriteType = globals::SpriteType;

  sprites[SpriteType::WIZARD] = std::make_shared<sprites::Card>(globals::CardType::WIZARD);
  sprites[SpriteType::KNIGHT] = std::make_shared<sprites::Card>(globals::CardType::KNIGHT);
  sprites[SpriteType::MAGE] = std::make_shared<sprites::Card>(globals::CardType::MAGE);
  sprites[SpriteType::DWARF] = std::make_shared<sprites::Card>(globals::CardType::DWARF);
  sprites[SpriteType::MINION] = std::make_shared<sprites::Card>(globals::CardType::MINION);
  sprites[SpriteType::LEEROY_JENKINS] = std::make_shared<sprites::Card>(globals::CardType::LEEROY_JENKINS);
  sprites[SpriteType::VOIDWALKER] = std::make_shared<sprites::Card>(globals::CardType::VOIDWALKER);
  sprites[SpriteType::BACK] = std::make_shared<sprites::Card>(globals::CardType::BACK);
  sprites[SpriteType::HERO] = std::make_shared<sprites::Card>(globals::CardType::HERO);

  sprites[SpriteType::HEART] = std::make_shared<sprites::Heart>();
  sprites[SpriteType::MANA] = std::make_shared<sprites::Mana>();
  sprites[SpriteType::SWORD] = std::make_shared<sprites::Sword>();
  sprites[SpriteType::SQUARE] = std::make_shared<sprites::Square>();
}

void SpriteManager::clear() {
  sprites.clear();
}

} // namespace sprites
} // namespace tema1
