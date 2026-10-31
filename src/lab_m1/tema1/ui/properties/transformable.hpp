#pragma once

#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/vector_float2.hpp"

namespace tema1 {
namespace ui {

class Transformable {
protected:
  glm::mat3 _modelMatrix;
  glm::vec2 _scale;
  glm::vec2 _position;
  float _rotation;

public:
  Transformable();

  const glm::vec2 &getPosition() const;
  const glm::vec2 &getScale() const;
  float getRotation() const;

  void setPosition(const glm::vec2 &position);
  void setScale(const glm::vec2 &scale);
  void setRotation(float radians);

  void scale(float amount);
  void scale(float scaleX, float scaleY);
  void scale(const glm::vec2 &scale);

  void rotate(float radians);

  void translate(float translateX, float translateY);
  void translate(const glm::vec2 &position);

  const glm::mat3 &getModelMatrix();
};

} // namespace ui
} // namespace tema1
