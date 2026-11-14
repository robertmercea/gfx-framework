#pragma once

#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/properties/transformable.hpp"
#include <vector>

namespace tema1 {
namespace ui {

class Deck : public Transformable {
public:
  Deck() = default;
  
  void setCardsInDeck(const std::vector<entities::CardPtr> &cards);
  const std::vector<entities::CardPtr> &getCardsInDeck() const;

  void arrangeCards();
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);

  void setPosition(const glm::vec2 &position) override;
  void setScale(const glm::vec2 &scale) override;

private:
  std::vector<entities::CardPtr> cardsInDeck;
  
  static constexpr float OFFSET_X = 4.0f;
  static constexpr float OFFSET_Y = -4.0f;
  static constexpr int MAX_VISIBLE_CARDS = 5;
};

} // namespace ui
} // namespace tema1
