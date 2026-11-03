#pragma once

#include "tema1/globals/cards/stats/stats.hpp"
#include "tema1/entities/effect/effect_fwd.hpp"

namespace tema1 {
namespace entities {

class CardData {
public:
  globals::stats::CardStats stats;
  EffectPtr effect;
};

} // namespace entities
} // namespace tema1
