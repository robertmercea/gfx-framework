#pragma once

#include "tema2/properties/renderable/renderable.hpp"
#include "tema2/properties/world_object/world_object.hpp"
namespace tema2 {
namespace entities {
namespace spaceship {

using namespace properties;

class Body : public WorldObject, private Renderable {
public:
  Body(const std::string &meshName = "cockpit_hemisphere",
                const std::string &shaderName = "VertexColor",
                const glm::vec3 &color = glm::vec3(0.2f, 0.7f, 0.95f),
                float hitboxRadius = 3.0f, float width = 1.0f,
                float height = 0.5f, float depth = 0.25f);

  void render(const RenderFunction &renderFunc, const RenderContext &ctx) const override;

private:
  std::string meshName;
  std::string shaderName;
};

} // namespace spaceship
} // namespace entities
} // namespace tema2
