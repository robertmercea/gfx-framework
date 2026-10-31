#pragma once

#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <memory>
#include <vector>

namespace tema1 {
namespace ui {

class Card : public Transformable {
public:
  enum CardType {
    WIZARD,
    KNIGHT,
    MAGE,
    DWARF,
  };

  static constexpr float MOUSE_ENTER_SCALE_FACTOR = 1.5f;
  static constexpr float MOUSE_LEAVE_SCALE_FACTOR = 0.0f;

  Card(CardType type, std::shared_ptr<sprites::Sprite> cardFront,
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
  bool frontRender;
  float shakeAmount = 0.f;
  float scaleAmount = 0.f;
  glm::vec2 defaultScale;
  CardType type;
  std::shared_ptr<sprites::Sprite> cardFront, cardBack;
};

} // namespace ui
} // namespace tema1
