#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/globals/player/player.hpp"

namespace tema1 {
namespace entities {

class CardDeck {
public:
  CardPtr drawTopCard();
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
  void setRenderMode(globals::player::PlayerType mode);
  void pushCard(const CardPtr card);
  CardVectorPtr getCards();

private:
  void setCardRenderMode(bool showFront);
  CardVector cards;
};

}
}

