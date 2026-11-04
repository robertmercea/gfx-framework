#include "card.hpp"
#include "tema1/globals/cards/stats/stats.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/sprites/shape/heart/heart.hpp"
#include "tema1/sprites/shape/mana/mana.hpp"
#include "tema1/sprites/shape/sword/sword.hpp"
#include "tema1/ui/transform/transform.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

Card::Card(globals::CardType cardType, globals::SpriteType spriteType)
    : frontRender(true), type(cardType), cardFront(fetchSprite(spriteType)),
      cardBack(fetchSprite(globals::SpriteType::BACK)) {

  const auto &stats = globals::stats::CARD_PROPERTIES.at(cardType);
  this->totalHealth = stats.health;
  this->defaultScale = glm::vec2(150.0f, 200.0f);
  this->_scale = defaultScale;

  createHearts(stats.health);
  createManaCost(stats.manaCost);
  createAttack(stats.attack);
}

void Card::showFront(bool show) {
  if (show) {
    showFront();
  } else {
    showBack();
  }
}
void Card::showFront() { frontRender = true; }
void Card::showBack() { frontRender = false; }
void Card::flip() { frontRender = !frontRender; }
void Card::shake(float amount) { shakeAmount = amount; }
void Card::onMouseEnter() { scaleAmount = MOUSE_ENTER_SCALE_FACTOR; }
void Card::onMouseLeave() { scaleAmount = MOUSE_LEAVE_SCALE_FACTOR; }

void Card::update(float deltaTime) {
  if (std::abs(scaleAmount) > 0) {
    scaleAmount = std::max(0.f, scaleAmount - deltaTime);
    _scale.x = defaultScale.x * sin(scaleAmount * 5.0f) * 0.1f;
    _scale.y = defaultScale.y * sin(scaleAmount * 5.0f) * 0.1f;
  } else {
    _scale = defaultScale;
  }

  if (shakeAmount > 0.f) {
    shakeAmount = std::max(0.f, shakeAmount - deltaTime);
    _rotation = sin(shakeAmount * 5.0f) * 0.1f;
  } else {
    _rotation = 0.f;
  }
}

void Card::getSpriteProperties(
    std::vector<sprites::SpriteProperties> &spriteProps) {

  glm::mat3 baseMatrix = getModelMatrix();

  if (frontRender) {
    if (cardFront) {
      cardFront->getSpriteProperties(spriteProps, baseMatrix);
    }

    renderHearts(spriteProps, baseMatrix);
    renderAttack(spriteProps, baseMatrix);
    renderManaCost(spriteProps, baseMatrix);
  } else {
    if (cardBack) {
      cardBack->getSpriteProperties(spriteProps, baseMatrix);
    }
  }
}

void Card::createHearts(int amount) {
  healthSprites.clear();
  for (int i = 0; i < amount; i++) {
    healthSprites.push_back(std::make_shared<sprites::Heart>(HEART_RADIUS));
  }
}

void Card::createManaCost(int amount) {
  manaCostSprites.clear();
  for (int i = 0; i < amount; i++) {
    manaCostSprites.push_back(std::make_shared<sprites::Mana>(MANA_SIZE));
  }
}

void Card::createAttack(int amount) {
  attackSprites.clear();
  for (int i = 0; i < amount; i++) {
    attackSprites.push_back(std::make_shared<sprites::Sword>(SWORD_SIZE));
  }
}

void Card::renderHearts(std::vector<sprites::SpriteProperties> &spriteProps,
                        const glm::mat3 &baseMatrix) {
  if (healthSprites.empty()) {
    std::cerr << "Card health sprites are empty!\n";
    return;
  }

  float statWidth = healthSprites[0]->width();
  float statHeight = healthSprites[0]->height();

  float spacingMultiplier = 1.25f;
  float stepX = statWidth * spacingMultiplier;
  float stepY = -statHeight * spacingMultiplier;

  float startX = -cardFront->width() / 2.0f;
  float startY = cardFront->height() / 2.0f;

  int maxPerRow = std::max(1, (int)(cardFront->width() / stepX));

  for (size_t i = 0; i < healthSprites.size(); ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (column * stepX);
    float offsetY = startY + (row * stepY);

    glm::mat3 statMatrix = baseMatrix;
    statMatrix *= ui::transform::translate(offsetX, offsetY);

    healthSprites[i]->getSpriteProperties(spriteProps, statMatrix);
  }
}

// renders the mana cost horizontally, with negative wrap-around, from under
// the hearts
void Card::renderManaCost(std::vector<sprites::SpriteProperties> &spriteProps,
                          const glm::mat3 &baseMatrix) {
  if (manaCostSprites.empty()) {
    std::cerr << "Card mana sprites are empty!\n";
    return;
  }

  float spacingMultiplier = 1.25f;
  float startX = -cardFront->width() / 2.0f;
  float startY = cardFront->height() / 2.0f;

  // render after last hearts
  if (!healthSprites.empty()) {
    float heartWidth = healthSprites[0]->width();
    float heartHeight = healthSprites[0]->height();
    float heartStepX = heartWidth * spacingMultiplier;
    float heartStepY = -heartHeight * spacingMultiplier;

    int heartMaxPerRow = std::max(1, (int)(cardFront->width() / heartStepX));
    int heartRows = ((int)healthSprites.size() - 1) / heartMaxPerRow + 1;

    startY += heartRows * heartStepY;
  }

  float statWidth = manaCostSprites[0]->width();
  float statHeight = manaCostSprites[0]->height();

  float stepX = statWidth * spacingMultiplier;
  float stepY = -statHeight * spacingMultiplier;

  int maxPerRow = std::max(1, (int)(cardFront->width() / stepX));

  for (size_t i = 0; i < manaCostSprites.size(); ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (column * stepX);
    float offsetY = startY + (row * stepY);

    glm::mat3 statMatrix = baseMatrix;
    statMatrix *= ui::transform::translate(offsetX, offsetY);

    manaCostSprites[i]->getSpriteProperties(spriteProps, statMatrix);
  }
}

// renders swords horizontally, from the bottom-left corner, with positive
// wrap-around
void Card::renderAttack(std::vector<sprites::SpriteProperties> &spriteProps,
                        const glm::mat3 &baseMatrix) {
  if (attackSprites.empty()) {
    std::cerr << "Card attack sprites are empty!\n";
    return;
  }

  float statWidth = attackSprites[0]->width();
  float statHeight = attackSprites[0]->height();

  float spacingMultiplier = 1.25f;
  float stepX = statWidth * spacingMultiplier;
  float stepY = statHeight * spacingMultiplier;

  float startX = -cardFront->width() / 2.0f;
  float startY = -cardFront->height() / 2.0f;

  int maxPerRow = std::max(1, (int)(cardFront->width() / stepX));

  for (size_t i = 0; i < attackSprites.size(); ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (column * stepX);
    float offsetY = startY + (row * stepY);

    glm::mat3 statMatrix = baseMatrix;
    statMatrix *= ui::transform::translate(offsetX, offsetY);

    attackSprites[i]->getSpriteProperties(spriteProps, statMatrix);
  }
}

std::shared_ptr<sprites::Sprite> Card::fetchSprite(globals::SpriteType key) {
  return sprites::SpriteManager::getManager()->getSprite(key);
}

} // namespace ui
} // namespace tema1
