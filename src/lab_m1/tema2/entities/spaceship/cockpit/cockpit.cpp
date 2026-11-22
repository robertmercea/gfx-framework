#include "cockpit.hpp"

namespace tema2 {
namespace entities {

Cockpit::Cockpit(const std::string &meshName, const std::string &shaderName,
                 const glm::vec3 &color, float radius)
    : WorldObject(radius, true),
      _meshName(meshName),
      _shaderName(shaderName),
      _color(color) {}

void Cockpit::render(const RenderFunction &renderFunc) const {
  renderFunc(_meshName, _shaderName, getModelMatrix());
}

} // namespace entities
} // namespace tema2
