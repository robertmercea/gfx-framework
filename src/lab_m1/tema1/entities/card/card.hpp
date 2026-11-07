#pragma once

#include "tema1/entities/card/card_data/card_data.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/ui/card/card.hpp"

namespace tema1 {
namespace entities {

class Card {
public:
  CardData cardData;
  ui::Card cardUI;
  Card(globals::CardType, globals::SpriteType);
  bool hasAttackedThisTurn = false;
  bool playedThisTurn = false;


private:
};

} // namespace entities
} // namespace tema1
