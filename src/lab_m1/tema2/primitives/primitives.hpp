#pragma once

#include "core/gpu/mesh.h"

namespace tema2 {
namespace primitives {

static const auto DEFAULT_VERTEX_COLOR = glm::vec3(0, 0, 0);

Mesh *createSphere(float radius);
Mesh *createCone(float radius, float height);
Mesh *createParallelepiped(const std::string &name, float width, float height,
                           float depth,
                           const glm::vec3 &color = glm::vec3(1.0f) = DEFAULT_VERTEX_COLOR);
Mesh *createTriangularPrism(const std::string &name, float l, float h,
                            const glm::vec3 &color = DEFAULT_VERTEX_COLOR);

} // namespace primitives
} // namespace tema2
