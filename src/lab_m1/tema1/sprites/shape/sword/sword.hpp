#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "core/gpu/mesh.h"
#include <memory>
#include <vector>

namespace tema1 {
namespace sprites {

class Sword : public Sprite {
public:
  Sword();
  Sword(float scale);
  virtual ~Sword() = default;

  void getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                           const glm::mat3 &modelMatrix, const glm::vec3 &color) override;

private:
  static constexpr float DEFAULT_SWORD_SCALE = 0.2f;
  std::shared_ptr<Mesh> swordMesh;
};

} // namespace sprites
} // namespace tema1
