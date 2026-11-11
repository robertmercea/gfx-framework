#pragma once

#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/properties/effect/effect.hpp"

namespace tema1 {
namespace entities {

class TankEffect : public Effect {
public:
  virtual void onAttack(CardPtr def, CardPtr atk, Game &game) override;
  virtual void onPlay(CardPtr card, Game &game) override;
  virtual void onDestroy(CardPtr card, Game &game) override;
};

} // namespace entities
} // namespace tema1
