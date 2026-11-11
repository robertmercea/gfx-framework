#pragma once

namespace tema1 {
namespace globals {

// card type for card stats
enum class CardType {
  WIZARD,
  KNIGHT,
  MAGE,
  DWARF,
  MINION,
  LEEROY_JENKINS,
  VOIDWALKER,
  HERO,
  BACK,
};

const unsigned int NUM_PLAYABLE_CARDS = 7;

} // namespace globals
} // namespace tema1
