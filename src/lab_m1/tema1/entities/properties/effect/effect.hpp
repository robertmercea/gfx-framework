// effect.hpp
#pragma once

// WARNING: including effect_fwd.hpp might be useful in the future
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/game/game.hpp"

namespace tema1 {
namespace entities {

class Effect {
public:
  virtual ~Effect() = default;
  virtual void onAttack(CardPtr def, CardPtr atk, Game &game) = 0;
  virtual void onPlay(CardPtr card, Game &game) = 0;
  virtual void onDestroy(CardPtr card, Game &game) = 0;
};

} // namespace entities
} // namespace tema1
