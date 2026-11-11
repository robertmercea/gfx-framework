#include "charge.hpp"

namespace tema1 {
namespace entities {

void ChargeEffect::onAttack(CardPtr def, CardPtr atk, Game &game) {}

void ChargeEffect::onPlay(CardPtr card, Game &game) {
  // allows the card to be used in the same turn it is played
  card->playedThisTurn = false;
}

void ChargeEffect::onDestroy(CardPtr card, Game &game) {}

} // namespace entities
} // namespace tema1
