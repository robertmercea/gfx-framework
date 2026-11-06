#pragma once

#include "core/gpu/mesh.h"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace sprites {

class Square : public Sprite {
public:
  Square();
  virtual ~Square() = default;

  void getSpriteProperties(
      std::vector<SpriteProperties> &spriteProps,
      const glm::mat3 &modelMatrix,
      const glm::vec3 &color) override;

private:
  static constexpr float UNIT_SQUARE_LENGTH = 0.70710678f;
  std::shared_ptr<Mesh> squareMesh;
};

} // namespace sprites
} // namespace tema1
