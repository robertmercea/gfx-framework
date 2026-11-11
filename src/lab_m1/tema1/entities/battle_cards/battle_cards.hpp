#pragma once

#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/player/player.hpp"
#include "tema1/entities/properties/renderable/renderable.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include "tema1/ui/card_area/card_area.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/entities/hero/hero.hpp"
#include <unordered_map>

namespace tema1 {
namespace entities {

class BattleCards;
using BattleCardsPtr = std::shared_ptr<BattleCards>;

class BattleCards : public Renderable {
public:
  using PlayerType = globals::player::PlayerType;
  std::unordered_map<globals::player::PlayerType, ui::CardArea> cardAreas;
  std::unordered_map<globals::player::PlayerType, CardVector> tanks;

  BattleCards();

  void addCard(const CardPtr card, PlayerType owner);
  void removeCard(const CardPtr card, PlayerType owner);
  void useCard(const CardPtr card, const CardPtr target, PlayerType owner);
  void getSpriteProperties(std::vector<tema1::sprites::SpriteProperties> &spriteProps) override;
  const CardVector& getPlayerCards(PlayerType owner) const;
  HeroPtr getHero(PlayerType owner) const;

private:
  static constexpr float CARD_AREA_WIDTH = 800.0f;
  static constexpr float CARD_AREA_HEIGHT = 100.0f;
  static constexpr float CARD_AREA_BORDER_THICKNESS = 5.0f;
  glm::vec3 CARD_AREA_AI_BG_COLOR = ui::colors::PURPLE;
  glm::vec3 CARD_AREA_HUMAN_BG_COLOR = ui::colors::CYAN;

  std::unordered_map<globals::player::PlayerType, CardVector> playerCards;
  std::unordered_map<globals::player::PlayerType, HeroPtr> heroes;
};

} // namespace entities
} // namespace tema1
