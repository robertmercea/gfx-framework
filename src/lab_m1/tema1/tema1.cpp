#include "lab_m1/tema1/tema1.hpp"
#include "tema1/entities/battle_cards/battle_cards.hpp"
#include "tema1/entities/card/card.hpp"
#include "tema1/entities/card/card_fwd.hpp"
#include "tema1/globals/cards/types/types.hpp"
#include "tema1/globals/player/player.hpp"
#include "tema1/sprites/properties/sprite/sprite.hpp"
#include "tema1/ui/card/card.hpp"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


tema1::entities::BattleCards *battlecards;

Tema1::~Tema1()
{
}


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

    float centerX = resolution.x / 2.0f;
    float centerY = resolution.y / 2.0f;
    float yOffset = 250.0f;
    float xOffset = 160.0f;

    battlecards = new entities::BattleCards();

    // Set the positions for the two card areas.
    battlecards->cardAreas[globals::player::PlayerType::HUMAN].setPosition(glm::vec2(centerX, centerY - yOffset));
    battlecards->cardAreas[globals::player::PlayerType::AI].setPosition(glm::vec2(centerX, centerY + yOffset));

    // Make 15 cards for the HUMAN player.
    for (int i = 0; i < 15; ++i) {
        // Cycle through WIZARD (0), KNIGHT (1), MAGE (2), and DWARF (3).
        auto cardType = static_cast<globals::CardType>(i % 4);
        auto spriteType = static_cast<globals::SpriteType>(i % 4);
        
        auto humanCard = std::make_shared<entities::Card>(cardType, spriteType);
        battlecards->addCard(humanCard, globals::player::PlayerType::HUMAN);
    }

    // Make 15 cards for the AI player.
    for (int i = 0; i < 15; ++i) {
        // Add an offset so the AI gets a different sequence of cards.
        auto cardType = static_cast<globals::CardType>((i + 2) % 4);
        auto spriteType = static_cast<globals::SpriteType>((i + 2) % 4);
        
        auto aiCard = std::make_shared<entities::Card>(cardType, spriteType);
        battlecards->addCard(aiCard, globals::player::PlayerType::AI);
    }
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

    battlecards->getSpriteProperties(spriteProps);

    for (const auto &prop : spriteProps) {
        RenderMesh2D(prop.mesh, prop.modelMatrix, prop.color);
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
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

glm::ivec2 Tema1::MouseToViewportCoords(int mouseX, int mouseY) {
    glm::ivec2 scaledRes = window->GetResolution(false);
    glm::ivec2 unscaledRes = window->GetResolution(true);

    // transform mouse coords from mouse origin to mesh origin
    float scaleX = (float)scaledRes.x / (float)unscaledRes.x;
    float scaleY = (float)scaledRes.y / (float)unscaledRes.y;

    float mouseWorldX = (float)mouseX * scaleX;
    float mouseWorldY = (float)scaledRes.y - ((float)mouseY * scaleY);

    glm::ivec2 worldCoords = {mouseWorldX, mouseWorldY};

    return worldCoords;
}
