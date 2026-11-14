#include "arrow.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/geometric.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/sprites/arrow/arrow.hpp"

namespace tema1 {
namespace ui {

Arrow::Arrow() {
  const auto spriteMgr = sprites::SpriteManager::getManager();
  arrowSprite = spriteMgr->getSprite(globals::SpriteType::ARROW);
  color = ui::colors::RED;
}

void Arrow::setStartEnd(const glm::vec2 &start, const glm::vec2 &end) {
  glm::vec2 diff = end - start;
  float distance = glm::length(diff);

  if (distance < 1.0f) {
    return;
  }

  float headHeight = sqrt(6.75f) / 3.0f * sprites::Arrow::HEAD_WIDTH;
  float totalHeight = sprites::Arrow::BODY_HEIGHT + headHeight;
  float scaleFactor = distance / totalHeight;
  setScale(glm::vec2(scaleFactor / 2., scaleFactor));

  float angle = atan2(diff.y, diff.x) - (glm::pi<float>() / 2.0f);
  setRotation(angle);

  glm::vec2 direction = glm::normalize(diff);
  float baseOffset = (sprites::Arrow::BODY_HEIGHT / 2.0f) * scaleFactor;
  setPosition(start + (direction * baseOffset));
}

void Arrow::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  arrowSprite->getSpriteProperties(spriteProps, getModelMatrix(), color);
}

} // namespace ui
} // namespace tema1
