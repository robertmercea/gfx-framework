#include "tema1/sprites/card/card_back/card_back.hpp"
#include "tema1/ui/shape/shape.hpp"
#include "tema1/ui/transform/transform.hpp"

namespace tema1 {
namespace sprites {

CardBack::CardBack() {
    borderMesh = std::shared_ptr<Mesh>(
        ui::shape::createSquare("border", 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)));

    innerMesh = std::shared_ptr<Mesh>(
        ui::shape::createSquare("inner", 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    heartMesh = std::shared_ptr<Mesh>(
        ui::shape::createHeart("heart", 0.03f, glm::vec3(1.0f, 0.0f, 0.0f)));
}

void CardBack::getSpriteProperties(std::vector<sprites::SpriteProperties>& spriteProps, const glm::mat3& modelMatrix) {
    spriteProps.push_back({borderMesh.get(), modelMatrix, 0});

    glm::mat3 innerMatrix = modelMatrix * ui::transform::scale(0.9f, 0.9f);
    spriteProps.push_back({innerMesh.get(), innerMatrix, 1});

    float heartScale = 0.03f;
    float verticalOffset = 2.0f * heartScale;
    glm::mat3 heartMatrix = modelMatrix * ui::transform::translate(0.0f, verticalOffset);
    spriteProps.push_back({heartMesh.get(), heartMatrix, 2});
}

} // namespace sprites
} // namespace tema1
