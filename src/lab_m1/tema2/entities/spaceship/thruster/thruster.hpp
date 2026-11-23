#pragma once

#include "tema2/properties/renderable/renderable.hpp"
#include "tema2/properties/world_object/world_object.hpp"
#include <string>

namespace tema2 {
namespace entities {
namespace spaceship {

using namespace properties;

class Thruster : public WorldObject, private Renderable {
public:
  Thruster(const std::string &meshName = "thruster",
           const std::string &shaderName = "VertexColor",
           const glm::vec3 &color = glm::vec3(1.0f, 0.5f, 0.1f),
           float hitboxRadius = 1.0f, float radius = 1.0f, float height = 1.0f);

  void render(const RenderFunction &renderFunc, const RenderContext &ctx) const override;
};

} // namespace spaceship
} // namespace entities
} // namespace tema2
