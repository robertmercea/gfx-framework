#include "lifesteal.hpp"

namespace tema1 {
namespace entities {

void LifestealEffect::onAttack(CardPtr def, CardPtr atk,
                               Game &game) {
  const auto &battleCards = game.getBattleCards();
  const auto &currentPlayer = game.getCurrentPlayer();
  const auto &enemyPlayer = game.getEnemyPlayer();
  const auto &alliedHero = battleCards.getHero(currentPlayer);

  const auto damageInflicted =
      std::min(atk->cardData.stats.attack, def->cardData.stats.health);

  alliedHero->cardData.stats.health = std::min(30, alliedHero->cardData.stats.health + damageInflicted);
  alliedHero->cardUI.setHealth(alliedHero->cardData.stats.health);
}

void LifestealEffect::onPlay(CardPtr card, Game &game) {}
void LifestealEffect::onDestroy(CardPtr card, Game &game) {}

} // namespace entities
} // namespace tema1
