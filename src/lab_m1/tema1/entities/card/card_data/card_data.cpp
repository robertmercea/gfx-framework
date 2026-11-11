#include "card_data.hpp"
#include "tema1/globals/cards/effects/effects.hpp"
#include "tema1/globals/cards/stats/stats.hpp"
#include "tema1/globals/cards/types/types.hpp"

namespace tema1 {
namespace entities {

CardData::CardData(globals::CardType type) {
  this->stats = globals::stats::CARD_PROPERTIES.at(type);
  this->effect = globals::effects::CARD_EFFECTS.at(type);
}

}
}
