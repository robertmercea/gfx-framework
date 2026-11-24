#pragma once

#include "core/window/window_object.h"
#include "tema2/properties/world_object/world_object.hpp"

namespace tema2 {
namespace entities {

using namespace properties;

class Spaceship : public WorldObject {
public:
  // body
  static constexpr float BODY_HITBOX_RADIUS = 2.2f;
  static constexpr float BODY_WIDTH = 1.0f;
  static constexpr float BODY_HEIGHT = 1.0f;
  static constexpr float BODY_DEPTH = 2.4f;

  // cockpit
  static constexpr float COCKPIT_RADIUS = BODY_WIDTH * 0.5f;
  static constexpr float COCKPIT_OFFSET_Y = 0.0f;
  static constexpr float COCKPIT_OFFSET_Z = -BODY_DEPTH * 0.5f;
  static constexpr float COCKPIT_ROTATION_X = -M_PI_2;

  // wing
  static constexpr float WING_LENGTH = 1.3f; // l (chord along Z & cross-section)
  static constexpr float WING_HEIGHT = 0.5f; // h (thickness along Y after ±90° Z rotation)
  static constexpr float WING_OFFSET_X =
      BODY_WIDTH * 0.5f + (WING_LENGTH * 1.7320508f) / 6.0f;
  static constexpr float WING_OFFSET_Y = 0.05f;
  static constexpr float WING_OFFSET_Z = 0.25f;
  static constexpr float LEFT_WING_ROTATION_Z = -M_PI_2;
  static constexpr float RIGHT_WING_ROTATION_Z = M_PI_2;

  // thruster
  static constexpr float THRUSTER_RADIUS = 0.22f;
  static constexpr float THRUSTER_HEIGHT = 0.6f;
  static constexpr float THRUSTER_OFFSET_X = BODY_WIDTH * 0.28f;
  static constexpr float THRUSTER_OFFSET_Z =
      BODY_DEPTH * 0.5f + THRUSTER_HEIGHT * 0.75f;

  // movement
  static constexpr float SPACESHIP_SPEED = 10.0f;
  static constexpr float ROTATION_SPEED = 0.005f;
  static constexpr float ROLL_MULTIPLIER = 300.0f;

  Spaceship();
  ~Spaceship() override;

  Spaceship(const Spaceship &) = delete;
  Spaceship &operator=(const Spaceship &) = delete;

  void render(const RenderFunction &renderFunc, const RenderContext &ctx) const override;
  const glm::vec3 &getCollisionCenter() const override;
  bool collidesWith(const WorldObject &other) const override;

  void onInputUpdate(const WindowObject *window, float deltaTime, int mods);
  void onMouseMove(const WindowObject *window, int mouseX, int mouseY, int deltaX,
                   int deltaY);

private:
  WorldObject *cockpit;
  WorldObject *body;
  WorldObject *leftWing, *rightWing;
  WorldObject *leftThruster, *rightThruster;
};

} // namespace entities
} // namespace tema2
