#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <memory>
namespace tema1 {
namespace ui {

class Timer : public Transformable {
public:
  Timer();
  Timer(float);
  void reset();
  void passTime(float);
  bool isTimeout();
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
private:
  glm::vec3 OUTER_CIRCLE_COLOR = ui::colors::DARK_GRAY;
  glm::vec3 INNER_CIRCLE_COLOR = ui::colors::GRAY;
  float time;
  float totalTime;

  std::shared_ptr<sprites::Sprite> outerCircle, innerCircle;
};

}
}
