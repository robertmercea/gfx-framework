#pragma once

#include "tema1/globals/cards/stats/stats.hpp"
#include "tema1/entities/properties/effect/effect_fwd.hpp"
#include "tema1/globals/cards/types/types.hpp"

namespace tema1 {
namespace entities {

class CardData {
public:
  CardData(globals::CardType);
  globals::stats::CardStats stats;
  EffectPtr effect;
};

} // namespace entities
} // namespace tema1
