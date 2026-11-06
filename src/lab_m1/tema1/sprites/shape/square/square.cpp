#include "tema1/sprites/shape/square/square.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"
#include <iostream>

namespace tema1 {
namespace sprites {

Square::Square() : Sprite(1.0f, 1.0f) {
  squareMesh = std::shared_ptr<Mesh>(
      ui::shape::createSquare("square", UNIT_SQUARE_LENGTH, ui::colors::WHITE));
}

void Square::getSpriteProperties(
    std::vector<SpriteProperties> &spriteProps,
    const glm::mat3 &modelMatrix,
    const glm::vec3 &color) {
  if (squareMesh) {
    spriteProps.push_back({squareMesh.get(), modelMatrix, 0, color});
  } else {
    std::cerr << "Missing square mesh\n";
  }
}

} // namespace sprites
} // namespace tema1
