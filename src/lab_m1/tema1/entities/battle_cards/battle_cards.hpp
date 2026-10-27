#pragma once

#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/card_collection/card_collection.hpp"

namespace tema1 {
namespace entities {

class BattleCards;
using BattleCardsPtr = std::shared_ptr<BattleCards>;

class BattleCards {
public:
  void play(const CardPtr card);
  void use(const CardPtr card);

private:
  CardCollection player1Cards;
  CardCollection player2Cards;
};

} // namespace entities
} // namespace tema1
