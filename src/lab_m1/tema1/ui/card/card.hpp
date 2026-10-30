#pragma once

#include "glm/ext/vector_float2.hpp"

namespace tema1 {
namespace ui {

class CardFront {

};

class CardBack {

};

class Card {
public:
  void render();

private:
  glm::vec2 scale;
  glm::vec2 rotation;
  glm::vec2 position;
};

} // namespace ui
} // namespace tema1
