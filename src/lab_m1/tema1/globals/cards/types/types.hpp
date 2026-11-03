#pragma once

namespace tema1 {
namespace globals {

// card type for card stats
enum class CardType {
  WIZARD,
  KNIGHT,
  MAGE,
  DWARF,
  BACK,
};

// this will bite me later on, wont it?

// type used as key to fetch sprites from the global sprite manager
enum class SpriteType {
  WIZARD,
  KNIGHT,
  MAGE,
  DWARF,
  BACK,
};

} // namespace globals
} // namespace tema1
