#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/properties/renderable/renderable.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/card_area/card_area.hpp"

namespace tema1 {
namespace entities {

class PlayerHand : public Renderable {
public:
  PlayerHand() = default;

  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
  void showCards(bool show);
  void pushCard(const CardPtr card);
  void removeCard(const CardPtr card);
  void arrangeCards();
  const CardVector& getCards() const;

  float getMaxWidth() const;
  void setMaxWidth(float);

  void setCenter(glm::vec2);
  glm::vec2 getCenter() const;

private:
  glm::vec2 center;
  float maxWidth;
  CardVector cards;
  ui::CardArea cardArea;
};

}
}

