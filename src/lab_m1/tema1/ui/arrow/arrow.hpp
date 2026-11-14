#pragma once

#include "tema1/sprites/arrow/arrow.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include "glm/ext/vector_float2.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

class Arrow : public Transformable {
public:
  Arrow();
  void setStartEnd(const glm::vec2 &start, const glm::vec2 &end);
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);

private:
  std::shared_ptr<sprites::Sprite> arrowSprite;
  glm::vec3 color;
};

} // namespace ui
} // namespace tema1
