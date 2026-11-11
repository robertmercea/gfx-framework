#pragma once

#include "tema1/entities/battle_cards/battle_cards.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/card_deck/card_deck.hpp"
#include "tema1/entities/player/player.hpp"
#include "tema1/entities/player_hand/player_hand.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/ui/button/button.hpp"
#include "tema1/ui/timer/timer.hpp"
#include <tuple>
#include <unordered_map>
#include <vector>

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
  using PlayerType = globals::player::PlayerType;

  void init(const glm::vec2 &resolution);
  void update(float deltaTime);
  void onMouseMove(float mouseX, float mouseY);
  void onMouseBtnPress(float mouseX, float mouseY);
  void onMouseBtnRelease(float mouseX, float mouseY);
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
  void cardAttack(const CardPtr def, const CardPtr atk, const PlayerType &defP, const PlayerType &atkP);
  void cardCleanup();
  BattleCards &getBattleCards();
  PlayerType getCurrentPlayer();
  PlayerType getEnemyPlayer();
  void switchPlayer();
  PlayerType getCardOwner(const CardPtr card);
  // TODO: split the damned state machine into multiple smaller functions

private:
  static constexpr float HUMAN_HAND_Y_OFFSET = 50.0f;
  static constexpr float AI_HAND_Y_OFFSET = 50.0f;
  static constexpr float HAND_MAX_WIDTH = 800.0f;
  static constexpr float BATTLECARDS_Y_OFFSET = 75.0f;

  GameState state;
  globals::player::PlayerType currentPlayer;
  glm::vec2 windowResolution;

  int currentMana;
  const int MAX_MANA = 10;

  const float TIMER_INIT_VALUE = 60.0f;
  const int GAME_START_DECK_AMOUNT = 25;
  const int GAME_START_PLAYER_HAND_AMOUNT = 5;

  CardPtr draggedCard;
  CardPtr attackingCard;
  CardPtr defendingCard;

  std::vector<std::tuple<PlayerType, CardPtr>> cleanupPool;

  BattleCards battlecards;
  std::unordered_map<globals::player::PlayerType, Player> players;
  std::unordered_map<globals::player::PlayerType, PlayerHand> playerHands;
  std::unordered_map<globals::player::PlayerType, CardDeck> decks;

  ui::Button endTurnBtn;
  ui::Timer timer;

  void updateCardColors();
  void aiTurn();
  GameState checkEndGame();
};

} // namespace entities
} // namespace tema1
