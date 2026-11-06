#pragma once

#include "core/gpu/mesh.h"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace tema1 {
namespace sprites {

class Card : public Sprite {
public:
  Card(globals::CardType cardType);

  void getSpriteProperties(
      std::vector<sprites::SpriteProperties> &spriteProps,
      const glm::mat3 &modelMatrix,
      const glm::vec3 &color) override;

private:
  std::shared_ptr<Mesh> borderMesh;
  std::shared_ptr<Mesh> innerMesh;
  std::shared_ptr<Mesh> symbolMesh;

  glm::vec3 innerColor;
  glm::vec3 symbolColor;
};

} // namespace sprites
} // namespace tema1
