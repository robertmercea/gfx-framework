#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "tema1/entities/battle_cards/battle_cards.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/entities/player/player.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/timer/timer.hpp"
#include "tema1/entities/properties/effect/effect.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

namespace tema1 {
namespace entities {

using PlayerType = globals::player::PlayerType;

void Game::init(const glm::vec2 &resolution) {
  std::cout << "[Game] Initializing game setup.\n";
  windowResolution = resolution;
  state = GameState::GAME_INIT;
  currentMana = 10;
  timer = ui::Timer(TIMER_INIT_VALUE);
  timer.setPosition(glm::vec2(windowResolution.x - 100.0f, windowResolution.y / 2.0f + 100.0f));
  timer.scale(glm::vec2(50.0f, 50.0f));

  srand(time(NULL));

  players[PlayerType::HUMAN] = Player();
  players[PlayerType::AI] = Player();
  
  endTurnBtn.setSize(120.0f, 50.0f);
  endTurnBtn.setPosition(glm::vec2(windowResolution.x - 100.0f, windowResolution.y / 2.0f));
  endTurnBtn.setColor(ui::colors::ORANGE);

  battlecards = BattleCards();
  battlecards.cardAreas[PlayerType::HUMAN].setPosition(glm::vec2(windowResolution.x / 2.0f, windowResolution.y / 2.0f - BATTLECARDS_Y_OFFSET));
  battlecards.cardAreas[PlayerType::AI].setPosition(glm::vec2(windowResolution.x / 2.0f, windowResolution.y / 2.0f + BATTLECARDS_Y_OFFSET));

  for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
    decks[p] = CardDeck();
    decks[p].setRenderMode(p);
    for (int i = 0; i < GAME_START_DECK_AMOUNT; ++i) {
      auto cardType = static_cast<globals::CardType>(rand() % globals::NUM_PLAYABLE_CARDS);
      // TODO: instantiate solely based on cardType
      auto spriteType = static_cast<globals::SpriteType>(static_cast<int>(cardType));
      decks[p].pushCard(std::make_shared<Card>(cardType, spriteType));
    }
  }

  for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
    playerHands[p] = PlayerHand();
    // TODO: increase GAME_START_DECK_AMOUNT such that it has GAME_START_PLAYER_HAND_AMOUNT extra cards
    for (int i = 0; i < GAME_START_PLAYER_HAND_AMOUNT; ++i) {
      playerHands[p].pushCard(decks[p].drawTopCard());
    }
  }
  playerHands[PlayerType::HUMAN].setCenter(glm::vec2(windowResolution.x / 2.0f, HUMAN_HAND_Y_OFFSET));
  playerHands[PlayerType::HUMAN].setMaxWidth(HAND_MAX_WIDTH);
  playerHands[PlayerType::HUMAN].arrangeCards();

  playerHands[PlayerType::AI].setCenter(glm::vec2(windowResolution.x / 2.0f, windowResolution.y - AI_HAND_Y_OFFSET));
  playerHands[PlayerType::AI].setMaxWidth(HAND_MAX_WIDTH);
  playerHands[PlayerType::AI].arrangeCards();

  players[PlayerType::HUMAN].playerUI.setPosition(glm::vec2(windowResolution.x / 2.0f, 100.0f));
  players[PlayerType::HUMAN].playerUI.setScale(glm::vec2(75.0f, 75.0f));

  players[PlayerType::AI].playerUI.setPosition(glm::vec2(windowResolution.x / 2.0f, windowResolution.y - 100.0f));
  players[PlayerType::AI].playerUI.setScale(glm::vec2(75.0f, 75.0f));


  currentPlayer = PlayerType::HUMAN;
  state = GameState::TURN_START;
  std::cout << "[State] GAME_INIT -> TURN_START\n";
}

void Game::update(float dt) {
  if (state == GameState::GAME_END) return;

  if (state == GameState::TURN_START) {
    currentMana = std::min(MAX_MANA, currentMana + 1);
    players[PlayerType::HUMAN].mana = currentMana;
    players[PlayerType::AI].mana = currentMana;
    
    std::cout << "[State] TURN_START. Global mana incremented to " << currentMana << ".\n";

    for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
      for (auto &c : battlecards.getPlayerCards(p)) {
        c->hasAttackedThisTurn = false;
        c->playedThisTurn = false;
      }
    }
    state = GameState::CARD_DRAW;
  } 
  else if (state == GameState::CARD_DRAW) {
    std::cout << "[State] CARD_DRAW\n";
    if (!decks[currentPlayer].getCards().empty()) { 
      playerHands[currentPlayer].pushCard(decks[currentPlayer].drawTopCard());
      playerHands[currentPlayer].arrangeCards();
      std::cout << "[Event] Player " << (int)currentPlayer << " drew a card.\n";
    }
    
    if (currentPlayer == PlayerType::HUMAN) {
      state = GameState::PLAYER_ATTACK;
      std::cout << "[State] CARD_DRAW -> PLAYER_ATTACK\n";
      timer.reset();
    } else {
      state = GameState::PLAYER_DEFEND;
      std::cout << "[State] CARD_DRAW -> PLAYER_DEFEND\n";
    }
  } 
  else if (state == GameState::PLAYER_ATTACK || state == GameState::CARD_DRAG || state == GameState::CARD_USE) {
    timer.passTime(dt);
    if (timer.isTimeout()) {
      std::cout << "[Event] Turn timer expired! Cancelling active actions.\n";
      if (draggedCard) {
        // TODO: fix this bloody mess (send it back to its default pos)
        draggedCard->cardUI.onMouseBtnRelease(0, 0);
        draggedCard = nullptr;
        std::cout << "[Action] Dragged card snapped back due to timeout.\n";
      }
      attackingCard = nullptr;
      defendingCard = nullptr;
      state = GameState::PLAYER_DEFEND;
      std::cout << "[State] Timeout -> PLAYER_DEFEND\n";
    } else {
      updateCardColors();
    }
  } 
  else if (state == GameState::PLAYER_DEFEND) {
    aiTurn();
  }

  // irrespective of game state, play card animations
  for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
    for (auto &c : battlecards.getPlayerCards(p)) {
      c->cardUI.update(dt);
    }
  }

  for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
    auto hero = battlecards.getHero(p);
    hero->cardUI.update(dt);
  }
}

void Game::aiTurn() {
  if (state == GameState::GAME_END) return;

  std::cout << "[AI] AI Turn Started.\n";
  currentPlayer = PlayerType::AI;
  
  if (!decks[PlayerType::AI].getCards().empty()) {
    playerHands[PlayerType::AI].pushCard(decks[PlayerType::AI].drawTopCard());
    playerHands[PlayerType::AI].arrangeCards();
    std::cout << "[AI] AI drew a card.\n";
  }

  const auto& aiHand = playerHands[PlayerType::AI].getCards();
  
  for (auto it = aiHand.begin(); it != aiHand.end(); ++it) {
    if ((*it)->cardData.stats.manaCost <= players[PlayerType::AI].mana) {
      players[PlayerType::AI].mana -= (*it)->cardData.stats.manaCost;
      (*it)->playedThisTurn = true;
      battlecards.addCard(*it, PlayerType::AI);

      (*it)->cardData.effect->onPlay(*it, *this);
      
      playerHands[PlayerType::AI].removeCard(*it);
      playerHands[PlayerType::AI].arrangeCards();
      std::cout << "[AI] AI played a card to the battleground. Remaining Mana: " << players[PlayerType::AI].mana << "\n";
      break; 
    }
  }

  auto aiField = battlecards.getPlayerCards(PlayerType::AI);
  auto huField = battlecards.getPlayerCards(PlayerType::HUMAN);
  
  if (!aiField.empty()) {
    auto attacker = aiField[rand() % aiField.size()];
    if (!attacker->playedThisTurn && !attacker->hasAttackedThisTurn) {
      
      if (!huField.empty()) {
        // Attack a random card
        auto defender = huField[rand() % huField.size()];
        cardAttack(defender, attacker, PlayerType::HUMAN, PlayerType::AI);
        std::cout << "[AI] AI attacked a player card!\n";
        cardCleanup();
        if (checkEndGame() == GameState::GAME_END) return;
      } else {
        // Attack the human hero directly
        auto humanHero = battlecards.getHero(PlayerType::HUMAN);
        cardAttack(humanHero, attacker, PlayerType::HUMAN, PlayerType::AI);
        std::cout << "[AI] AI attacked the human hero!\n";
        if (checkEndGame() == GameState::GAME_END) return;
      }
      
    }
  }

  currentPlayer = PlayerType::HUMAN;
  state = GameState::TURN_START;
  std::cout << "[State] AI turn ended. -> TURN_START\n";
}

void Game::updateCardColors() {
  for (auto &c : playerHands[PlayerType::HUMAN].getCards()) { 
    if (c->cardData.stats.manaCost <= players[PlayerType::HUMAN].mana) {
      c->cardUI.setBorderColor(ui::colors::BLUE);
    } else {
      c->cardUI.setBorderColor(ui::colors::WHITE);
    }
  }

  for (auto &c : battlecards.getPlayerCards(PlayerType::HUMAN)) {
    if (!c->hasAttackedThisTurn && !c->playedThisTurn) {
      c->cardUI.setBorderColor(ui::colors::WHITE);
    } else {
      c->cardUI.setBorderColor(ui::colors::GRAY);
    }
  }

  if (attackingCard) {
    attackingCard->cardUI.setBorderColor(ui::colors::RED);
  }
}

void Game::onMouseMove(float x, float y) {
  if (state == GameState::CARD_DRAG && draggedCard) {
    draggedCard->cardUI.onMouseMove(x, y);
  }
}

void Game::onMouseBtnPress(float x, float y) {
  if (state == GameState::PLAYER_ATTACK) {
    if (endTurnBtn.contains(x, y)) {
      std::cout << "[Action] Player clicked End Turn button.\n";
      state = GameState::PLAYER_DEFEND;
      return;
    }
    
    for (auto &c : playerHands[PlayerType::HUMAN].getCards()) {
      if (c->cardUI.contains(x, y) && c->cardData.stats.manaCost <= players[PlayerType::HUMAN].mana) {
        draggedCard = c;
        state = GameState::CARD_DRAG;
        std::cout << "[State] PLAYER_ATTACK -> CARD_DRAG. Picked up card from hand.\n";
        c->cardUI.onMouseBtnPress(x, y);
        return;
      }
    }
    
    for (auto &c : battlecards.getPlayerCards(PlayerType::HUMAN)) {
      if (c->cardUI.contains(x, y) && !c->hasAttackedThisTurn && !c->playedThisTurn) {
        attackingCard = c;
        state = GameState::CARD_USE;
        std::cout << "[State] PLAYER_ATTACK -> CARD_USE. Selected attacker on battleground.\n";
        return;
      }
    }
  } 
  else if (state == GameState::CARD_USE) {
    for (auto &c : battlecards.getPlayerCards(PlayerType::AI)) {
      if (c->cardUI.contains(x, y)) {
        defendingCard = c;
        cardAttack(defendingCard, attackingCard, PlayerType::AI, PlayerType::HUMAN);
        
        std::cout << "[Combat] Player attacked AI card! Player Card HP: " << attackingCard->cardData.stats.health 
                  << " | AI Card HP: " << defendingCard->cardData.stats.health << "\n";
        
        attackingCard = nullptr;
        defendingCard = nullptr;
        state = GameState::PLAYER_ATTACK;
        std::cout << "[State] CARD_USE -> PLAYER_ATTACK. Combat resolved.\n";

        cardCleanup();
        (void) checkEndGame();
        return;
      }
    }

    auto aiHero = battlecards.getHero(PlayerType::AI);

    if (aiHero->cardUI.contains(x, y)) {
      defendingCard = aiHero;
      cardAttack(defendingCard, attackingCard, PlayerType::AI, PlayerType::HUMAN);
      std::cout << "[Combat] Player hero attacked AI hero!\n";
      
      attackingCard = nullptr;
      defendingCard = nullptr;
      state = GameState::PLAYER_ATTACK;
      std::cout << "[State] CARD_USE -> PLAYER_ATTACK. Combat resolved.\n";

      (void) checkEndGame();
      return;
    }
    
    for (auto &c : battlecards.getPlayerCards(PlayerType::HUMAN)) {
      if (c->cardUI.contains(x, y) && !c->hasAttackedThisTurn && !c->playedThisTurn) {
        attackingCard = c;
        std::cout << "[Action] Switched selected attacker.\n";
        return;
      }
    }
    
    attackingCard = nullptr;
    state = GameState::PLAYER_ATTACK;
    std::cout << "[State] CARD_USE -> PLAYER_ATTACK. Attack cancelled.\n";
  }
}

void Game::onMouseBtnRelease(float x, float y) {
  if (state == GameState::CARD_DRAG && draggedCard) {
    draggedCard->cardUI.onMouseBtnRelease(x, y);
    
    if (battlecards.cardAreas[PlayerType::HUMAN].contains(x, y)) {
      players[PlayerType::HUMAN].mana -= draggedCard->cardData.stats.manaCost;
      draggedCard->playedThisTurn = true;
      battlecards.addCard(draggedCard, PlayerType::HUMAN);
      playerHands[PlayerType::HUMAN].removeCard(draggedCard);
      playerHands[PlayerType::HUMAN].arrangeCards();

      draggedCard->cardData.effect->onPlay(draggedCard, *this);
      
      std::cout << "[Action] Card successfully played. Remaining Mana: " << players[PlayerType::HUMAN].mana << "\n";
    } else {
      std::cout << "[Action] Card dropped outside valid area. Snapping back to hand.\n";
    }
    
    draggedCard = nullptr;
    state = GameState::PLAYER_ATTACK;
    std::cout << "[State] CARD_DRAG -> PLAYER_ATTACK\n";
  }
}

void Game::getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps) {
  battlecards.getSpriteProperties(spriteProps);
  playerHands[PlayerType::HUMAN].getSpriteProperties(spriteProps);
  playerHands[PlayerType::AI].getSpriteProperties(spriteProps);
  players[PlayerType::HUMAN].playerUI.getSpriteProperties(spriteProps, players[PlayerType::HUMAN].mana);
  players[PlayerType::AI].playerUI.getSpriteProperties(spriteProps, players[PlayerType::AI].mana);
  endTurnBtn.getSpriteProperties(spriteProps);
  timer.getSpriteProperties(spriteProps);
}

void Game::cardAttack(const CardPtr def, const CardPtr atk, const PlayerType &defP, const PlayerType &atkP) {
  const auto damageDealt = atk->cardData.stats.attack;
  const auto resistance = def->cardData.stats.attack;
  const auto humanHero = battlecards.getHero(PlayerType::HUMAN);
  const auto aiHero = battlecards.getHero(PlayerType::AI);

  atk->hasAttackedThisTurn = true;
  atk->cardData.effect->onAttack(def, atk, *this);

  def->cardData.stats.health = std::max(0, def->cardData.stats.health - damageDealt);
  atk->cardData.stats.health = std::max(0, atk->cardData.stats.health - resistance);

  atk->cardUI.setHealth(atk->cardData.stats.health);
  def->cardUI.setHealth(def->cardData.stats.health);

  if (atk->cardData.stats.health <= 0 && atk != humanHero && atk != aiHero) {
    atk->cardData.effect->onDestroy(atk, *this);
    cleanupPool.push_back({atkP, atk});
  }

  if (def->cardData.stats.health <= 0 && def != humanHero && def != aiHero) {
    def->cardData.effect->onDestroy(def, *this);
    cleanupPool.push_back({defP, def});
  }

  if (def->cardData.stats.health > 0) {
    def->cardUI.shake(2);
  }
}

GameState Game::checkEndGame() {
  auto humanHero = battlecards.getHero(PlayerType::HUMAN);
  auto aiHero = battlecards.getHero(PlayerType::AI);

  if (humanHero->cardData.stats.health <= 0) {
    std::cout << "[State] You lost!\n";
    state = GameState::GAME_END;
  }

  if (aiHero->cardData.stats.health <= 0) {
    std::cout << "[State] You won!\n";
    state = GameState::GAME_END;
  }
  
  return state;
}

void Game::cardCleanup() {
  for (const auto &it : cleanupPool) {
    const auto &player = std::get<0>(it);
    const auto &cardptr = std::get<1>(it);

    std::cout << "[Cleanup] Removed card from game!\n";
    battlecards.removeCard(cardptr, player);
  }

  cleanupPool.clear();
}

BattleCards &Game::getBattleCards() {
  return battlecards;
}

PlayerType Game::getCurrentPlayer() {
  return currentPlayer;
}

PlayerType Game::getEnemyPlayer() {
  return currentPlayer == PlayerType::HUMAN ? PlayerType::AI : PlayerType::HUMAN;
}

void Game::switchPlayer() {
  currentPlayer = getEnemyPlayer();
}

} // namespace entities
} // namespace tema1
