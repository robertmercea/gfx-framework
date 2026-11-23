#pragma once

#include "tema2/properties/renderable/renderable.hpp"
#include "tema2/properties/world_object/world_object.hpp"
namespace tema2 {
namespace entities {
namespace spaceship {

using namespace properties;

class Wing : public WorldObject, private Renderable {
public:
  Wing(const std::string &meshName = "wing",
       const std::string &shaderName = "VertexColor",
       const glm::vec3 &color = glm::vec3(0.4f, 0.1f, 0.2f),
       float hitboxRadius = 1.0f, float length = 1.0f, float height = 1.0f);
  void render(const RenderFunction &renderFunc, const RenderContext &ctx) const;
};

} // namespace spaceship
} // namespace entities
} // namespace tema2
