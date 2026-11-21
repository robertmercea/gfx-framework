#include "camera.hpp"

namespace tema2 {
namespace camera {

Camera::Camera() {
  position = glm::vec3(0, 2, 5);
  forward = glm::vec3(0, 0, -1);
  up = glm::vec3(0, 1, 0);
  right = glm::vec3(1, 0, 0);
  distanceToTarget = 2;
}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &center,
               const glm::vec3 &up) {
  Set(position, center, up);
}

void Camera::Set(const glm::vec3 &position, const glm::vec3 &center,
                 const glm::vec3 &up) {
  this->position = position;
  forward = glm::normalize(center - position);
  right = glm::normalize(glm::cross(forward, up));
  this->up = glm::normalize(glm::cross(right, forward));
}

void Camera::moveForward(float distance) {
  glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
  position += dir * distance;
}

void Camera::translateForward(float distance) {
  position += glm::normalize(forward) * distance;
}

void Camera::translateUpward(float distance) {
  position += glm::normalize(up) * distance;
}

void Camera::translateRight(float distance) {
  glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
  position += dir * distance;
}

void Camera::rotateFirstPerson_OX(float angle) {
  forward = glm::normalize(glm::vec3(
      glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 0.0f)));
  up = glm::normalize(glm::cross(right, forward));
}

void Camera::rotateFirstPerson_OY(float angle) {
  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
  forward = glm::normalize(glm::vec3(rot * glm::vec4(forward, 0.0f)));
  right = glm::normalize(glm::vec3(rot * glm::vec4(right, 0.0f)));
  up = glm::normalize(glm::cross(right, forward));
}

void Camera::rotateFirstPerson_OZ(float angle) {
  right = glm::normalize(glm::vec3(
      glm::rotate(glm::mat4(1.0f), angle, forward) * glm::vec4(right, 0.0f)));
  up = glm::normalize(glm::cross(right, forward));
}

void Camera::rotateThirdPerson_OX(float angle) {
  translateForward(distanceToTarget);
  rotateFirstPerson_OX(angle);
  translateForward(-distanceToTarget);
}

void Camera::rotateThirdPerson_OY(float angle) {
  translateForward(distanceToTarget);
  rotateFirstPerson_OY(angle);
  translateForward(-distanceToTarget);
}

void Camera::rotateThirdPerson_OZ(float angle) {
  translateForward(distanceToTarget);
  rotateFirstPerson_OZ(angle);
  translateForward(-distanceToTarget);
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + forward, up);
}

glm::vec3 Camera::getTargetPosition() const {
  return position + forward * distanceToTarget;
}

void Camera::onInputUpdate(WindowObject *window, float deltaTime, int mods) {
  if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

    if (window->KeyHold(GLFW_KEY_W)) {
      translateForward(CAMERA_SPEED * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
      translateRight(-CAMERA_SPEED * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_S)) {
      translateForward(-CAMERA_SPEED * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
      translateRight(CAMERA_SPEED * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
      translateUpward(-CAMERA_SPEED * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_E)) {
      translateUpward(CAMERA_SPEED * deltaTime);
    }
  }
}

bool Camera::onMouseMove(WindowObject *window, int mouseX, int mouseY,
                         int deltaX, int deltaY) {
  if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
    if (window->GetSpecialKeyState() == 0) {
      rotateFirstPerson_OX(-deltaY * SENSITITY_OX);
      rotateFirstPerson_OY(-deltaX * SENSITITY_OY);
      return false; // renderCameraTarget = false
    }

    if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
      rotateThirdPerson_OX(-deltaY * SENSITITY_OX);
      rotateThirdPerson_OY(-deltaX * SENSITITY_OY);
      return true; // renderCameraTarget = true
    }
  }

  return false;
}

} // namespace camera
} // namespace tema2
