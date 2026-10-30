#include "tema1/ui/shape/shape.hpp"
#include <vector>

namespace tema1 {
namespace ui {
namespace shape {

Mesh *createNgon(const std::string name, int numVertices, float offset, float radius, const glm::vec3 color) {
  using namespace std;

  const glm::vec3 NGON_NORMAL = glm::vec3(0, 0, 1);
  vector<VertexFormat> vertices;
  vector<unsigned int> indices;
  double deltaTheta = 2 * M_PI / numVertices;

  // origin
  vertices.push_back(
      VertexFormat(glm::vec3(0, 0, 0), color, NGON_NORMAL));

  for (int i = 0; i < numVertices; i++) {
    double theta = i * deltaTheta + offset;
    vertices.push_back(
        VertexFormat(glm::vec3(radius * cos(theta), radius * sin(theta), 0),
                     color, NGON_NORMAL));
  }

  // actual circle
  for (int i = 1; i <= numVertices; i++) {
    indices.push_back(0);
    indices.push_back(i);
    indices.push_back((i % numVertices) + 1);
  }

  Mesh *mesh = new Mesh(name);
  mesh->InitFromData(vertices, indices);

  return mesh;
}

Mesh *createSquare(const std::string name, float length, const glm::vec3 color) {
  return createNgon(name, 4, M_PI / 4, length, color);
}

Mesh *createCircle(const std::string name, float radius, const glm::vec3 color) {
  return createNgon(name, 32, 0, radius, color);
}

Mesh *createTriangle(const std::string name, float length, const glm::vec3 color) {
  return createNgon(name, 3, M_PI / 2, length, color);
}

Mesh *createSword();
Mesh *createHeart();
Mesh *createStar();
Mesh *createSpell();
Mesh *createArrow();

} // namespace shape
} // namespace ui
} // namespace tema1
