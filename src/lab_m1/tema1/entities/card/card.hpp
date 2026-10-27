#pragma once

// WARNING: including card_fwd.hpp might be useful in the future
#include "tema1/entities/effect/effect_fwd.hpp"

namespace tema1 {
namespace entities {

class Card {
public:
  void onMouseEnter();
  void onMouseLeave();
  void render();

  EffectPtr effect;

private:
  // game-related
  int manaCost;
  int attack;
  int defense; // TODO: check if needed

  // animation-related
  float scaleX, scaleY;
  float posX, posY;
};

} // namespace entities
} // namespace tema1
