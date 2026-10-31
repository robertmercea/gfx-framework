#pragma once

#include "core/gpu/mesh.h"
#include <vector>
namespace tema1 {
namespace sprites {

struct SpriteProperties {
  Mesh *mesh;
  glm::mat3 modelMatrix;
  int zLevel;
};

class Sprite {
public:
  virtual void getSpriteProperties(std::vector<SpriteProperties> &spriteProps, const glm::mat3 &modelMatrix) = 0;
};
} // namespace sprites
} // namespace tema1
