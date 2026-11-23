#include "tema2.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "tema2/entities/spaceship/cockpit/cockpit.hpp"
#include "tema2/entities/spaceship/spaceship.hpp"
#include "tema2/primitives/primitives.hpp"
#include "tema2/properties/world_object/world_object.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace m1;

Tema2::Tema2() {}

Tema2::~Tema2() {}

void Tema2::Init() {
  RenderByName = [this](const std::string &meshName,
                        const std::string &shaderName,
                        const glm::mat4 &modelMatrix) {
    auto meshIt = meshes.find(meshName);
    auto shaderIt = shaders.find(shaderName);

    if (meshIt == meshes.end() || shaderIt == shaders.end()) {
      return;
    }

    RenderMesh(meshIt->second, shaderIt->second, modelMatrix);
  };

  renderCameraTarget = false;

  camera = new tema2::camera::Camera();
  camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

{
  Mesh *mesh = primitives::createParallelepiped(
      "parallelepiped", 1.0f, 1.0f, 1.0f, glm::vec3(0.75f, 0.75f, 0.82f));
  meshes[mesh->GetMeshID()] = mesh;
}

{
  Mesh *mesh = primitives::createSphere(
      "hemisphere", 1.0f, glm::vec3(0.2f, 0.7f, 0.95f), true);
  meshes[mesh->GetMeshID()] = mesh;
}

{
  Mesh *mesh = primitives::createTriangularPrism(
      "prism", 1.0f, 1.0f, glm::vec3(0.85f, 0.25f, 0.25f));
  meshes[mesh->GetMeshID()] = mesh;
}

{
  Mesh *mesh = primitives::createCone(
      "cone", 1.0f, 1.0f, glm::vec3(1.0f, 0.55f, 0.1f));
  meshes[mesh->GetMeshID()] = mesh;
}

  spaceship = new entities::Spaceship();

  // TODO(student): After you implement the changing of the projection
  // parameters, remove hardcodings of these 3arameters
  projectionMatrix =
      glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Tema2::FrameStart() {
  // Clears the color buffer (using the previously set color) and depth buffer
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::ivec2 resolution = window->GetResolution();
  // Sets the screen area where to draw
  glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds) {
  properties::RenderContext defaultContext;
  defaultContext.parentMatrix = glm::mat4(1.0f);

  spaceship->render(RenderByName, defaultContext);
}

void Tema2::FrameEnd() {
  DrawCoordinateSystem(camera->getViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh *mesh, Shader *shader,
                       const glm::mat4 &modelMatrix) {
  if (!mesh || !shader || !shader->program)
    return;

  // Render an object using the specified shader and the specified position
  shader->Use();
  glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE,
                     glm::value_ptr(camera->getViewMatrix()));
  glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE,
                     glm::value_ptr(projectionMatrix));
  glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE,
                     glm::value_ptr(modelMatrix));

  mesh->Render();
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema2::OnInputUpdate(float deltaTime, int mods) {
  camera->onInputUpdate(window, deltaTime, mods);
}

void Tema2::OnKeyPress(int key, int mods) {}

void Tema2::OnKeyRelease(int key, int mods) {}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
  renderCameraTarget =
      camera->onMouseMove(window, mouseX, mouseY, deltaX, deltaY);
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema2::OnWindowResize(int width, int height) {}
