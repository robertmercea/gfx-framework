#include "tank.hpp"

namespace tema1 {
namespace entities {

void TankEffect::onAttack(CardPtr def, CardPtr atk, Game &game) {}

void TankEffect::onPlay(CardPtr card, Game &game) {
  auto &battleCards = game.getBattleCards();
  const auto owner = game.getCardOwner(card);
  battleCards.tanksPresent[owner]++;
}

void TankEffect::onDestroy(CardPtr card, Game &game) {
  auto &battleCards = game.getBattleCards();
  const auto owner = game.getCardOwner(card);
  battleCards.tanksPresent[owner]--;
}

} // namespace entities
} // namespace tema1
