#include "spaceship.hpp"
#include "GLFW/glfw3.h"
#include "glm/geometric.hpp"
#include "tema2/entities/spaceship/body/body.hpp"
#include "tema2/entities/spaceship/cockpit/cockpit.hpp"
#include "tema2/entities/spaceship/thruster/thruster.hpp"
#include "tema2/entities/spaceship/wing/wing.hpp"
#include "tema2/properties/world_object/world_object.hpp"

namespace tema2 {
namespace entities {

Spaceship::Spaceship() : WorldObject(0.0f, true) {
  // body @ origin (0,0,0)
  body = new spaceship::Body("parallelepiped", "VertexColor",
                             glm::vec3(0.75f, 0.75f, 0.82f), BODY_HITBOX_RADIUS,
                             BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
  body->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

  cockpit =
      new spaceship::Cockpit("hemisphere", "VertexColor",
                             glm::vec3(0.2f, 0.7f, 0.95f), COCKPIT_RADIUS);
  cockpit->setPosition(glm::vec3(0.0f, COCKPIT_OFFSET_Y, COCKPIT_OFFSET_Z));
  cockpit->setRotation(glm::vec3(COCKPIT_ROTATION_X, 0, 0));

  leftWing = new spaceship::Wing("prism", "VertexColor",
                                 glm::vec3(0.85f, 0.25f, 0.25f), WING_LENGTH,
                                 WING_LENGTH, WING_HEIGHT);
  leftWing->setPosition(
      glm::vec3(-WING_OFFSET_X, WING_OFFSET_Y, WING_OFFSET_Z));
  leftWing->setRotation(glm::vec3(0, 0, LEFT_WING_ROTATION_Z));

  rightWing = new spaceship::Wing("prism", "VertexColor",
                                  glm::vec3(0.85f, 0.25f, 0.25f), WING_LENGTH,
                                  WING_LENGTH, WING_HEIGHT);
  rightWing->setPosition(
      glm::vec3(WING_OFFSET_X, WING_OFFSET_Y, WING_OFFSET_Z));
  rightWing->setRotation(glm::vec3(0, 0, RIGHT_WING_ROTATION_Z));

  leftThruster = new spaceship::Thruster(
      "cone", "VertexColor", glm::vec3(1.0f, 0.55f, 0.1f), THRUSTER_RADIUS,
      THRUSTER_RADIUS, THRUSTER_HEIGHT);
  leftThruster->setPosition(
      glm::vec3(-THRUSTER_OFFSET_X, 0.0f, THRUSTER_OFFSET_Z));

  rightThruster = new spaceship::Thruster(
      "cone", "VertexColor", glm::vec3(1.0f, 0.55f, 0.1f), THRUSTER_RADIUS,
      THRUSTER_RADIUS, THRUSTER_HEIGHT);
  rightThruster->setPosition(
      glm::vec3(THRUSTER_OFFSET_X, 0.0f, THRUSTER_OFFSET_Z));

  addComponent(body);
  addComponent(cockpit);
  addComponent(leftWing);
  addComponent(rightWing);
  addComponent(leftThruster);
  addComponent(rightThruster);
}

Spaceship::~Spaceship() {
  delete body;
  delete cockpit;
  delete leftWing;
  delete rightWing;
  delete leftThruster;
  delete rightThruster;
  _components.clear();
}

void Spaceship::render(const RenderFunction &renderFunc,
                       const RenderContext &ctx) const {
  const glm::mat4 &shipMatrix = getModelMatrix();

  RenderContext childCtx = ctx;
  childCtx.parentMatrix = shipMatrix;

  for (const WorldObject *part : _components) {
    part->render(renderFunc, childCtx);
  }
}

const glm::vec3 &Spaceship::getCollisionCenter() const {
  return body->getCollisionCenter();
}

bool Spaceship::collidesWith(const WorldObject &other) const {
  if (!_collisionEnabled || !other.isCollisionEnabled()) {
    return false;
  }

  for (const WorldObject *part : _components) {
    if (!part->isCollisionEnabled())
      continue;

    for (const WorldObject *otherPart : other.getComponents()) {
      if (part->collidesWith(*otherPart)) {
        return true;
      }
    }
  }

  return false;
}

void Spaceship::onInputUpdate(const WindowObject *window, float deltaTime,
                              int mods) {
  int moveForward = 0;
  int moveRight = 0;
  int moveUp = 0;

  if (window->KeyHold(GLFW_KEY_W))
    moveForward += 1;
  if (window->KeyHold(GLFW_KEY_S))
    moveForward -= 1;

  if (window->KeyHold(GLFW_KEY_E))
    moveRight += 1;
  if (window->KeyHold(GLFW_KEY_Q))
    moveRight -= 1;

  if (window->KeyHold(GLFW_KEY_Z))
    moveUp += 1;
  if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
    moveUp -= 1;

  glm::vec3 moveDirection = getForward() * static_cast<float>(moveForward) +
                            getRight() * static_cast<float>(moveRight) +
                            getUp() * static_cast<float>(moveUp);

  if (glm::length(moveDirection) > 0) {
    moveDirection = glm::normalize(moveDirection);
    translate(moveDirection * SPACESHIP_SPEED * deltaTime);
  }

  if (window->KeyHold(GLFW_KEY_A)) {
    rotateLocal(
        glm::vec3(0.0f, 0.0f, ROTATION_SPEED * deltaTime * ROLL_MULTIPLIER));
  }

  if (window->KeyHold(GLFW_KEY_D)) {
    rotateLocal(
        glm::vec3(0.0f, 0.0f, -ROTATION_SPEED * deltaTime * ROLL_MULTIPLIER));
  }
}

void Spaceship::onMouseMove(const WindowObject *window, int mouseX, int mouseY,
                            int deltaX, int deltaY) {
  rotateLocal(
      glm::vec3(-deltaY * ROTATION_SPEED, -deltaX * ROTATION_SPEED, 0.0f));
}

} // namespace entities
} // namespace tema2
