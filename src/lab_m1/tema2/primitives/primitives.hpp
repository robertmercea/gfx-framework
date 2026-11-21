#pragma once

#include "core/gpu/mesh.h"

namespace tema2 {
namespace primitives {

Mesh *createSphere(float radius);
Mesh *createCone(float radius, float height);
Mesh *createParallelepiped(float width, float height,
                                           float depth);
Mesh *createTriangularPrism(float length, float height);

} // namespace primitives
} // namespace tema2
