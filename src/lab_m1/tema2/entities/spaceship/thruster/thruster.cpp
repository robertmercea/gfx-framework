#include "thruster.hpp"
#include "utils/math_utils.h"

namespace tema2 {
namespace entities {
namespace spaceship {

Thruster::Thruster(const std::string &meshName, const std::string &shaderName,
                   const glm::vec3 &color, float hitboxRadius, float radius,
                   float height)
    : WorldObject(hitboxRadius, true),
      Renderable(meshName, shaderName, color) {
  setScale(glm::vec3(radius, height, radius));
  // point cone tip (+Y) forward (-Z) so the circular base faces the rear (+Z)
  setRotation(glm::vec3(RADIANS(-90.0f), 0.0f, 0.0f));
}

void Thruster::render(const RenderFunction &renderFunc, const RenderContext &ctx) const {
  renderFunc(_meshName, _shaderName, ctx.parentMatrix * getModelMatrix());
}

} // namespace spaceship
} // namespace entities
} // namespace tema2
