#include "lab_m1/tema1/tema1.hpp"
#include "tema1/sprites/card/card_back/card_back.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/card/card.hpp"

#include <vector>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


tema1::ui::Card *card;
void Tema1::Init()
{
    using namespace tema1;

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    sprites::CardBack cardBackSprite = sprites::CardBack();
    auto cardBack = make_shared<sprites::CardBack>(cardBackSprite);
    auto cardFront = cardBack;

    card = new ui::Card(ui::Card::CardType::KNIGHT, cardFront, cardBack);
    
    card->setPosition(glm::vec2(resolution.x / 2.0f, resolution.y / 2.0f));
    card->showFront();
    card->shake(50000);
}


void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    using namespace tema1;
    std::vector<sprites::SpriteProperties> spriteProps;

    card->update(deltaTimeSeconds);
    card->getSpriteProperties(spriteProps);

    for (const auto & prop : spriteProps) {
        RenderMesh2D(prop.mesh, shaders["VertexColor"], prop.modelMatrix);
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
