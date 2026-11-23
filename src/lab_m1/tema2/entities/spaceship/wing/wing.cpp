#include "wing.hpp"
#include "tema2/properties/renderable/renderable.hpp"
#include "tema2/properties/world_object/world_object.hpp"

namespace tema2 {
namespace entities {
namespace spaceship {

Wing::Wing(const std::string &meshName, const std::string &shaderName,
           const glm::vec3 &color, float hitboxRadius, float length,
           float height)
    : WorldObject(hitboxRadius, true), Renderable(meshName, shaderName, color) {

  setScale(glm::vec3(height, length, length));
}

void Wing::render(const RenderFunction &renderFunc, const RenderContext &ctx) const {
  renderFunc(_meshName, _shaderName, ctx.parentMatrix * getModelMatrix());
}

} // namespace spaceship
} // namespace entities
} // namespace tema2
