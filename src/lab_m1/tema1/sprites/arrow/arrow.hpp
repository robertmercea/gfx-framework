#pragma once

#include "core/gpu/mesh.h"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include <memory>

namespace tema1 {
namespace sprites {

class Arrow : public Sprite {
public:
  Arrow();
  void getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                           const glm::mat3 &modelMatrix,
                           const glm::vec3 &color) override;

private:
  static constexpr float BODY_WIDTH = 1.0f;
  static constexpr float BODY_HEIGHT = 10.0f;
  static constexpr float HEAD_WIDTH = 3. * BODY_WIDTH;
  std::shared_ptr<Mesh> arrowBody, arrowHead;
};

} // namespace sprites
} // namespace tema1
