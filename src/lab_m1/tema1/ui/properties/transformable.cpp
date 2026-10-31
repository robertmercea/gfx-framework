#include "transformable.hpp"
#include "tema1/ui/transform/transform.hpp"

namespace tema1 {
namespace ui {

Transformable::Transformable()
    : _modelMatrix(1.0f), _scale(1.0f, 1.0f), _position(0.0f, 0.0f),
      _rotation(0.0f) {}

const glm::vec2 &Transformable::getPosition() const { return _position; }

const glm::vec2 &Transformable::getScale() const { return _scale; }

float Transformable::getRotation() const { return _rotation; }

void Transformable::setPosition(const glm::vec2 &position) {
  _position = position;
}

void Transformable::setScale(const glm::vec2 &scale) { _scale = scale; }

void Transformable::setRotation(float radians) { _rotation = radians; }

void Transformable::scale(float amount) {
  _scale.x += amount;
  _scale.y += amount;
}

void Transformable::scale(float scaleX, float scaleY) {
  _scale.x += scaleX;
  _scale.y += scaleY;
}

void Transformable::scale(const glm::vec2 &scale) { _scale += scale; }

void Transformable::rotate(float radians) { _rotation += radians; }

void Transformable::translate(float translateX, float translateY) {
  _position.x += translateX;
  _position.y += translateY;
}

void Transformable::translate(const glm::vec2 &position) {
  _position += position;
}

const glm::mat3 &Transformable::getModelMatrix() {
  // TODO: figure out how to make this less horribly inefficient
  _modelMatrix = glm::mat3(1.0f);
  _modelMatrix *= tema1::ui::transform::translate(_position.x, _position.y);
  _modelMatrix *= tema1::ui::transform::rotate(_rotation);
  _modelMatrix *= tema1::ui::transform::scale(_scale.x, _scale.y);

  return _modelMatrix;
}

} // namespace ui
} // namespace tema1
