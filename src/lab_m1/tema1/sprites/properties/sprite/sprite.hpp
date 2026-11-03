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

  Sprite(float width, float height) {
    dimensions = {width, height};
  }

  Sprite() {
    dimensions = {0, 0};
  }

  float width() const;
  float height() const;
protected:
  glm::vec2 dimensions;
};
} // namespace sprites
} // namespace tema1
