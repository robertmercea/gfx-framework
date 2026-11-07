#pragma once

#include "tema1/entities/battle_cards/battle_cards.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/entities/player/player.hpp"
#include "tema1/entities/player_hand/player_hand.hpp"
#include "tema1/entities/card_deck/card_deck.hpp"
#include <unordered_map>

namespace tema1 {
namespace entities {

enum class GameState {
  GAME_INIT,
  TURN_START,
  CARD_DRAW,
  CARD_DRAG,
  CARD_USE,
  PLAYER_ATTACK,
  PLAYER_DEFEND,
  TURN_END,
  GAME_END,
};

class Game {
public:
  void init();
  void update(float);
  void onMouseMove(float, float);
  void onMouseBtnPress(float, float);
  void onMouseBtnRelease(float, float);
private:
  // game state machine
  GameState state;
  globals::player::PlayerType currentPlayer;

  // game logic
  int currentMana;
  const int MAX_MANA = 10;

  // card ui management
  CardPtr draggedCard;
  CardPtr attackingCard, defendingCard;
  // all cards currently in the game
  CardVector gameCards;

  // game entities
  std::unordered_map<globals::player::PlayerType, BattleCards> battlecards;
  std::unordered_map<globals::player::PlayerType, Player> players;
  std::unordered_map<globals::player::PlayerType, PlayerHand> playerHands;
  std::unordered_map<globals::player::PlayerType, CardVector> playerCards;
  // TODO: add "end turn" button
  // TODO: add timer
};

} // namespace entities
} // namespace tema1

