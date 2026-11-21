#pragma once

#include "glm/ext/matrix_float4x4.hpp"

namespace tema2 {
namespace properties {

class Transformable {
protected:
  glm::mat4 _modelMatrix;
  glm::vec3 _scale;
  glm::vec3 _position;
  glm::vec3 _rotation; // pitch (X), yaw (Y), roll (Z) in radians
  bool _dirty;

public:
  Transformable();
  virtual ~Transformable() = default;

  const glm::vec3 &getPosition() const;
  const glm::vec3 &getScale() const;
  const glm::vec3 &getRotation() const;

  virtual void setPosition(const glm::vec3 &position);
  virtual void setScale(const glm::vec3 &scale);
  virtual void setRotation(const glm::vec3 &radians);

  void scale(float amount);
  void scale(float scaleX, float scaleY, float scaleZ);
  void scale(const glm::vec3 &scale);

  void rotate(float radX, float radY, float radZ);
  void rotate(const glm::vec3 &radians);
  void rotateX(float radians);
  void rotateY(float radians);
  void rotateZ(float radians);

  void translate(float translateX, float translateY, float translateZ);
  void translate(const glm::vec3 &offset);

  virtual const glm::mat4 &getModelMatrix();
};

} // namespace properties
} // namespace tema2
