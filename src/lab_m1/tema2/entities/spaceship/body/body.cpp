#include "body.hpp"
#include "tema2/properties/renderable/renderable.hpp"
#include "tema2/properties/world_object/world_object.hpp"

namespace tema2 {
namespace entities {
namespace spaceship {

Body::Body(const std::string &meshName, const std::string &shaderName,
           const glm::vec3 &color, float hitboxRadius, float width,
           float height, float depth)
    : WorldObject(hitboxRadius, true), Renderable(meshName, shaderName, color) {

  setScale(glm::vec3(width, height, depth));
}

void Body::render(const RenderFunction &renderFunc, const RenderContext &ctx) const {
  renderFunc(_meshName, _shaderName, ctx.parentMatrix * getModelMatrix());
}

} // namespace spaceship
} // namespace entities
} // namespace tema2
