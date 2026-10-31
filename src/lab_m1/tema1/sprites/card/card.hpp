#pragma once

#include "core/gpu/mesh.h"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/card/card.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace tema1 {
namespace sprites {

class Card : public Sprite {
public:
  Card(tema1::ui::CardType cardType);
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps,
                           const glm::mat3 &modelMatrix);

private:
  std::shared_ptr<Mesh> borderMesh;
  std::shared_ptr<Mesh> innerMesh;
  std::shared_ptr<Mesh> symbolMesh;
};

} // namespace sprites
} // namespace tema1
