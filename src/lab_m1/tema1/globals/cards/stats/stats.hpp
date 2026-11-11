#pragma once

#include "tema1/globals/cards/types/types.hpp"
#include <unordered_map>

namespace tema1 {
namespace globals {
namespace stats {

struct CardStats {
  int manaCost;
  int health;
  int attack;
};

const CardStats WIZARD = {5, 3, 2};
const CardStats DWARF = {3, 2, 1};
const CardStats KNIGHT = {4, 3, 3};
const CardStats MAGE = {2, 2, 2};
const CardStats HERO = {0, 10, 0};
const CardStats MINION = {3, 3, 2};

const std::unordered_map<globals::CardType, CardStats> CARD_PROPERTIES = {
    {CardType::WIZARD, WIZARD},
    {CardType::DWARF, DWARF},
    {CardType::KNIGHT, KNIGHT},
    {CardType::MAGE, MAGE},
    {CardType::HERO, HERO},
    {CardType::MINION, MINION},
};

} // namespace stats
} // namespace globals
} // namespace tema1
