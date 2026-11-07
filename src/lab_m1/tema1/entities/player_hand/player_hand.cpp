#include "player_hand.hpp"
#include "tema1/entities/card/card.hpp"
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

const CardVector& PlayerHand::getCards() const {
  return cards;
}

void PlayerHand::removeCard(const CardPtr card) {
  cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
}

void PlayerHand::setCenter(glm::vec2 center) {
  this->center = center;
}

glm::vec2 PlayerHand::getCenter() const {
  return this->center;
}

float PlayerHand::getMaxWidth() const {
  return this->maxWidth;
}

void PlayerHand::setMaxWidth(float maxWidth) {
  this->maxWidth = maxWidth;
}

void PlayerHand::arrangeCards() {
  if (cards.empty()) return;

  float padding = 10.0f;
  float cardW = std::abs(cards[0]->cardUI.getScale().x);
  float totalCardWidth = cards.size() * cardW + (cards.size() - 1) * padding;
  
  float startX = center.x;
  float stepX = cardW + padding;

  if (totalCardWidth > maxWidth) {
    stepX = (maxWidth - cardW) / std::max(1.0f, static_cast<float>(cards.size() - 1));
    startX = center.x - (maxWidth / 2.0f) + (cardW / 2.0f);
  } else {
    startX = center.x - (totalCardWidth / 2.0f) + (cardW / 2.0f);
  }

  for (size_t i = 0; i < cards.size(); ++i) {
    cards[i]->cardUI.setInitialPosition(glm::vec2(startX + i * stepX, center.y));
    cards[i]->cardUI.setPosition(glm::vec2(startX + i * stepX, center.y));
  }
}

} // namespace entities
} // namespace tema1
