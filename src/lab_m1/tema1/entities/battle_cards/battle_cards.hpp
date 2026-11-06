#pragma once

#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/properties/renderable/renderable.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/ui/card_area/card_area.hpp"
#include "tema1/ui/globals/colors.hpp"
#include <unordered_map>

namespace tema1 {
namespace entities {

class BattleCards;
using BattleCardsPtr = std::shared_ptr<BattleCards>;

class BattleCards : public Renderable {
public:
  using PlayerType = globals::player::PlayerType;
  std::unordered_map<globals::player::PlayerType, ui::CardArea> cardAreas;

  BattleCards();

  // TODO: add onCardDestroy() handler
  void addCard(const CardPtr card, PlayerType owner);
  void useCard(const CardPtr card, PlayerType owner);
  void getSpriteProperties(std::vector<tema1::sprites::SpriteProperties> &spriteProps) override;

private:
  const float CARD_AREA_WIDTH = 500.0f;
  const float CARD_AREA_HEIGHT = 300.0f;
  const float CARD_AREA_BORDER_THICKNESS = 5.0f;
  const glm::vec3 CARD_AREA_AI_BG_COLOR = ui::colors::PURPLE;
  const glm::vec3 CARD_AREA_HUMAN_BG_COLOR = ui::colors::CYAN;

  std::unordered_map<globals::player::PlayerType, CardVector> playerCards;
  // std::unordered_map<PlayerType, ui::CardArea> cardAreas;
};

} // namespace entities
} // namespace tema1
