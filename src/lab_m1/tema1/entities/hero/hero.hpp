#pragma once

#include "tema1/entities/card/card.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/globals/sprites/types/types.hpp"
#include <memory>
namespace tema1 {
namespace entities {

class Hero;
using HeroPtr = std::shared_ptr<Hero>;

class Hero : public Card {
public:
  CardData cardData;
  Hero();
};

} // namespace entities
} // namespace tema1

