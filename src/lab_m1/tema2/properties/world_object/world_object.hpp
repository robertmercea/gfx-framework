#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/gtc/quaternion.hpp"
#include <functional>
#include <string>
#include <vector>

namespace tema2 {
namespace properties {

using RenderFunction = std::function<void(
    const std::string &, const std::string &, const glm::mat4 &)>;

struct RenderContext {
  glm::mat4 parentMatrix = glm::mat4(1.0f);
};

class WorldObject {
protected:
  // Transform state
  mutable glm::mat4 _modelMatrix;
  glm::vec3 _scale;
  glm::vec3 _position;
  glm::quat _rotation;
  mutable bool _dirty;

  // Collision state
  float _boundingRadius;
  bool _collisionEnabled;

  // Hierarchical sub-components (e.g., ship parts, planet moons)
  std::vector<WorldObject *> _components;

public:
  explicit WorldObject(float boundingRadius = 1.0f,
                       bool collisionEnabled = true);
  virtual ~WorldObject() = default;

  // --- Transform ---
  const glm::vec3 getPosition() const;
  const glm::vec3 getScale() const;
  const glm::vec3 getRotation() const;

  void setPosition(const glm::vec3 &position);
  void setScale(const glm::vec3 &scale);
  void setRotation(const glm::vec3 &radians);

  void scale(float amount);
  void scale(float scaleX, float scaleY, float scaleZ);
  void scale(const glm::vec3 &scale);

  void rotateLocal(const glm::vec3&);
  void rotateGlobal(const glm::vec3&);

  void translate(float translateX, float translateY, float translateZ);
  void translate(const glm::vec3 &offset);

  glm::vec3 getForward() const;
  glm::vec3 getUp() const;
  glm::vec3 getRight() const;

  const glm::mat4 &getModelMatrix() const;

  // --- Collision ---
  virtual const glm::vec3 &getCollisionCenter() const;

  float getBoundingRadius() const;
  void setBoundingRadius(float r);

  bool isCollisionEnabled() const;
  void setCollisionEnabled(bool enabled);

  virtual bool collidesWith(const WorldObject &other) const;

  // --- Hierarchy ---
  const std::vector<WorldObject *> &getComponents() const;
  void addComponent(WorldObject *component);

  // --- Rendering ---
  virtual void render(const RenderFunction &renderFunc, const RenderContext &ctx) const = 0;
};

} // namespace properties
} // namespace tema2
