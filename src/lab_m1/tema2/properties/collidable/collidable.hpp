#pragma once

#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"

namespace tema2 {
namespace properties {

class Collidable {
protected:
  float _boundingRadius;
  bool _collisionEnabled = true;

public:
  explicit Collidable(float radius) : _boundingRadius(radius) {}
  virtual ~Collidable() = default;

  // gets the position for which to calculate collisions.
  // must be explicitly implemented by inheriting classes
  virtual glm::vec3 getCollisionCenter() const = 0;

  float getBoundingRadius() const { return _boundingRadius; }
  void setBoundingRadius(float r) { _boundingRadius = r; }

  bool isCollisionEnabled() const { return _collisionEnabled; }
  void setCollisionEnabled(bool enabled) { _collisionEnabled = enabled; }

  bool collidesWith(const Collidable &other) const {
    if (!_collisionEnabled || !other._collisionEnabled) {
      return false;
    }

    const float r1 = _boundingRadius;
    const float r2 = other._boundingRadius;
    const glm::vec3 &c1 = getCollisionCenter();
    const glm::vec3 &c2 = other.getCollisionCenter();

    return glm::distance(c1, c2) <= r1 + r2;
  }
};

} // namespace properties
} // namespace tema2
