#include "tema1/sprites/shape/heart/heart.hpp"
#include "tema1/ui/globals/colors.hpp"
#include "tema1/ui/shape/shape.hpp"

namespace tema1 {
namespace sprites {

Heart::Heart() {
  heartMesh = std::shared_ptr<Mesh>(
      ui::shape::createHeart("heart", DEFAULT_HEART_RADIUS, ui::colors::RED));
}

Heart::Heart(float radius) {
heartMesh = std::shared_ptr<Mesh>(
      ui::shape::createHeart("heart", radius, ui::colors::RED));
}

void Heart::getSpriteProperties(std::vector<SpriteProperties> &spriteProps,
                                const glm::mat3 &modelMatrix) {
  if (heartMesh) {
    SpriteProperties props{};
    props.modelMatrix = modelMatrix;
    props.mesh = heartMesh.get();
    spriteProps.push_back(props);
  } else {
    printf("no heart mesh\n");
  }
}

} // namespace sprites
} // namespace tema1
