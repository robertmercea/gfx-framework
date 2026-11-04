#include "tema1/entities/card/card.hpp"
#include "tema1/entities/card/card_data/card_data.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/ui/card/card.hpp"

namespace tema1 {
namespace entities {

Card::Card(globals::CardType cardType, globals::SpriteType spriteType)
    : cardUI(cardType, spriteType), cardData(cardType)  {}

} // namespace entities
} // namespace tema1
