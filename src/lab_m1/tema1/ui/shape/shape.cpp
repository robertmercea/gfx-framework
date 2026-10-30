#include "tema1/ui/shape/shape.hpp"
#include <vector>

namespace tema1 {
namespace ui {
namespace shape {

const glm::vec3 VERTEX_NORMAL = glm::vec3(0, 0, 1);

Mesh *createNgon(const std::string name, int numVertices, float offset, float radius, const glm::vec3 color) {
  using namespace std;

  vector<VertexFormat> vertices;
  vector<unsigned int> indices;
  double deltaTheta = 2 * M_PI / numVertices;

  // origin
  vertices.push_back(
      VertexFormat(glm::vec3(0, 0, 0), color, VERTEX_NORMAL));

  for (int i = 0; i < numVertices; i++) {
    double theta = i * deltaTheta + offset;
    vertices.push_back(
        VertexFormat(glm::vec3(radius * cos(theta), radius * sin(theta), 0),
                     color, VERTEX_NORMAL));
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

Mesh *createHeart(const std::string name, float scale, const glm::vec3 color) {
  using namespace std;

  const int NUM_VERTICES = 1 << 6;
  vector<VertexFormat> vertices;
  vector<unsigned int> indices;
  double deltaTheta = 2 * M_PI / NUM_VERTICES;

  // origin
  vertices.push_back(
      VertexFormat(glm::vec3(0, 0, 0), color, VERTEX_NORMAL));

  for (int i = 0; i < NUM_VERTICES; i++) {
    double theta = i * deltaTheta;
    double x = 16 * pow(sin(theta), 3);
    double y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);

    vertices.push_back(
        VertexFormat(glm::vec3(scale * x, scale * y, 0),
                     color, VERTEX_NORMAL));
  }

  // actual circle
  for (int i = 1; i <= NUM_VERTICES; i++) {
    indices.push_back(0);
    indices.push_back(i);
    indices.push_back((i % NUM_VERTICES) + 1);
  }

  Mesh *mesh = new Mesh(name);
  mesh->InitFromData(vertices, indices);

  return mesh;
}

Mesh *createStar();
Mesh *createSpell();
Mesh *createArrow();

} // namespace shape
} // namespace ui
} // namespace tema1
