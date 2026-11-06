#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/sprites/shape/square/square.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

class CardArea : public Transformable {
public:
  CardArea() = default;
  CardArea(float width, float height, const glm::vec3 &bgColor);

  CardArea(float width, float height, const glm::vec3 &bgColor,
           const glm::vec3 &borderColor, float borderThickness);

  virtual ~CardArea() = default;

  void setSize(float width, float height);
  void setBorderThickness(float thickness);

  bool contains(float x, float y) const;

  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);

private:
  // a circumradius of 1 / sqrt(2) gives the Square a base width and height of 1.0f
  static constexpr float UNIT_SQUARE_LENGTH = 0.70710678f;

  glm::vec3 bgColor, borderColor;
  float borderThickness = 0.0f;
  std::shared_ptr<sprites::Sprite> innerSquare;
  std::shared_ptr<sprites::Sprite> borderSquare;
};

} // namespace ui
} // namespace tema1
