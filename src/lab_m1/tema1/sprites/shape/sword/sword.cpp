#include "tema1/sprites/shape/sword/sword.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"
#include <iostream>

namespace tema1 {
namespace sprites {

Sword::Sword(float scale) : Sprite(scale * 0.93f, scale * 1.00f) {
  swordMesh = std::shared_ptr<Mesh>(
      ui::shape::createSword("sword", scale, ui::colors::GRAY));
}

Sword::Sword() : Sword(DEFAULT_SWORD_SCALE) {}

void Sword::getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                                const glm::mat3 &modelMatrix) {
  if (swordMesh) {
    SpriteProperties props{};
    props.modelMatrix = modelMatrix;
    props.mesh = swordMesh.get();
    spriteProps.push_back(props);
  } else {
    std::cerr << "Missing sword mesh\n";
  }
}

} // namespace sprites
} // namespace tema1
