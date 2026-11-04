#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"

namespace tema1 {
namespace entities {

enum class RenderMode {
  PLAYER,
  ENEMY,
};

class CardCollection {
public:
  CardPtr drawTopCard();
  void getSpriteProperties(std::vector<sprites::SpriteProperties> &spriteProps);
  void setRenderMode(RenderMode mode);
  void pushCard(const CardPtr card);
  CardVectorPtr getCards();

private:
  void setCardRenderMode(bool showFront);
  CardVector cards;
};

}
}

