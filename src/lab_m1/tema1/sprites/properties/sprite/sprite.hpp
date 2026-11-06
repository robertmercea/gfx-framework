#pragma once

#include "core/gpu/mesh.h"
#include <glm/glm.hpp>
#include <vector>

namespace tema1 {
namespace sprites {

struct SpriteProperties {
  Mesh *mesh;
  glm::mat3 modelMatrix;
  int zLevel = 0;
  glm::vec3 color;

  SpriteProperties(Mesh *m, const glm::mat3 &mat, int z, const glm::vec3 &col)
        : mesh(m), modelMatrix(mat), zLevel(z), color(col) {}
};

class Sprite {
public:
  Sprite(float width, float height) : dimensions{width, height} {}
  Sprite() : dimensions{0.0f, 0.0f} {}
  virtual ~Sprite() = default;

  virtual void getSpriteProperties(
      std::vector<SpriteProperties> &spriteProps,
      const glm::mat3 &modelMatrix,
      const glm::vec3 &color) = 0;

  float width() const;
  float height() const;

protected:
  glm::vec2 dimensions;
};

} // namespace sprites
} // namespace tema1
