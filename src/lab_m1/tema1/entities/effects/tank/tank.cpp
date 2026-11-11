#include "tank.hpp"

namespace tema1 {
namespace entities {

void TankEffect::onAttack(CardPtr def, CardPtr atk, Game &game) {}

void TankEffect::onPlay(CardPtr card, Game &game) {
  auto &battleCards = game.getBattleCards();
  const auto owner = game.getCardOwner(card);
  battleCards.tanks[owner].push_back(card);
}

void TankEffect::onDestroy(CardPtr card, Game &game) {
  auto &battleCards = game.getBattleCards();
  const auto owner = game.getCardOwner(card);
  auto &tankList = battleCards.tanks[owner];
  tankList.erase(std::remove(tankList.begin(), tankList.end(), card), tankList.end());
}

} // namespace entities
} // namespace tema1
