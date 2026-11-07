#pragma once

#include "tema1/ui/player/player.hpp"

namespace tema1 {
namespace entities {

class Player {
public:
  int mana = 0;
  int health = 30;
  ui::Player playerUI;
};

} // namespace entities
} // namespace tema1
