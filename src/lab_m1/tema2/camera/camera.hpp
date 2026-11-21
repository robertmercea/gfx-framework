#pragma once

#include "core/window/window_object.h"

namespace tema2 {
namespace camera {

class Camera {
public:
  Camera();
  Camera(const glm::vec3 &position, const glm::vec3 &center,
         const glm::vec3 &up);
  ~Camera() = default;

  void Set(const glm::vec3 &position, const glm::vec3 &center,
           const glm::vec3 &up);

  glm::mat4 getViewMatrix() const;
  glm::vec3 getTargetPosition() const;

  void onInputUpdate(WindowObject *window, float deltaTime, int mods);
  bool onMouseMove(WindowObject *window, int mouseX, int mouseY, int deltaX,
                   int deltaY);

  void moveForward(float distance);
  void translateForward(float distance);
  void translateUpward(float distance);
  void translateRight(float distance);

  void rotateFirstPerson_OX(float angle);
  void rotateFirstPerson_OY(float angle);
  void rotateFirstPerson_OZ(float angle);

  void rotateThirdPerson_OX(float angle);
  void rotateThirdPerson_OY(float angle);
  void rotateThirdPerson_OZ(float angle);

private:
  static constexpr float SENSITITY_OX = 0.001f;
  static constexpr float SENSITITY_OY = 0.001f;
  static constexpr float CAMERA_SPEED = 10.0f;
  float distanceToTarget;
  glm::vec3 position;
  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
};

} // namespace camera
} // namespace tema2
