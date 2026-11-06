#include "battle_cards.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/ui/card_area/card_area.hpp"

namespace tema1 {
namespace entities {

using PlayerType = globals::player::PlayerType;

BattleCards::BattleCards() {
  cardAreas.insert(
      {PlayerType::HUMAN,
       ui::CardArea(CARD_AREA_WIDTH, CARD_AREA_HEIGHT, CARD_AREA_HUMAN_BG_COLOR,
                    CARD_AREA_HUMAN_BG_COLOR, CARD_AREA_BORDER_THICKNESS)});
  cardAreas.insert({PlayerType::AI,
      ui::CardArea(CARD_AREA_WIDTH, CARD_AREA_HEIGHT, CARD_AREA_AI_BG_COLOR,
                   CARD_AREA_AI_BG_COLOR, CARD_AREA_BORDER_THICKNESS)});

  playerCards.insert({PlayerType::HUMAN, CardVector()});
  playerCards.insert({PlayerType::AI, CardVector()});
}

void BattleCards::addCard(const CardPtr card, PlayerType owner) {
  playerCards[owner].push_back(card);
}

void BattleCards::useCard(const CardPtr card, PlayerType owner) {}

void BattleCards::getSpriteProperties(
    std::vector<tema1::sprites::SpriteProperties> &spriteProps) {

  for (auto &areaPair : cardAreas) {
    areaPair.second.getSpriteProperties(spriteProps);
  }

  for (const auto &p : playerCards) {
    const auto &cards = p.second;

    for (const auto &card : cards) {
      card->cardUI.getSpriteProperties(spriteProps);
    }
  }
}
} // namespace entities
} // namespace tema1
