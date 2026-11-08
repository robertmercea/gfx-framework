#include "timer.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/manager/manager.hpp"
#include "tema1/ui/transform/transform.hpp"

namespace tema1 {
namespace ui {

Timer::Timer(float time) {
  this->totalTime = this->time  = time;

  const auto spriteMgr = sprites::SpriteManager::getManager();
  outerCircle = spriteMgr->getSprite(globals::SpriteType::SQUARE);
  innerCircle = spriteMgr->getSprite(globals::SpriteType::SQUARE);
}

Timer::Timer() {
  Timer(0.0f);
}

void Timer::reset() {
  time = totalTime;
}

void Timer::passTime(float dt) {
  time -= dt;
}

bool Timer::isTimeout() {
  return time <= 0;
}

void Timer::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  const auto baseMatrix = getModelMatrix();
  outerCircle->getSpriteProperties(spriteProps, baseMatrix, OUTER_CIRCLE_COLOR);

  const float innerDimension = time / totalTime;
  const auto innerMatrix = baseMatrix * transform::scale(innerDimension, innerDimension);
  innerCircle->getSpriteProperties(spriteProps, innerMatrix, INNER_CIRCLE_COLOR);
}

}
}
