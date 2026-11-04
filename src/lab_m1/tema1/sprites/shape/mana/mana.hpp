#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "core/gpu/mesh.h"
#include <memory>
#include <vector>

namespace tema1 {
namespace sprites {

class Mana : public Sprite {
public:
  Mana();
  Mana(float length);
  virtual ~Mana() = default;

  void getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                           const glm::mat3 &modelMatrix) override;

private:
  static constexpr float DEFAULT_MANA_LENGTH = 0.15f;
  std::shared_ptr<Mesh> manaMesh;
};

} // namespace sprites
} // namespace tema1
