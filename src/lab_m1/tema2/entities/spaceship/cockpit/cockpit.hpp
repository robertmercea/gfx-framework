#pragma once

#include "glm/ext/vector_float3.hpp"
#include "tema2/properties/world_object/world_object.hpp"
#include <string>

namespace tema2 {
namespace entities {

class Cockpit : public WorldObject {
private:
  std::string _meshName;
  std::string _shaderName;
  glm::vec3 _color;

public:
  Cockpit(const std::string &meshName = "cockpit_hemisphere",
          const std::string &shaderName = "VertexColor",
          const glm::vec3 &color = glm::vec3(0.2f, 0.7f, 0.95f),
          float radius = 1.0f);

  void render(const RenderFunction &renderFunc) const override;
};

} // namespace entities
} // namespace tema2
