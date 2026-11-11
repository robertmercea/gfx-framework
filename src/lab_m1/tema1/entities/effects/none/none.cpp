#include "none.hpp"

namespace tema1 {
namespace entities {

void NoneEffect::onAttack(CardPtr def, CardPtr atk, Game &game) {}
void NoneEffect::onPlay(CardPtr card, Game &game) {}
void NoneEffect::onDestroy(CardPtr card, Game &game) {}

} // namespace entities
} // namespace tema1
