#include "tema1/entities/card/card_fwd.hpp"

namespace tema1 {
namespace entities {

enum RenderMode {
  PLAYER,
  ENEMY,
};

class CardCollection {
public:
  CardPtr drawCard();
  void orderCards();
  void render();
  void setRenderMode(RenderMode mode);
  void addCard(const CardPtr card);
  CardVectorPtr getCards();

private:
  CardVector cards;
};

}
}

