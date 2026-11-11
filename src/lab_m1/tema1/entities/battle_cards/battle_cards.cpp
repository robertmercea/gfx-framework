#include "battle_cards.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/hero/hero.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/ui/card_area/card_area.hpp"
#include <memory>

namespace tema1 {
namespace entities {

using PlayerType = globals::player::PlayerType;

BattleCards::BattleCards() {
  cardAreas.insert(
      {PlayerType::HUMAN,
       ui::CardArea(CARD_AREA_WIDTH, CARD_AREA_HEIGHT, CARD_AREA_HUMAN_BG_COLOR,
                    CARD_AREA_HUMAN_BG_COLOR, CARD_AREA_BORDER_THICKNESS)});
  cardAreas.insert(
      {PlayerType::AI,
       ui::CardArea(CARD_AREA_WIDTH, CARD_AREA_HEIGHT, CARD_AREA_AI_BG_COLOR,
                    CARD_AREA_AI_BG_COLOR, CARD_AREA_BORDER_THICKNESS)});

  playerCards.insert({PlayerType::HUMAN, CardVector()});
  playerCards.insert({PlayerType::AI, CardVector()});

  heroes.insert({PlayerType::HUMAN, std::make_shared<Hero>()});
  heroes.insert({PlayerType::AI, std::make_shared<Hero>()});
}

void BattleCards::addCard(const CardPtr card, PlayerType owner) {
  playerCards[owner].push_back(card);
}

void BattleCards::useCard(const CardPtr card, const CardPtr target,
                          PlayerType owner) {}

void BattleCards::getSpriteProperties(
    std::vector<tema1::sprites::SpriteProperties> &spriteProps) {

  // render card areas
  for (auto &areaPair : cardAreas) {
    areaPair.second.getSpriteProperties(spriteProps);
  }

  // render player cards
  for (const auto &p : playerCards) {
    auto playerType = p.first;
    const auto &cards = p.second;

    if (cards.empty()) {
      continue;
    }

    auto it = cardAreas.find(playerType);
    if (it == cardAreas.end()) {
      continue;
    }

    ui::CardArea &area = it->second;

    float areaX = area.getPosition().x;
    float areaY = area.getPosition().y;
    float areaW = std::abs(area.getScale().x);
    float areaH = std::abs(area.getScale().y);

    float padding = 20.0f;
    // may be an issue later on, but oh well
    float spacing = cards[0]->cardUI.getScale().x;

    float startX = areaX - (areaW / 2.0f);
    float startY = areaY + (areaH / 2.0f);

    for (size_t i = 0; i < cards.size(); ++i) {
      ui::Card &cardUI = cards[i]->cardUI;

      float cardW = std::abs(cardUI.getScale().x);
      float cardH = std::abs(cardUI.getScale().y);

      float stepX = cardW + spacing;
      float stepY = cardH + spacing;

      int maxPerRow = std::max(
          1, static_cast<int>((areaW - 2.0f * padding + spacing) / stepX));

      int column = i % maxPerRow;
      int row = i / maxPerRow;

      float targetX = startX + padding + (cardW / 2.0f) + (column * stepX);
      float targetY = startY - padding - (cardH / 2.0f) - (row * stepY);

      cardUI.setInitialPosition(glm::vec2(targetX, targetY));
      cardUI.getSpriteProperties(spriteProps);
    }
  }

  // render player heroes
  heroes[PlayerType::HUMAN]->cardUI.setInitialPosition({cardAreas[PlayerType::HUMAN].getPosition().x, cardAreas[PlayerType::HUMAN].getPosition().y - 100.0f});
  heroes[PlayerType::AI]->cardUI.setInitialPosition({cardAreas[PlayerType::AI].getPosition().x, cardAreas[PlayerType::AI].getPosition().y + 100.0f});

  heroes[PlayerType::HUMAN]->cardUI.getSpriteProperties(spriteProps);
  heroes[PlayerType::AI]->cardUI.getSpriteProperties(spriteProps);
}

void BattleCards::removeCard(const CardPtr card, PlayerType owner) {
  auto &vec = playerCards[owner];
  vec.erase(std::remove(vec.begin(), vec.end(), card), vec.end());
}

const CardVector &BattleCards::getPlayerCards(PlayerType owner) const {
  return playerCards.at(owner);
}

HeroPtr BattleCards::getHero(PlayerType owner) const {
  return heroes.at(owner);
}

} // namespace entities
} // namespace tema1
