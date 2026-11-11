#include "tema1/sprites/card/card.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"
#include "tema1/ui/transform/transform.hpp"

namespace tema1 {
namespace sprites {

Card::Card(globals::CardType cardType)
    : Sprite(1.0f * std::sqrt(2.0f), 1.0f * std::sqrt(2.0f)) {
  // width and height are multiplied by sqrt(2), because the corners of the
  // square at on the unit circle, meaning that the distance between them is
  // sqrt(2)
  using namespace ui;
  using CardType = globals::CardType;
  borderMesh = std::shared_ptr<Mesh>(
      ui::shape::createSquare("border", 1.0f, colors::WHITE));

  innerColor = colors::GREEN;
  symbolColor = colors::RED;

  switch (cardType) {
  case CardType::DWARF:
    innerColor = colors::ORANGE;
    symbolColor = colors::RED;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createHeart("heart", 0.35f, symbolColor));
    break;
  case CardType::KNIGHT:
    innerColor = colors::BLACK;
    symbolColor = colors::GOLD;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createCircle("circle", 0.35f, symbolColor));
    break;
  case CardType::MAGE:
    innerColor = colors::PURPLE;
    symbolColor = colors::MANA_BLUE;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createSquare("square", 0.35f, symbolColor));
    break;
  case CardType::WIZARD:
    innerColor = colors::CYAN;
    symbolColor = colors::BLACK;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createTriangle("triangle", 0.35f, symbolColor));
    break;
  case CardType::MINION:
    innerColor = colors::GOLD;
    symbolColor = colors::BLACK;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createTriangle("triangle", 0.35f, symbolColor));
    break;
  case CardType::BACK:
    innerColor = colors::GRAY;
    symbolColor = colors::GRAY;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createTriangle("triangle", 0.35f, symbolColor));
    break;
  case CardType::HERO:
    innerColor = colors::DARK_GRAY;
    symbolColor = colors::MAGENTA;
    symbolMesh = std::shared_ptr<Mesh>(
        ui::shape::createNgon("pentagon", 5, 0, 0.35f, symbolColor));
    break;
  }

  innerMesh =
      std::shared_ptr<Mesh>(ui::shape::createSquare("inner", 1.0f, innerColor));
}

void Card::getSpriteProperties(
    std::vector<sprites::SpriteProperties> &spriteProps,
    const glm::mat3 &modelMatrix,
    const glm::vec3 &borderColor) {

  if (borderMesh) {
    spriteProps.push_back({borderMesh.get(), modelMatrix, 0, borderColor});
  }

  if (innerMesh) {
    glm::mat3 innerMatrix = modelMatrix * ui::transform::scale(0.9f, 0.9f);
    spriteProps.push_back({innerMesh.get(), innerMatrix, 1, this->innerColor});
  }

  if (symbolMesh) {
    glm::mat3 symbolMatrix = modelMatrix * ui::transform::translate(0.0f, 0.0f);
    spriteProps.push_back({symbolMesh.get(), symbolMatrix, 2, this->symbolColor});
  }
}

} // namespace sprites
} // namespace tema1
