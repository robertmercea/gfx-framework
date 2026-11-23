#include "renderable.hpp"

namespace tema2 {
namespace properties {

Renderable::Renderable(const std::string &meshName,
                       const std::string &shaderName, const glm::vec3 &color)
    : _meshName(meshName), _shaderName(shaderName), _color(color) {}

} // namespace properties
} // namespace tema2
