
#include "tema1/entities/effect/effect_fwd.hpp"
namespace tema1 {
namespace entities {

class CardData {
public:
  int manaCost;
  int attack;
  int health;
  EffectPtr effect;
};

} // namespace entities
} // namespace tema1
