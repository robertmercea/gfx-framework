// effect.hpp
#pragma once

// WARNING: including effect_fwd.hpp might be useful in the future
#include "tema1/entities/battle_cards/battle_cards.hpp"
#include "tema1/entities/card/card_fwd.hpp"

namespace tema1 {
namespace entities {

class Effect {
public:
  void use(const CardPtr card, const BattleCardsPtr battleCards);
};

} // namespace entities
} // namespace tema1
