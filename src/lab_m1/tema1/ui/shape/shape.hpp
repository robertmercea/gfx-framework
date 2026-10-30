#pragma once

#include "core/gpu/mesh.h"

namespace tema1 {
namespace ui {
namespace shape {

Mesh *createNgon(const std::string name, int numVertices, float offset, float radius, const glm::vec3 color);
Mesh *createSquare(const std::string name, float length, const glm::vec3 color);
Mesh *createCircle(const std::string name, float radius, const glm::vec3 color);
Mesh *createTriangle(const std::string name, float length, const glm::vec3 color);

Mesh *createSword();
Mesh *createHeart(const std::string name, float radius, const glm::vec3 color);
Mesh *createStar();
Mesh *createSpell();
Mesh *createArrow();

} // namespace shape
} // namespace ui
} // namespace tema1
