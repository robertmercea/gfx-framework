#pragma once

#include "tema1/entities/card_collection/card_collection.hpp"

namespace tema1 {
namespace entities {

class CardView {
public:
  CardVector viewCards();

private:
  const std::shared_ptr<CardCollection> cards;
};

} // namespace entities
} // namespace tema1

