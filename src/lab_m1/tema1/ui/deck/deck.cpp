#include "deck.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/ui/card/card.hpp"
#include <algorithm>

namespace tema1 {
namespace ui {

void Deck::setCardsInDeck(const std::vector<entities::CardPtr> &cards) {
  cardsInDeck = cards;
  arrangeCards();
}

const std::vector<entities::CardPtr> &Deck::getCardsInDeck() const {
  return cardsInDeck;
}

void Deck::arrangeCards() {
  int size = cardsInDeck.size();
  
  for (int i = 0; i < size; ++i) {
    // top card is at the back of the vector (index: size - 1) and gets 0 offset.
    // cards below it get progressively larger offsets, capped at MAX_VISIBLE_CARDS.
    int offsetMultiplier = std::min(size - 1 - i, MAX_VISIBLE_CARDS - 1);
    
    glm::vec2 cardPos = _position + glm::vec2(OFFSET_X * offsetMultiplier, OFFSET_Y * offsetMultiplier);
    
    cardsInDeck[i]->cardUI.setPosition(cardPos);
    cardsInDeck[i]->cardUI.setScale(_scale);
  }
}

void Deck::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  int size = cardsInDeck.size();
  if (size == 0) return;

  int startIndex = std::max(0, size - MAX_VISIBLE_CARDS);
  
  // draw from bottom to top
  for (int i = startIndex; i < size; ++i) {
    cardsInDeck[i]->cardUI.getSpriteProperties(spriteProps);
  }
}

void Deck::setPosition(const glm::vec2 &position) {
  Transformable::setPosition(position);
  arrangeCards();
}

void Deck::setScale(const glm::vec2 &scale) {
  Transformable::setScale(scale);
  arrangeCards();
}

} // namespace ui
} // namespace tema1
