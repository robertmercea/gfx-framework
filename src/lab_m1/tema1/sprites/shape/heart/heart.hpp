#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "core/gpu/mesh.h"
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
                           const glm::mat3 &modelMatrix) override;
private:
  static constexpr float DEFAULT_HEART_RADIUS = 0.2f;
  std::shared_ptr<Mesh> heartMesh;
};

} // namespace sprites
} // namespace tema1
