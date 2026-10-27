#pragma once

#include "tema1/entities/card/card.hpp"
#include "tema1/entities/card_view/card_view.hpp"
#include "tema1/entities/hero/hero.hpp"

namespace tema1 {
namespace entities {

class Player {
public:
  // TODO: figure out what to put as params for draw/playCard functions
  void drawCard();
  void playCard();
  void endTurn();

private:
  int mana;

  Hero hero;
  CardView cardView;
};

} // namespace entities
} // namespace tema1

