#include "player.hpp"
#include "tema1/entities/player/player.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/transform/transform.hpp"
#include <algorithm>

namespace tema1 {
namespace ui {

Player::Player() {
  manaSprite = sprites::SpriteManager::getManager()->getSprite(globals::SpriteType::MANA);
}

void Player::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps, int mana) {
  if (!manaSprite || mana <= 0) return;

  float currentScaleX = std::max(1.0f, std::abs(getScale().x));

  float statWidth = manaSprite->width();
  float statHeight = manaSprite->height();
  float spacingMultiplier = 1.25f;
  float stepX = statWidth * spacingMultiplier;
  float stepY = -statHeight * spacingMultiplier;
  
  float availableWidth = 400.0f / currentScaleX;

  int maxPerRow = std::max(1, static_cast<int>(availableWidth / stepX));

  float totalWidth = std::min(availableWidth, mana * stepX);
  float startX = -totalWidth / 2.0f + (statWidth / 2.0f);
  float startY = 0.0f;

  glm::mat3 baseMatrix = getModelMatrix();

  for (int i = 0; i < mana; ++i) {
    int column = i % maxPerRow;
    int row = i / maxPerRow;

    float offsetX = startX + (static_cast<float>(column) * stepX);
    float offsetY = startY + (static_cast<float>(row) * stepY);

    glm::mat3 statMatrix = baseMatrix * ui::transform::translate(offsetX, offsetY);
    manaSprite->getSpriteProperties(spriteProps, statMatrix, ui::colors::BLUE);
  }
}

} // namespace ui
} // namespace tema1
