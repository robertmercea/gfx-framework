#include "card_deck.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/globals/player/player.hpp"
#include <iostream>
#include <memory>

namespace tema1 {
namespace entities {

CardPtr CardDeck::drawTopCard() {
  CardPtr card = cards.back();
  cards.pop_back();

  return card;
}

void CardDeck::pushCard(const CardPtr card) {
  cards.push_back(card);
}

void CardDeck::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  for (const auto &cardPtr : cards) {
    cardPtr->cardUI.getSpriteProperties(spriteProps);
  }
}

void CardDeck::setRenderMode(globals::player::PlayerType mode) {
  switch (mode) {
    case globals::player::PlayerType::HUMAN:
      setCardRenderMode(true);
      break;
    case globals::player::PlayerType::AI:
      setCardRenderMode(false);
      break;
    default:
      std::cerr << "[CardDeck] Unknown render mode\n";
      break;
  }
}

void CardDeck::setCardRenderMode(bool showFront) {
  for (const auto &cardPtr : cards) {
    cardPtr->cardUI.showFront(showFront);
  }
}

const CardVector& CardDeck::getCards() const {
  return cards;
}

} // namespace entities
} // namespace tema1
