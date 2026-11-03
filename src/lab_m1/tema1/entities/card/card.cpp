#include "tema1/entities/card/card.hpp"
#include "tema1/entities/card/card_data/card_data.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/ui/card/card.hpp"

namespace tema1 {
namespace entities {

Card::Card(globals::CardType cardType, globals::SpriteType spriteType)
    : cardData(cardType), cardUI(cardType, spriteType) {}

void Card::getSpriteProperties(
    std::vector<sprites::SpriteProperties> &spriteProps) {
    cardUI.getSpriteProperties(spriteProps);
}

void Card::update(float deltaTime) {
    cardUI.update(deltaTime);
}

} // namespace entities
} // namespace tema1
