#pragma once

#include "core/gpu/mesh.h"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace tema1 {
namespace sprites {

class CardBack : public Sprite {
public:
  CardBack();
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps,
                           const glm::mat3 &modelMatrix);

private:
  std::shared_ptr<Mesh> borderMesh;
  std::shared_ptr<Mesh> innerMesh;
  std::shared_ptr<Mesh> heartMesh;
};

} // namespace sprites
} // namespace tema1
