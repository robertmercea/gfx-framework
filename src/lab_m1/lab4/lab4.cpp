#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "GLFW/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init()
{
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    // NOTE: bonus
    sunCoords = glm::vec3(0, 0, 0);
    earthCoords = glm::vec3(0, 5, 0);
    moonCoords = glm::vec3(0, 7, 0);

    earthRotation = 0.f;
    moonRotation = 0.f;
}

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::vec3 changedCoords(glm::vec3 coord) {
  return glm::vec3(4 * sin(coord.x), 4 * sin(coord.y), 4 * sin(coord.z));
}

void Lab4::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    const glm::vec3 sunRenderCoords = changedCoords(sunCoords);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(sunRenderCoords.x, sunRenderCoords.y, sunRenderCoords.z);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    // const glm::vec3 earthRenderCoords = changedCoords(earthCoords);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(sunRenderCoords.x, sunRenderCoords.y, sunRenderCoords.z);
    modelMatrix *= transform3D::RotateOZ(earthRotation);
    modelMatrix *= transform3D::Translate(-sunRenderCoords.x, -sunRenderCoords.y, -sunRenderCoords.z);
    modelMatrix *= transform3D::Translate(sunRenderCoords.x, sunRenderCoords.y + 5, sunRenderCoords.z);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    // const glm::vec3 moonRenderCoords = changedCoords(moonCoords);
    modelMatrix = glm::mat4(1);
    // compute earth coords
    modelMatrix *= transform3D::Translate(sunRenderCoords.x, sunRenderCoords.y, sunRenderCoords.z);
    modelMatrix *= transform3D::RotateOZ(earthRotation);
    modelMatrix *= transform3D::Translate(-sunRenderCoords.x, -sunRenderCoords.y, -sunRenderCoords.z);
    modelMatrix *= transform3D::Translate(sunRenderCoords.x, sunRenderCoords.y + 5, sunRenderCoords.z);
    glm::mat4 earthMatrix = modelMatrix;

    // now compute moon coords
    modelMatrix = glm::mat4(1);
    modelMatrix *= earthMatrix;
    modelMatrix *= transform3D::RotateOZ(moonRotation);
    modelMatrix *= glm::inverse(earthMatrix);
    modelMatrix *= transform3D::Translate(0, 3, 0);
    modelMatrix *= earthMatrix;
    modelMatrix *= transform3D::Scale(0.5f, 0.5f, 0.5f);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    DrawCoordinateSystem();
    RenderScene();

    sunCoords.x += 0.5f * deltaTimeSeconds;
    moonRotation += 0.35f * deltaTimeSeconds;
    earthRotation += 0.15f * deltaTimeSeconds;
}

void Lab4::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
    const float DISPLACEMENT = deltaTime * 3;
    // TODO(student): Add transformation logic
    // NOTE: movement
    if (window->KeyHold(GLFW_KEY_W)) {
      translateX += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
      translateX -= DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
      translateZ += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
      translateZ -= DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_R)) {
      translateY += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_F)) {
      translateY -= DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_1)) {
      scaleX += DISPLACEMENT;
      scaleY += DISPLACEMENT;
      scaleZ += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_2)) {
      scaleX -= DISPLACEMENT;
      scaleY -= DISPLACEMENT;
      scaleZ -= DISPLACEMENT;
    }


    // NOTE: rotations
    if (window->KeyHold(GLFW_KEY_3)) {
      angularStepOX += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_4)) {
      angularStepOX -= DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_5)) {
      angularStepOY += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_6)) {
      angularStepOY -= DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_7)) {
      angularStepOZ += DISPLACEMENT;
    }

    if (window->KeyHold(GLFW_KEY_8)) {
      angularStepOZ -= DISPLACEMENT;
    }


}


void Lab4::OnKeyPress(int key, int mods)
{
    const int DISPLACEMENT = 3;
    const int VIEWPORT_SCALING_FACTOR = 2;
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    
    // TODO(student): Add viewport movement and scaling logic
    // NOTE: viewport
    if (key == GLFW_KEY_I) {
      miniViewportArea.y += DISPLACEMENT;
    }

    if (key == GLFW_KEY_K) {
      miniViewportArea.y -= DISPLACEMENT;
    }

    if (key == GLFW_KEY_J) {
      miniViewportArea.x -= DISPLACEMENT;
    }

    if (key == GLFW_KEY_L) {
      miniViewportArea.x += DISPLACEMENT;
    }

    if (key == GLFW_KEY_U) {
      miniViewportArea.width *= VIEWPORT_SCALING_FACTOR;
      miniViewportArea.height *= VIEWPORT_SCALING_FACTOR;
    }

    if (key == GLFW_KEY_O) {
      miniViewportArea.width /= VIEWPORT_SCALING_FACTOR;
      miniViewportArea.height /= VIEWPORT_SCALING_FACTOR;
    }
}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
