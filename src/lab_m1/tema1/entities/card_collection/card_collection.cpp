#include "card_collection.hpp"
#include "tema1/entities/card/card.hpp"
#include <iostream>
#include <memory>

namespace tema1 {
namespace entities {

CardPtr CardCollection::drawTopCard() {
  CardPtr card = cards.back();
  cards.pop_back();

  return card;
}

void CardCollection::pushCard(const CardPtr card) {
  cards.push_back(card);
}

void CardCollection::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  for (const auto &cardPtr : cards) {
    cardPtr->cardUI.getSpriteProperties(spriteProps);
  }
}

void CardCollection::setRenderMode(RenderMode mode) {
  switch (mode) {
    case tema1::entities::RenderMode::PLAYER:
      setCardRenderMode(true);
      break;
    case tema1::entities::RenderMode::ENEMY:
      setCardRenderMode(false);
      break;
    default:
      std::cerr << "[CardCollection] Unknown render mode\n";
      break;
  }
}

void CardCollection::setCardRenderMode(bool showFront) {
  for (const auto &cardPtr : cards) {
    cardPtr->cardUI.showFront(showFront);
  }
}

CardVectorPtr CardCollection::getCards() {
  return std::make_shared<CardVector>(cards);
}

} // namespace entities
} // namespace tema1
