#pragma once

#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

class Card : public Transformable {
public:
  static constexpr float MOUSE_ENTER_SCALE_FACTOR = 1.5f;
  static constexpr float MOUSE_LEAVE_SCALE_FACTOR = 0.0f;
  const glm::vec2 DEFAULT_SCALE = {40.0f, 50.0f};

  Card(globals::CardType, globals::SpriteType);

  void showFront(bool show);
  void showFront();
  void showBack();
  void flip();
  void shake(float amount);
  void unselect();
  void onHoverEnter();
  void onHoverLeave();
  void prepareToAttack();

  void onMouseMove(float mouseX, float mouseY);
  void onMouseBtnPress(float mouseX, float mouseY);
  void onMouseBtnRelease(float mouseX, float mouseY);

  void update(float deltaTime);
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
  void setBorderColor(const glm::vec3 &color) { borderColor = color; }
  void setHealth(int newHealth) { health = newHealth; }

  void setInitialPosition(const glm::vec2 &position);
  bool contains(float x, float y);

private:
  static constexpr const float HEART_RADIUS = 0.15f;
  static constexpr const float MANA_SIZE = 0.1f;
  static constexpr const float SWORD_SIZE = 0.2f;
  static constexpr const float SELECTED_SCALING = 1.5f;
  static constexpr const float PREPARED_SCALING = 0.25f;

  int totalHealth;
  int health, manaCost, attack;
  bool frontRender;
  float shakeAmount = 0.f;
  float scaleAmount = 0.f;
  bool isSelected = false;

  glm::vec2 defaultScale;
  glm::vec2 defaultPosition;
  glm::vec3 borderColor = ui::colors::WHITE;

  globals::CardType type;
  std::shared_ptr<sprites::Sprite> cardFront, cardBack, heartSprite, manaCostSprite, attackSprite;

  void createHearts(int amount);
  void createManaCost(int amount);
  void createAttack(int amount);

  void renderHearts(std::vector<sprites::SpriteProperties> &spriteProps, const glm::mat3 &baseMatrix);
  void renderManaCost(std::vector<sprites::SpriteProperties> &spriteProps, const glm::mat3 &baseMatrix);
  void renderAttack(std::vector<sprites::SpriteProperties> &spriteProps, const glm::mat3 &baseMatrix);
};

} // namespace ui
} // namespace tema1
