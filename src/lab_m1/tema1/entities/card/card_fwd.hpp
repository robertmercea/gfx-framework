#pragma once

#include <memory>
#include <vector>

namespace tema1 {
namespace entities {

class Card;
using CardPtr = std::shared_ptr<Card>;
using CardVector = std::vector<CardPtr>;
using CardVectorPtr = std::shared_ptr<CardVector>;

} // namespace entities
} // namespace tema1
