#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

class Button : public Transformable {
public:
  Button();
  void setSize(float width, float height);
  void setColor(const glm::vec3 &color);
  bool contains(float x, float y) const;
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);

private:
  std::shared_ptr<sprites::Sprite> squareSprite;
  glm::vec3 color;
};

} // namespace ui
} // namespace tema1
