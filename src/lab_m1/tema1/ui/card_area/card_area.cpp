#include "tema1/ui/card_area/card_area.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/ui/transform/transform.hpp"
#include "tema1/ui/globals/colors.hpp"
#include <algorithm>
#include <cmath>

namespace tema1 {
namespace ui {

CardArea::CardArea(float width, float height, const glm::vec3 &bgColor)
    : bgColor(bgColor), borderThickness(0.0f), borderSquare(nullptr) {

  const auto spriteMgr = tema1::sprites::SpriteManager::getManager();

  innerSquare = spriteMgr->getSprite(globals::SpriteType::SQUARE);
  this->_scale = glm::vec2(width, height);
}

CardArea::CardArea(float width, float height, const glm::vec3 &bgColor,
                   const glm::vec3 &borderColor, float borderThickness)
    : bgColor(bgColor), borderColor(borderColor), borderThickness(borderThickness) {

  const auto spriteMgr = tema1::sprites::SpriteManager::getManager();
  this->_scale = glm::vec2(width, height);

  innerSquare = spriteMgr->getSprite(globals::SpriteType::SQUARE);
  borderSquare = spriteMgr->getSprite(globals::SpriteType::SQUARE);
}

void CardArea::setSize(float width, float height) {
  this->_scale = glm::vec2(width, height);
}

void CardArea::setBorderThickness(float thickness) {
  this->borderThickness = thickness;
}

bool CardArea::contains(float x, float y) const {
  const float x0 = _position.x;
  const float y0 = _position.y;
  const float w = innerSquare->width() * std::abs(_scale.x);
  const float h = innerSquare->height() * std::abs(_scale.y);

  return (x >= x0 - w / 2.0f) && (x <= x0 + w / 2.0f) &&
         (y >= y0 - h / 2.0f) && (y <= y0 + h / 2.0f);
}

void CardArea::getSpriteProperties(
    std::vector<sprites::SpriteProperties> &spriteProps) {
  glm::mat3 baseMatrix = getModelMatrix();

  if (borderSquare && borderThickness > 0.0f) {
    borderSquare->getSpriteProperties(spriteProps, baseMatrix, borderColor);

    float totalW = std::abs(_scale.x);
    float totalH = std::abs(_scale.y);

    float innerRatioX = std::max(0.0f, (totalW - 2.0f * borderThickness) / totalW);
    float innerRatioY = std::max(0.0f, (totalH - 2.0f * borderThickness) / totalH);

    glm::mat3 innerMatrix = baseMatrix * ui::transform::scale(innerRatioX, innerRatioY);
    innerSquare->getSpriteProperties(spriteProps, innerMatrix, bgColor);
  } else if (innerSquare) {
    innerSquare->getSpriteProperties(spriteProps, baseMatrix, bgColor);
  }
}

} // namespace ui
} // namespace tema1
