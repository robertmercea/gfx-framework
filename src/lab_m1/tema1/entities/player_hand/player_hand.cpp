#include "player_hand.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/globals/player/player.hpp"
#include <iostream>
#include <memory>

namespace tema1 {
namespace entities {

void PlayerHand::pushCard(const CardPtr card) {
  cards.push_back(card);
}

void PlayerHand::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  for (const auto &cardPtr : cards) {
    cardPtr->cardUI.getSpriteProperties(spriteProps);
  }
}

void PlayerHand::showCards(bool show) {
  for (const auto &cardPtr : cards) {
    cardPtr->cardUI.showFront(show);
  }
}

CardVectorPtr PlayerHand::getCards() {
  return std::make_shared<CardVector>(cards);
}

} // namespace entities
} // namespace tema1
