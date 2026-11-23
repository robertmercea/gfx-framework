#pragma once

#include "glm/ext/vector_float3.hpp"
#include <string>

namespace tema2 {
namespace properties {

class Renderable {
public:
  Renderable(const std::string&, const std::string&, const glm::vec3&);

protected:
  std::string _meshName;
  std::string _shaderName;
  glm::vec3 _color;
};

} // namespace properties
} // namespace tema2
