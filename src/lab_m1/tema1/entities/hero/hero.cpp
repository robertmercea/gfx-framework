#include "hero.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/globals/sprites/types/types.hpp"

namespace tema1 {
namespace entities {

Hero::Hero()
    : Card(globals::CardType::HERO, globals::SpriteType::HERO) {}

} // namespace entities
} // namespace tema1
