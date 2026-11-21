#include "primitives.hpp"
#include "core/gpu/mesh.h"
#include "core/gpu/vertex_format.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include <memory>

namespace tema2 {
namespace primitives {

Mesh *createSphere(float radius) {}
Mesh *createCone(const std::string &name, float radius, float height,
                 const glm::vec3 &color) {

  const unsigned int NUM_CIRCLES = (int)height;
  const unsigned int CIRCLE_VERTICES = DEFAULT_CONE_RESOLUTION;
  const float TAN_THETA = radius / height;

  std::vector<VertexFormat> vertices;
  float ctheta = 0;
  const float DELTA_THETA = 2 * M_PI / CIRCLE_VERTICES;
  const float DELTA_Y = height / NUM_CIRCLES;

  // circles
  for (int i = 0; i < NUM_CIRCLES; i++) {
    ctheta = 0;
    for (int j = 0; j < CIRCLE_VERTICES; j++) {
      float vy = (i - 1) * DELTA_Y;
      float newRadius = radius - vy * TAN_THETA;
      float vx = newRadius * cos(ctheta);
      float vz = newRadius * sin(ctheta);
      auto normal = glm::normalize(glm::vec3(cos(ctheta), TAN_THETA, sin(ctheta)));

      vertices.push_back(VertexFormat(
          glm::vec3(vx, vy, vz),
          color, normal));
      ctheta += DELTA_THETA;
    }
  }

  // tip
  const unsigned int TIP_INDEX = static_cast<unsigned int>(vertices.size());
  vertices.push_back(
      VertexFormat(glm::vec3(0.0f, height, 0.0f), color, glm::vec3(0, 1, 0)));

  std::vector<unsigned int> indices;

  // connect circles
  for (unsigned int i = 0; i < NUM_CIRCLES - 1; i++) {
    unsigned int currRing = i * CIRCLE_VERTICES;
    unsigned int nextRing = (i + 1) * CIRCLE_VERTICES;

    for (unsigned int j = 0; j < CIRCLE_VERTICES; j++) {
      unsigned int nextJ = (j + 1) % CIRCLE_VERTICES;

      indices.push_back(currRing + j);
      indices.push_back(nextRing + j);
      indices.push_back(currRing + nextJ);

      indices.push_back(currRing + nextJ);
      indices.push_back(nextRing + j);
      indices.push_back(nextRing + nextJ);
    }
  }

  // connect last (top) circle to tip of cone
  const unsigned int LAST_RING = (NUM_CIRCLES - 1) * CIRCLE_VERTICES;
  for (unsigned int j = 0; j < CIRCLE_VERTICES; j++) {
    unsigned int nextJ = (j + 1) % CIRCLE_VERTICES;

    indices.push_back(LAST_RING + j);
    indices.push_back(TIP_INDEX);
    indices.push_back(LAST_RING + nextJ);
  }

  Mesh *mesh = new Mesh(name);
  mesh->InitFromData(vertices, indices);

  return mesh;
}

Mesh *createParallelepiped(const std::string &name, float width, float height,
                           float depth, const glm::vec3 &color) {
  const float halfW = width * 0.5f;
  const float halfH = height * 0.5f;
  const float halfD = depth * 0.5f;

  // corners
  glm::vec3 p000(-halfW, -halfH, -halfD);
  glm::vec3 p001(-halfW, -halfH, halfD);
  glm::vec3 p010(-halfW, halfH, -halfD);
  glm::vec3 p011(-halfW, halfH, halfD);
  glm::vec3 p100(halfW, -halfH, -halfD);
  glm::vec3 p101(halfW, -halfH, halfD);
  glm::vec3 p110(halfW, halfH, -halfD);
  glm::vec3 p111(halfW, halfH, halfD);

  // normals
  glm::vec3 nFront(0.0f, 0.0f, 1.0f);
  glm::vec3 nBack(0.0f, 0.0f, -1.0f);
  glm::vec3 nRight(1.0f, 0.0f, 0.0f);
  glm::vec3 nLeft(-1.0f, 0.0f, 0.0f);
  glm::vec3 nTop(0.0f, 1.0f, 0.0f);
  glm::vec3 nBottom(0.0f, -1.0f, 0.0f);

  std::vector<VertexFormat> vertices = {
      // front face
      VertexFormat(p001, color, nFront),
      VertexFormat(p101, color, nFront),
      VertexFormat(p111, color, nFront),
      VertexFormat(p011, color, nFront),

      // back face
      VertexFormat(p100, color, nBack),
      VertexFormat(p000, color, nBack),
      VertexFormat(p010, color, nBack),
      VertexFormat(p110, color, nBack),

      // right face
      VertexFormat(p101, color, nRight),
      VertexFormat(p100, color, nRight),
      VertexFormat(p110, color, nRight),
      VertexFormat(p111, color, nRight),

      // left face
      VertexFormat(p000, color, nLeft),
      VertexFormat(p001, color, nLeft),
      VertexFormat(p011, color, nLeft),
      VertexFormat(p010, color, nLeft),

      // top face
      VertexFormat(p011, color, nTop),
      VertexFormat(p111, color, nTop),
      VertexFormat(p110, color, nTop),
      VertexFormat(p010, color, nTop),

      // bottom face
      VertexFormat(p000, color, nBottom),
      VertexFormat(p100, color, nBottom),
      VertexFormat(p101, color, nBottom),
      VertexFormat(p001, color, nBottom),
  };

  std::vector<unsigned int> indices = {
      0,  1,  2,  0,  2,  3,  // front
      4,  5,  6,  4,  6,  7,  // back
      8,  9,  10, 8,  10, 11, // right
      12, 13, 14, 12, 14, 15, // left
      16, 17, 18, 16, 18, 19, // top
      20, 21, 22, 20, 22, 23  // bottom
  };

  Mesh *mesh = new Mesh(name);
  mesh->InitFromData(vertices, indices);
  return mesh;
}

Mesh *createTriangularPrism(const std::string &name, float l, float h,
                            const glm::vec3 &color) {
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
      0,
      1,
      2,
      // left triangle
      3,
      4,
      5,
      // top rectangle
      6,
      7,
      8,
      6,
      8,
      9,
      // front-slanted rectangle
      10,
      11,
      12,
      10,
      12,
      13,
      // back-slanted rectangle
      14,
      15,
      16,
      14,
      16,
      17,
  };

  Mesh *prism = new Mesh(name);
  prism->InitFromData(vertices, indices);
  return prism;
}

} // namespace primitives
} // namespace tema2
