#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/entities/properties/renderable/renderable.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/ui/card/card.hpp"

namespace tema1 {
namespace entities {

class PlayerHand : public Renderable {
public:
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
  void showCards(bool show);
  void pushCard(const CardPtr card);
  void removeCard(const CardPtr card);
  void arrangeCards();
  CardVectorPtr getCards();

private:
  CardVector cards;
  ui::Card cardArea;
};

}
}

