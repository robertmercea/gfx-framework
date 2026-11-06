#include "tema1/sprites/shape/mana/mana.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"
#include <cmath>
#include <iostream>

namespace tema1 {
namespace sprites {

Mana::Mana(float length)
    : Sprite(length * std::sqrt(2.0f), length * std::sqrt(2.0f)) {
  manaMesh = std::shared_ptr<Mesh>(
      ui::shape::createSquare("mana", length, ui::colors::BLUE));
}

Mana::Mana() : Mana(DEFAULT_MANA_LENGTH) {}

void Mana::getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                               const glm::mat3 &modelMatrix,
                               const glm::vec3 &color) {
  if (manaMesh) {
    spriteProps.push_back({manaMesh.get(), modelMatrix, 0, color});
  } else {
    std::cerr << "Missing mana mesh\n";
  }
}

} // namespace sprites
} // namespace tema1
