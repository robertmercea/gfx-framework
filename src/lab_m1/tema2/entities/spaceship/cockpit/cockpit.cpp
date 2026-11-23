#include "cockpit.hpp"
#include "glm/ext/vector_float3.hpp"
#include "tema2/properties/renderable/renderable.hpp"

namespace tema2 {
namespace entities {
namespace spaceship {

Cockpit::Cockpit(const std::string &meshName, const std::string &shaderName,
                 const glm::vec3 &color, float radius)
    : WorldObject(radius, true), Renderable(meshName, shaderName, color) {
  setScale(glm::vec3(radius));
}

void Cockpit::render(const RenderFunction &renderFunc, const RenderContext &ctx) const {
  renderFunc(_meshName, _shaderName, ctx.parentMatrix * getModelMatrix());
}

} // namespace entities
} // namespace tema2
}
