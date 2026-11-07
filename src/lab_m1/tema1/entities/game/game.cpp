#include "game.hpp"
#include "tema1/entities/card/card.hpp"
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
  timer = TIMER_INIT_VALUE;
  srand(time(NULL));

  players[PlayerType::HUMAN] = Player();
  players[PlayerType::AI] = Player();
  
  players[PlayerType::HUMAN].playerUI.setPosition(glm::vec2(windowResolution.x / 2.0f, 50.0f));
  players[PlayerType::AI].playerUI.setPosition(glm::vec2(windowResolution.x / 2.0f, windowResolution.y - 50.0f));

  endTurnBtn.setSize(120.0f, 50.0f);
  endTurnBtn.setPosition(glm::vec2(windowResolution.x - 100.0f, windowResolution.y / 2.0f));
  endTurnBtn.setColor(ui::colors::ORANGE);

  battlecards = BattleCards();
  battlecards.cardAreas[PlayerType::HUMAN].setPosition(glm::vec2(windowResolution.x / 2.0f, windowResolution.y / 2.0f - 160.0f));
  battlecards.cardAreas[PlayerType::AI].setPosition(glm::vec2(windowResolution.x / 2.0f, windowResolution.y / 2.0f + 160.0f));

  for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
    decks[p] = CardDeck();
    decks[p].setRenderMode(p);
    for (int i = 0; i < GAME_START_DECK_AMOUNT; ++i) {
      auto cardType = static_cast<globals::CardType>(rand() % 4);
      auto spriteType = static_cast<globals::SpriteType>(static_cast<int>(cardType));
      decks[p].pushCard(std::make_shared<Card>(cardType, spriteType));
    }
  }

  for (auto p : {PlayerType::HUMAN, PlayerType::AI}) {
    playerHands[p] = PlayerHand();
    for (int i = 0; i < GAME_START_PLAYER_HAND_AMOUNT; ++i) {
      playerHands[p].pushCard(decks[p].drawTopCard());
    }
  }
  
  playerHands[PlayerType::HUMAN].arrangeCards(glm::vec2(windowResolution.x / 2.0f, 150.0f), 800.0f);
  playerHands[PlayerType::AI].arrangeCards(glm::vec2(windowResolution.x / 2.0f, windowResolution.y - 150.0f), 800.0f);

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
      glm::vec2 center = (currentPlayer == PlayerType::HUMAN) ? 
          glm::vec2(windowResolution.x / 2.0f, 150.0f) : 
          glm::vec2(windowResolution.x / 2.0f, windowResolution.y - 150.0f);
      playerHands[currentPlayer].arrangeCards(center, 800.0f);
      std::cout << "[Event] Player " << (int)currentPlayer << " drew a card.\n";
    }
    
    if (currentPlayer == PlayerType::HUMAN) {
      state = GameState::PLAYER_ATTACK;
      std::cout << "[State] CARD_DRAW -> PLAYER_ATTACK\n";
      timer = TIMER_INIT_VALUE;
    } else {
      state = GameState::PLAYER_DEFEND;
      std::cout << "[State] CARD_DRAW -> PLAYER_DEFEND\n";
    }
  } 
  else if (state == GameState::PLAYER_ATTACK || state == GameState::CARD_DRAG || state == GameState::CARD_USE) {
    timer -= dt;
    if (timer <= 0.0f) {
      std::cout << "[Event] Turn timer expired! Cancelling active actions.\n";
      if (draggedCard) {
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
}

void Game::aiTurn() {
  std::cout << "[AI] AI Turn Started.\n";
  currentPlayer = PlayerType::AI;
  
  if (!decks[PlayerType::AI].getCards().empty()) {
    playerHands[PlayerType::AI].pushCard(decks[PlayerType::AI].drawTopCard());
    playerHands[PlayerType::AI].arrangeCards(glm::vec2(windowResolution.x / 2.0f, windowResolution.y - 150.0f), 800.0f);
    std::cout << "[AI] AI drew a card.\n";
  }

  const auto& aiHand = playerHands[PlayerType::AI].getCards();
  
  for (auto it = aiHand.begin(); it != aiHand.end(); ++it) {
    if ((*it)->cardData.stats.manaCost <= players[PlayerType::AI].mana) {
      players[PlayerType::AI].mana -= (*it)->cardData.stats.manaCost;
      (*it)->playedThisTurn = true;
      battlecards.addCard(*it, PlayerType::AI);
      playerHands[PlayerType::AI].removeCard(*it);
      playerHands[PlayerType::AI].arrangeCards(glm::vec2(windowResolution.x / 2.0f, windowResolution.y - 150.0f), 800.0f);
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
        auto defender = huField[rand() % huField.size()];
        attacker->cardData.stats.health -= defender->cardData.stats.attack;
        defender->cardData.stats.health -= attacker->cardData.stats.attack;
        attacker->hasAttackedThisTurn = true;
        
        std::cout << "[AI] AI attacked a player card! AI Card HP: " << attacker->cardData.stats.health 
                  << " | Player Card HP: " << defender->cardData.stats.health << "\n";
        
        attacker->cardUI.setHealth(attacker->cardData.stats.health);
        defender->cardUI.setHealth(defender->cardData.stats.health);
        
        if (attacker->cardData.stats.health <= 0) {
          battlecards.removeCard(attacker, PlayerType::AI);
          std::cout << "[Event] AI card destroyed in combat.\n";
        }
        if (defender->cardData.stats.health <= 0) {
          battlecards.removeCard(defender, PlayerType::HUMAN);
          std::cout << "[Event] Player card destroyed in combat.\n";
        }
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
        attackingCard->cardData.stats.health -= defendingCard->cardData.stats.attack;
        defendingCard->cardData.stats.health -= attackingCard->cardData.stats.attack;
        attackingCard->hasAttackedThisTurn = true;
        
        std::cout << "[Combat] Player attacked AI card! Player Card HP: " << attackingCard->cardData.stats.health 
                  << " | AI Card HP: " << defendingCard->cardData.stats.health << "\n";
        
        attackingCard->cardUI.setHealth(attackingCard->cardData.stats.health);
        defendingCard->cardUI.setHealth(defendingCard->cardData.stats.health);
        
        if (attackingCard->cardData.stats.health <= 0) {
          battlecards.removeCard(attackingCard, PlayerType::HUMAN);
          std::cout << "[Event] Player card destroyed in combat.\n";
        }
        if (defendingCard->cardData.stats.health <= 0) {
          battlecards.removeCard(defendingCard, PlayerType::AI);
          std::cout << "[Event] AI card destroyed in combat.\n";
        }
        
        attackingCard = nullptr;
        defendingCard = nullptr;
        state = GameState::PLAYER_ATTACK;
        std::cout << "[State] CARD_USE -> PLAYER_ATTACK. Combat resolved.\n";
        return;
      }
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
      playerHands[PlayerType::HUMAN].arrangeCards(glm::vec2(windowResolution.x / 2.0f, 150.0f), 800.0f);
      
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
  players[PlayerType::HUMAN].playerUI.getSpriteProperties(spriteProps, players[PlayerType::HUMAN].health);
  players[PlayerType::AI].playerUI.getSpriteProperties(spriteProps, players[PlayerType::AI].health);
  endTurnBtn.getSpriteProperties(spriteProps);
}

} // namespace entities
} // namespace tema1
