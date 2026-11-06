#include "tema1/sprites/shape/heart/heart.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"
#include <iostream>

namespace tema1 {
namespace sprites {

Heart::Heart(float radius) {
  heartMesh = std::shared_ptr<Mesh>(
      ui::shape::createHeart("heart", radius, ui::colors::RED));
  dimensions.x = radius * 1.00f;
  dimensions.y = radius * 0.9375f;
}

Heart::Heart() : Heart(DEFAULT_HEART_RADIUS) {}

void Heart::getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                                const glm::mat3 &modelMatrix, const glm::vec3 &color) {
  if (heartMesh) {
    spriteProps.push_back({heartMesh.get(), modelMatrix, 0, color});
  } else {
    std::cerr << "Missing heart mesh\n";
  }
}

} // namespace sprites
} // namespace tema1
