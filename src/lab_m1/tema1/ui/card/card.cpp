#include "card.hpp"
#include "tema1/globals/cards/stats/stats.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/transform/transform.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

Card::Card(globals::CardType cardType, globals::SpriteType spriteType)
    : frontRender(true), type(cardType) {

  const auto spriteMgr = sprites::SpriteManager::getManager();
  const auto &stats = globals::stats::CARD_PROPERTIES.at(cardType);
  this->totalHealth = stats.health;
  this->defaultScale = DEFAULT_SCALE;
  this->defaultPosition = {_position.x, _position.y};
  this->_scale = defaultScale;

  health = stats.health;
  attack = stats.attack;
  manaCost = stats.manaCost;

  cardFront = spriteMgr->getSprite(spriteType);
  cardBack = spriteMgr->getSprite(globals::SpriteType::BACK);
  heartSprite = spriteMgr->getSprite(globals::SpriteType::HEART);
  attackSprite = spriteMgr->getSprite(globals::SpriteType::SWORD);
  manaCostSprite = spriteMgr->getSprite(globals::SpriteType::MANA);
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

void Card::onMouseMove(float mouseX, float mouseY) {
  if (!contains(mouseX, mouseY)) {
    return;
  }

  if (isSelected) {
    setPosition({mouseX, mouseY});
  }
}

void Card::update(float deltaTime) {
  if (std::abs(scaleAmount) > 0) {
    _scale.x = defaultScale.x * scaleAmount;
    _scale.y = defaultScale.y * scaleAmount;
  } else {
    _scale = defaultScale;
  }

  if (shakeAmount > 0.f) {
    shakeAmount = std::max(0.f, shakeAmount - deltaTime);
    _rotation = sin(shakeAmount * 5.0f) * 0.1f;
  } else {
    _rotation = 0.f;
  }

  if (destroyAnimationOffset > 0) {
    destroyAnimationOffset -= deltaTime;
  } else {
    destroyAnimationOffset = 0;
  }
}

void Card::onHoverEnter() {
  scaleAmount = SELECTED_SCALING;
}

void Card::onHoverLeave() {
  scaleAmount = 0.0f;
}

void Card::unselect() {
  scaleAmount = 0.0f;
}

void Card::destroy() {
  destroyAnimationOffset = DESTROY_ANIMATION_DURATION;
}

void Card::prepareToAttack() {
  scaleAmount = SELECTED_SCALING + PREPARED_SCALING;
}

void Card::getSpriteProperties(
    std::vector<sprites::SpriteProperties> &spriteProps) {

  _position.x += sin(destroyAnimationOffset * 50.0f) * DESTROY_OFFSET;
  glm::mat3 baseMatrix = getModelMatrix();
  _position.x -= sin(destroyAnimationOffset * 50.0f) * DESTROY_OFFSET;

  if (frontRender) {
    if (cardFront)
      cardFront->getSpriteProperties(spriteProps, baseMatrix, borderColor);

    renderHearts(spriteProps, baseMatrix);
    renderManaCost(spriteProps, baseMatrix);
    renderAttack(spriteProps, baseMatrix);
  } else {
    if (cardBack)
      cardBack->getSpriteProperties(spriteProps, baseMatrix, borderColor);
  }
}

void Card::renderHearts(std::vector<sprites::SpriteProperties> &spriteProps,
                        const glm::mat3 &baseMatrix) {
  float statWidth = heartSprite->width();
  float statHeight = heartSprite->height();
  float spacingMultiplier = 1.25f;
  float stepX = statWidth * spacingMultiplier;
  float stepY = -statHeight * spacingMultiplier;

  float paddingX = (statWidth / 2.0f) + 0.10f;
  float paddingY = (statHeight / 2.0f) + 0.10f;

  float startX = -cardFront->width() / 2.0f + paddingX;
  float startY = cardFront->height() / 2.0f - paddingY;

  float availableWidth = cardFront->width() - (2.0f * paddingX);
  int maxPerRow = std::max(1, (int)(availableWidth / stepX));

  for (size_t i = 0; i < health; ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (column * stepX);
    float offsetY = startY + (row * stepY);

    glm::mat3 statMatrix =
        baseMatrix * ui::transform::translate(offsetX, offsetY);
    heartSprite->getSpriteProperties(spriteProps, statMatrix, ui::colors::RED);
  }
}

void Card::renderManaCost(std::vector<sprites::SpriteProperties> &spriteProps,
                          const glm::mat3 &baseMatrix) {
  float statWidth = manaCostSprite->width();
  float statHeight = manaCostSprite->height();
  float spacingMultiplier = 1.25f;
  float stepX = statWidth * spacingMultiplier;
  float stepY = -statHeight * spacingMultiplier;

  float paddingX = (statWidth / 2.0f) + 0.10f;
  float paddingY = (statHeight / 2.0f) + 0.10f;

  float startX = -cardFront->width() / 2.0f + paddingX;
  float startY = cardFront->height() / 2.0f - paddingY;

  if (health > 0) {
    float heartWidth = heartSprite->width();
    float heartHeight = heartSprite->height();
    float heartStepX = heartWidth * spacingMultiplier;
    float heartStepY = -heartHeight * spacingMultiplier;

    float hPaddingX = (heartWidth / 2.0f) + 0.05f;
    float availableWidth = cardFront->width() - (2.0f * hPaddingX);

    int heartMaxPerRow = std::max(1, (int)(availableWidth / heartStepX));
    int heartRows = (health - 1) / heartMaxPerRow + 1;

    startY += heartRows * heartStepY;
  }

  float availableWidth = cardFront->width() - (2.0f * paddingX);
  int maxPerRow = std::max(1, (int)(availableWidth / stepX));

  for (size_t i = 0; i < manaCost; ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (column * stepX);
    float offsetY = startY + (row * stepY);

    glm::mat3 statMatrix =
        baseMatrix * ui::transform::translate(offsetX, offsetY);
    manaCostSprite->getSpriteProperties(spriteProps, statMatrix,
                                        ui::colors::BLUE);
  }
}

void Card::renderAttack(std::vector<sprites::SpriteProperties> &spriteProps,
                        const glm::mat3 &baseMatrix) {
  if (attack == 0)
    return;

  float statWidth = attackSprite->width();
  float statHeight = attackSprite->height();
  float spacingMultiplier = 1.25f;
  float stepX = statWidth * spacingMultiplier;
  float stepY = statHeight * spacingMultiplier; // Positive moves upwards

  float paddingX = (statWidth / 2.0f) + 0.10f;
  float paddingY = (statHeight / 2.0f) + 0.10f;

  float startX = -cardFront->width() / 2.0f + paddingX;
  float startY = -cardFront->height() / 2.0f + paddingY;

  float availableWidth = cardFront->width() - (2.0f * paddingX);
  int maxPerRow = std::max(1, (int)(availableWidth / stepX));

  for (size_t i = 0; i < attack; ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (column * stepX);
    float offsetY = startY + (row * stepY);

    glm::mat3 statMatrix =
        baseMatrix * ui::transform::translate(offsetX, offsetY);
    attackSprite->getSpriteProperties(spriteProps, statMatrix,
                                      ui::colors::GRAY);
  }
}

void Card::onMouseBtnPress(float mouseX, float mouseY) {
  if (!contains(mouseX, mouseY))
    return;

  isSelected = true;
}

void Card::onMouseBtnRelease(float mouseX, float mouseY) {
  if (!contains(mouseX, mouseY))
    return;

  isSelected = false;
  setPosition(defaultPosition);
}

void Card::setInitialPosition(const glm::vec2 &position) {
  _position.x = defaultPosition.x = position.x;
  _position.y = defaultPosition.y = position.y;
}

bool Card::contains(float x, float y) {
  const float x0 = _position.x;
  const float y0 = _position.y;
  const float w = cardFront->width() * std::abs(_scale.x);
  const float h = cardFront->height() * std::abs(_scale.y);

  return x0 - w / 2. <= x && x <= x0 + w / 2. && y0 - h / 2. <= y &&
         y <= y0 + h / 2.;
}

} // namespace ui
} // namespace tema1
