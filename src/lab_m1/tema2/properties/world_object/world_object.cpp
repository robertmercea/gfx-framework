#include "world_object.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "tema2/utils/transform/transform.hpp"

namespace tema2 {
namespace properties {

WorldObject::WorldObject(float boundingRadius, bool collisionEnabled)
    : _modelMatrix(1.0f), _scale(1.0f, 1.0f, 1.0f), _position(0.0f, 0.0f, 0.0f),
      _rotation(1, 0, 0, 0), _dirty(true),
      _boundingRadius(boundingRadius), _collisionEnabled(collisionEnabled) {}

// --- Transform ---

const glm::vec3 WorldObject::getPosition() const { return _position; }

const glm::vec3 WorldObject::getScale() const { return _scale; }

const glm::vec3 WorldObject::getRotation() const { return glm::eulerAngles(_rotation); }

void WorldObject::setPosition(const glm::vec3 &position) {
  _position = position;
  _dirty = true;
}

void WorldObject::setScale(const glm::vec3 &scale) {
  _scale = scale;
  _dirty = true;
}

void WorldObject::setRotation(const glm::vec3 &radians) {
  glm::quat qY = glm::angleAxis(radians.y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::quat qX = glm::angleAxis(radians.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::quat qZ = glm::angleAxis(radians.z, glm::vec3(0.0f, 0.0f, 1.0f));
  _rotation = glm::normalize(qY * qX * qZ);
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

void WorldObject::rotateLocal(const glm::vec3 &rotation) {
  glm::quat qPitch = glm::angleAxis(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::quat qYaw   = glm::angleAxis(rotation.y,   glm::vec3(0.0f, 1.0f, 0.0f));
  glm::quat qRoll  = glm::angleAxis(rotation.z,  glm::vec3(0.0f, 0.0f, 1.0f));
  _rotation = glm::normalize(_rotation * qYaw * qPitch * qRoll);
  _dirty = true;
}

void WorldObject::rotateGlobal(const glm::vec3 &rotation) {
  glm::quat qPitch = glm::angleAxis(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::quat qYaw   = glm::angleAxis(rotation.y,   glm::vec3(0.0f, 1.0f, 0.0f));
  glm::quat qRoll  = glm::angleAxis(rotation.z,  glm::vec3(0.0f, 0.0f, 1.0f));
  _rotation = glm::normalize(qYaw * qPitch * qRoll * _rotation);
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

glm::vec3 WorldObject::getForward() const {
  return glm::normalize(_rotation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 WorldObject::getUp() const {
  return glm::normalize(_rotation * glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 WorldObject::getRight() const {
  return glm::normalize(_rotation * glm::vec3(1.0f, 0.0f, 0.0f));
}

const glm::mat4 &WorldObject::getModelMatrix() const {
  if (_dirty) {
    _modelMatrix = glm::mat4(1.0f);
    _modelMatrix *=
        utils::transform::translate(_position.x, _position.y, _position.z);
    _modelMatrix *= glm::mat4_cast(_rotation);
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
