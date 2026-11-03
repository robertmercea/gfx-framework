#pragma once

#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

using CardType = entities::CardType;

class Card : public Transformable {
public:
  static constexpr float MOUSE_ENTER_SCALE_FACTOR = 1.5f;
  static constexpr float MOUSE_LEAVE_SCALE_FACTOR = 0.0f;

  Card(CardType type, int health, int manaCost, int attack, std::shared_ptr<sprites::Sprite> cardFront,
       std::shared_ptr<sprites::Sprite> cardBack);

  void showFront();
  void showBack();
  void flip();
  void shake(float amount);
  void onMouseEnter();
  void onMouseLeave();
  void update(float deltaTime);

  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);

private:
  const float HEART_RADIUS = 0.15f;
  int totalHealth;
  bool frontRender;
  float shakeAmount = 0.f;
  float scaleAmount = 0.f;
  glm::vec2 defaultScale;
  CardType type;
  std::shared_ptr<sprites::Sprite> cardFront, cardBack;
  std::vector<std::shared_ptr<sprites::Sprite>> healthSprites, manaCostSprites, attackSprites;

  void createHearts(int amount);
  void createManaCost(int amount);
  void renderHearts(std::vector<sprites::SpriteProperties> &spriteProps, const glm::mat3 &baseMatrix);
  void renderManaCost(std::vector<sprites::SpriteProperties> &spriteProps, const glm::mat3 &baseMatrix);
};

} // namespace ui
} // namespace tema1
