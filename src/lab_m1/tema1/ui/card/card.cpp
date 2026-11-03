#include "card.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include <cmath>

namespace tema1 {
namespace ui {

using CardType = entities::CardType;

Card::Card(CardType type, std::shared_ptr<sprites::Sprite> cardFront,
           std::shared_ptr<sprites::Sprite> cardBack)
    : frontRender(true), type(type), cardFront(cardFront), cardBack(cardBack) {
  this->defaultScale = glm::vec2(150.0f, 200.0f);
  this->_scale = defaultScale;
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

  // i just wanna shake shake shake shake shake shake it
  // i shake it off
  // i shake it off
  if (shakeAmount > 0.f) {
    shakeAmount = std::max(0.f, shakeAmount - deltaTime);
    _rotation = sin(shakeAmount * 5.0f) * 0.1f;
  } else {
    _rotation = 0.f;
  }
}

void Card::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  if (frontRender) {
    cardFront->getSpriteProperties(spriteProps, getModelMatrix());
  } else {
    cardBack->getSpriteProperties(spriteProps, getModelMatrix());
  }
}

} // namespace ui
} // namespace tema1
