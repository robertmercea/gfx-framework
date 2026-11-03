#include "card.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/sprites/shape/heart/heart.hpp"
#include "tema1/ui/transform/transform.hpp"
#include <cmath>
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

using CardType = entities::CardType;

Card::Card(CardType type, int health, int manaCost, int attack,
           std::shared_ptr<sprites::Sprite> cardFront,
           std::shared_ptr<sprites::Sprite> cardBack)
    : frontRender(true), type(type), cardFront(cardFront), cardBack(cardBack) {
  this->totalHealth = health;
  this->defaultScale = glm::vec2(150.0f, 200.0f);
  this->_scale = defaultScale;

  createHearts(health);
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

    if (!healthSprites.empty()) {
      float statWidth = healthSprites[0]->width();
      float statHeight = healthSprites[0]->height();

      float spacingMultiplier = 1.25f;
      float stepX = statWidth * spacingMultiplier;
      float stepY = -statHeight * spacingMultiplier;

      float availableWidth = cardFront->width();

      float startX = -availableWidth / 2.0f;
      float startY = cardFront->height() / 2.0f;

      int maxPerRow = std::max(1, (int)(availableWidth / stepX));

      for (size_t i = 0; i < healthSprites.size(); ++i) {
        int column = i % maxPerRow;
        int row = i / maxPerRow;

        float offsetX = startX + (column * stepX);
        float offsetY = startY + (row * stepY);

        glm::mat3 statMatrix =
            baseMatrix * ui::transform::translate(offsetX, offsetY);
        healthSprites[i]->getSpriteProperties(spriteProps, statMatrix);
      }
    }
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

} // namespace ui
} // namespace tema1
