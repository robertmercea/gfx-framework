#include "arrow.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"
#include "tema1/ui/transform/transform.hpp"

namespace tema1 {
namespace sprites {

Arrow::Arrow() : Sprite(HEAD_WIDTH, BODY_HEIGHT + sqrt(6.75) / 3 * HEAD_WIDTH) {
  arrowBody = std::shared_ptr<Mesh>(ui::shape::createSquare("rectangle", BODY_WIDTH, ui::colors::RED));
  arrowHead = std::shared_ptr<Mesh>(ui::shape::createTriangle("rectangle", HEAD_WIDTH, ui::colors::RED));
}

void Arrow::getSpriteProperties(
    std::vector<sprites::SpriteProperties> &spriteProps,
    const glm::mat3 &modelMatrix,
    const glm::vec3 &color) {

  const auto bodyMatrix = modelMatrix * ui::transform::scale(BODY_WIDTH, BODY_HEIGHT);
  spriteProps.push_back({arrowBody.get(), bodyMatrix, 0, color});

  const auto arrowMatrix = modelMatrix * ui::transform::translate(0, (BODY_HEIGHT / 2.0f) + (sqrt(6.75) / 9. * HEAD_WIDTH));
  spriteProps.push_back({arrowHead.get(), arrowMatrix, 0, color});
}

}
}
