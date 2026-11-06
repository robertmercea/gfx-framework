#pragma once

#include "core/gpu/mesh.h"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace sprites {

class Heart : public Sprite {
public:
  Heart();
  Heart(float length);
  virtual ~Heart() = default;

  void getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                           const glm::mat3 &modelMatrix,
                           const glm::vec3 &color) override;

private:
  static constexpr float DEFAULT_HEART_RADIUS = 0.2f;
  std::shared_ptr<Mesh> heartMesh;
};

} // namespace sprites
} // namespace tema1
