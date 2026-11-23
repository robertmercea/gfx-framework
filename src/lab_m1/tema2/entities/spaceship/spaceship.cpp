#include "spaceship.hpp"
#include "tema2/entities/spaceship/body/body.hpp"
#include "tema2/entities/spaceship/cockpit/cockpit.hpp"
#include "tema2/entities/spaceship/thruster/thruster.hpp"
#include "tema2/entities/spaceship/wing/wing.hpp"
#include "tema2/properties/world_object/world_object.hpp"

namespace tema2 {
namespace entities {

Spaceship::Spaceship() : WorldObject(0.0f, true) {
  // body @ origin (0,0,0)
  body = new spaceship::Body(
      "parallelepiped", "VertexColor", glm::vec3(0.75f, 0.75f, 0.82f),
      BODY_HITBOX_RADIUS, BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
  body->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

  cockpit = new spaceship::Cockpit(
      "hemisphere", "VertexColor", glm::vec3(0.2f, 0.7f, 0.95f),
      COCKPIT_RADIUS);
  cockpit->setPosition(glm::vec3(0.0f, COCKPIT_OFFSET_Y, COCKPIT_OFFSET_Z));
  cockpit->setRotation(glm::vec3(COCKPIT_ROTATION_X, 0, 0));

  leftWing = new spaceship::Wing(
      "prism", "VertexColor", glm::vec3(0.85f, 0.25f, 0.25f),
      WING_LENGTH, WING_LENGTH, WING_HEIGHT);
  leftWing->setPosition(glm::vec3(-WING_OFFSET_X, WING_OFFSET_Y, WING_OFFSET_Z));
  leftWing->setRotation(glm::vec3(0, 0, LEFT_WING_ROTATION_Z));

  rightWing = new spaceship::Wing(
      "prism", "VertexColor", glm::vec3(0.85f, 0.25f, 0.25f),
      WING_LENGTH, WING_LENGTH, WING_HEIGHT);
  rightWing->setPosition(glm::vec3(WING_OFFSET_X, WING_OFFSET_Y, WING_OFFSET_Z));
  rightWing->setRotation(glm::vec3(0, 0, RIGHT_WING_ROTATION_Z));

  leftThruster = new spaceship::Thruster(
      "cone", "VertexColor", glm::vec3(1.0f, 0.55f, 0.1f),
      THRUSTER_RADIUS, THRUSTER_RADIUS, THRUSTER_HEIGHT);
  leftThruster->setPosition(glm::vec3(-THRUSTER_OFFSET_X, 0.0f, THRUSTER_OFFSET_Z));

  rightThruster = new spaceship::Thruster(
      "cone", "VertexColor", glm::vec3(1.0f, 0.55f, 0.1f),
      THRUSTER_RADIUS, THRUSTER_RADIUS, THRUSTER_HEIGHT);
  rightThruster->setPosition(glm::vec3(THRUSTER_OFFSET_X, 0.0f, THRUSTER_OFFSET_Z));

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
}

void Spaceship::render(const RenderFunction &renderFunc, const RenderContext &ctx) const {
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
    if (!part->isCollisionEnabled()) continue;

    for (const WorldObject *otherPart : other.getComponents()) {
      if (part->collidesWith(*otherPart)) {
        return true;
      }
    }

  }

  return false;
}

} // namespace entities
} // namespace tema2
