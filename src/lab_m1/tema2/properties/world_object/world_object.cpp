#include "world_object.hpp"
#include "tema2/utils/transform/transform.hpp"

namespace tema2 {
namespace properties {

WorldObject::WorldObject(float boundingRadius, bool collisionEnabled)
    : _modelMatrix(1.0f), _scale(1.0f, 1.0f, 1.0f), _position(0.0f, 0.0f, 0.0f),
      _rotation(0.0f, 0.0f, 0.0f), _dirty(true),
      _boundingRadius(boundingRadius), _collisionEnabled(collisionEnabled) {}

// --- Transform ---

const glm::vec3 &WorldObject::getPosition() const { return _position; }

const glm::vec3 &WorldObject::getScale() const { return _scale; }

const glm::vec3 &WorldObject::getRotation() const { return _rotation; }

void WorldObject::setPosition(const glm::vec3 &position) {
  _position = position;
  _dirty = true;
}

void WorldObject::setScale(const glm::vec3 &scale) {
  _scale = scale;
  _dirty = true;
}

void WorldObject::setRotation(const glm::vec3 &radians) {
  _rotation = radians;
  _dirty = true;
}

void WorldObject::scale(float amount) {
  _scale *= amount;
  _dirty = true;
}

void WorldObject::scale(float scaleX, float scaleY, float scaleZ) {
  _scale *= glm::vec3(scaleX, scaleY, scaleZ);
  _dirty = true;
}

void WorldObject::scale(const glm::vec3 &scale) {
  _scale *= scale;
  _dirty = true;
}

void WorldObject::rotate(float radX, float radY, float radZ) {
  _rotation += glm::vec3(radX, radY, radZ);
  _dirty = true;
}

void WorldObject::rotate(const glm::vec3 &radians) {
  _rotation += radians;
  _dirty = true;
}

void WorldObject::rotateX(float radians) {
  _rotation.x += radians;
  _dirty = true;
}

void WorldObject::rotateY(float radians) {
  _rotation.y += radians;
  _dirty = true;
}

void WorldObject::rotateZ(float radians) {
  _rotation.z += radians;
  _dirty = true;
}

void WorldObject::translate(float translateX, float translateY,
                            float translateZ) {
  _position += glm::vec3(translateX, translateY, translateZ);
  _dirty = true;
}

void WorldObject::translate(const glm::vec3 &offset) {
  _position += offset;
  _dirty = true;
}

const glm::mat4 &WorldObject::getModelMatrix() const {
  if (_dirty) {
    _modelMatrix = glm::mat4(1.0f);
    _modelMatrix *=
        utils::transform::translate(_position.x, _position.y, _position.z);
    _modelMatrix *= utils::transform::rotateOY(_rotation.y);
    _modelMatrix *= utils::transform::rotateOX(_rotation.x);
    _modelMatrix *= utils::transform::rotateOZ(_rotation.z);
    _modelMatrix *= utils::transform::scale(_scale.x, _scale.y, _scale.z);
    _dirty = false;
  }
  return _modelMatrix;
}

// --- Collision ---

const glm::vec3 &WorldObject::getCollisionCenter() const { return _position; }

float WorldObject::getBoundingRadius() const { return _boundingRadius; }

void WorldObject::setBoundingRadius(float r) { _boundingRadius = r; }

bool WorldObject::isCollisionEnabled() const { return _collisionEnabled; }

void WorldObject::setCollisionEnabled(bool enabled) {
  _collisionEnabled = enabled;
}

bool WorldObject::collidesWith(const WorldObject &other) const {
  if (!_collisionEnabled || !other._collisionEnabled) {
    return false;
  }

  const float radiusSum = _boundingRadius + other._boundingRadius;
  const glm::vec3 diff = getCollisionCenter() - other.getCollisionCenter();
  return glm::dot(diff, diff) <= (radiusSum * radiusSum);
}

// --- Hierarchy ---

const std::vector<WorldObject *> &WorldObject::getComponents() const {
  return _components;
}

void WorldObject::addComponent(WorldObject *component) {
  if (component) {
    _components.push_back(component);
  }
}

} // namespace properties
} // namespace tema2
