#pragma once

#include "tema1/entities/card/card_data/card_data.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/ui/card/card.hpp"

namespace tema1 {
namespace entities {

class Card {
public:
  ui::Card cardUI;
  Card(globals::CardType, globals::SpriteType);

private:
  CardData cardData;
};

} // namespace entities
} // namespace tema1
