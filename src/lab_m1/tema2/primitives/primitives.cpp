#include "primitives.hpp"
#include "core/gpu/mesh.h"
#include <memory>

namespace tema2 {
namespace primitives {

static const auto VERTEX_COLOR = glm::vec3(0,0,0);

Mesh *createSphere(float radius) {}
Mesh *createCone(float radius, float height) {}
Mesh *createParallelepiped(float width, float height,
                                           float depth) {}

Mesh *createTriangularPrism(const std::string &name, float l, float h,
                            const glm::vec3 &color = glm::vec3(1.0f)) {
  const float halfH = h * 0.5f;
  const float halfL = l * 0.5f;
  const float sqrt3 = std::sqrt(3.0f);
  const float topY = (l * sqrt3) / 6.0f;
  const float botY = -(l * sqrt3) / 3.0f;

  // prism corners
  glm::vec3 R_topBack(halfH, topY, -halfL);
  glm::vec3 R_topFront(halfH, topY, halfL);
  glm::vec3 R_bot(halfH, botY, 0.0f);

  glm::vec3 L_topBack(-halfH, topY, -halfL);
  glm::vec3 L_topFront(-halfH, topY, halfL);
  glm::vec3 L_bot(-halfH, botY, 0.0f);

  // face normals
  glm::vec3 nRight(1.0f, 0.0f, 0.0f);
  glm::vec3 nLeft(-1.0f, 0.0f, 0.0f);
  glm::vec3 nTop(0.0f, 1.0f, 0.0f);
  glm::vec3 nFront(0.0f, -0.5f, sqrt3 * 0.5f);
  glm::vec3 nBack(0.0f, -0.5f, -sqrt3 * 0.5f);

  std::vector<VertexFormat> vertices = {
      // right triangle
      VertexFormat(R_topFront, color, nRight),
      VertexFormat(R_bot, color, nRight),
      VertexFormat(R_topBack, color, nRight),

      // left triangle
      VertexFormat(L_topBack, color, nLeft),
      VertexFormat(L_bot, color, nLeft),
      VertexFormat(L_topFront, color, nLeft),

      // top rectangle
      VertexFormat(L_topBack, color, nTop),
      VertexFormat(L_topFront, color, nTop),
      VertexFormat(R_topFront, color, nTop),
      VertexFormat(R_topBack, color, nTop),

      // front-slanted rectangle
      VertexFormat(L_topFront, color, nFront),
      VertexFormat(L_bot, color, nFront),
      VertexFormat(R_bot, color, nFront),
      VertexFormat(R_topFront, color, nFront),

      // back-slanted rectangle
      VertexFormat(R_topBack, color, nBack),
      VertexFormat(R_bot, color, nBack),
      VertexFormat(L_bot, color, nBack),
      VertexFormat(L_topBack, color, nBack),
  };

  std::vector<unsigned int> indices = {
      // righr triangle
      0, 1, 2,
      // left triangle
      3, 4, 5,
      // top rectangle
      6, 7, 8,
      6, 8, 9,
      // front-slanted rectangle
      10, 11, 12,
      10, 12, 13,
      // back-slanted rectangle
      14, 15, 16,
      14, 16, 17,
  };

  Mesh *prism = new Mesh(name);
  prism->InitFromData(vertices, indices);
  return prism;
}

} // namespace primitives
} // namespace tema2
