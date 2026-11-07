#include "button.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/ui/globals/colors.hpp"
#include <cmath>

namespace tema1 {
namespace ui {

Button::Button() : color(ui::colors::ORANGE) {
  squareSprite = sprites::SpriteManager::getManager()->getSprite(globals::SpriteType::SQUARE);
}

void Button::setSize(float width, float height) {
  _scale = glm::vec2(width, height);
}

void Button::setColor(const glm::vec3 &c) {
  color = c;
}

bool Button::contains(float x, float y) const {
  if (!squareSprite) return false;
  float w = std::abs(_scale.x);
  float h = std::abs(_scale.y);
  return (x >= _position.x - w / 2.0f) && (x <= _position.x + w / 2.0f) &&
         (y >= _position.y - h / 2.0f) && (y <= _position.y + h / 2.0f);
}

void Button::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  if (squareSprite) {
    squareSprite->getSpriteProperties(spriteProps, getModelMatrix(), color);
  }
}

} // namespace ui
} // namespace tema1
