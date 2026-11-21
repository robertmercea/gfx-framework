#include "transformable.hpp"
#include "tema2/utils/transform/transform.hpp"

namespace tema2 {
namespace properties {

Transformable::Transformable()
    : _modelMatrix(1.0f), _scale(1.0f, 1.0f, 1.0f), _position(0.0f, 0.0f, 0.0f),
      _rotation(0.0f, 0.0f, 0.0f), _dirty(true) {}

const glm::vec3 &Transformable::getPosition() const { return _position; }

const glm::vec3 &Transformable::getScale() const { return _scale; }

const glm::vec3 &Transformable::getRotation() const { return _rotation; }

void Transformable::setPosition(const glm::vec3 &position) {
  _position = position;
  _dirty = true;
}

void Transformable::setScale(const glm::vec3 &scale) {
  _scale = scale;
  _dirty = true;
}

void Transformable::setRotation(const glm::vec3 &radians) {
  _rotation = radians;
  _dirty = true;
}

void Transformable::scale(float amount) {
  _scale *= amount;
  _dirty = true;
}

void Transformable::scale(float scaleX, float scaleY, float scaleZ) {
  _scale *= glm::vec3(scaleX, scaleY, scaleZ);
  _dirty = true;
}

void Transformable::scale(const glm::vec3 &scale) {
  _scale *= scale;
  _dirty = true;
}

void Transformable::rotate(float radX, float radY, float radZ) {
  _rotation += glm::vec3(radX, radY, radZ);
  _dirty = true;
}

void Transformable::rotate(const glm::vec3 &radians) {
  _rotation += radians;
  _dirty = true;
}

void Transformable::rotateX(float radians) {
  _rotation.x += radians;
  _dirty = true;
}

void Transformable::rotateY(float radians) {
  _rotation.y += radians;
  _dirty = true;
}

void Transformable::rotateZ(float radians) {
  _rotation.z += radians;
  _dirty = true;
}

void Transformable::translate(float translateX, float translateY,
                              float translateZ) {
  _position += glm::vec3(translateX, translateY, translateZ);
  _dirty = true;
}

void Transformable::translate(const glm::vec3 &offset) {
  _position += offset;
  _dirty = true;
}

const glm::mat4 &Transformable::getModelMatrix() {
  if (_dirty) {
    _modelMatrix = glm::mat4(1.0f);
    _modelMatrix *= transform::translate(_position.x, _position.y, _position.z);
    _modelMatrix *= transform::rotateOY(_rotation.y);
    _modelMatrix *= transform::rotateOX(_rotation.x);
    _modelMatrix *= transform::rotateOZ(_rotation.z);
    _modelMatrix *= transform::scale(_scale.x, _scale.y, _scale.z);
    _dirty = false;
  }
  return _modelMatrix;
}

} // namespace transform
} // namespace tema2
