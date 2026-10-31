#pragma once

// WARNING: including card_fwd.hpp might be useful in the future
#include "tema1/entities/card/card_data/card_data.hpp"
#include "tema1/ui/card/card.hpp"

namespace tema1 {
namespace entities {

class Card {
public:
  // TODO: card stuff

private:
  CardData cardData;
  ui::Card cardUI;
};

} // namespace entities
} // namespace tema1
