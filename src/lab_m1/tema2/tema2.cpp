#include "tema2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "tema2/primitives/primitives.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace m1;

Tema2::Tema2() {}

Tema2::~Tema2() {}

void Tema2::Init() {
  renderCameraTarget = false;

  camera = new tema2::camera::Camera();
  camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

  {
    Mesh *mesh = new Mesh("box");
    mesh->LoadMesh(
        PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"),
        "box.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  {
    Mesh *mesh = new Mesh("sphere");
    mesh->LoadMesh(
        PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"),
        "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  {
    Mesh *mesh = tema2::primitives::createTriangularPrism("tri", 2, 0.1f, glm::vec3(1,0,0));
    meshes[mesh->GetMeshID()] = mesh;
  }

  {
    Mesh *mesh = tema2::primitives::createParallelepiped("para", 5, 3, 2, glm::vec3(1,0,0));
    meshes[mesh->GetMeshID()] = mesh;
  }

  // TODO(student): After you implement the changing of the projection
  // parameters, remove hardcodings of these parameters
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
  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));

    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
  }

  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
  }

  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
  }

  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, 0.5f, 0));
    RenderMesh(meshes["tri"], shaders["Simple"], modelMatrix);
  }

  {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7, 0.5f, 0));
    RenderMesh(meshes["para"], shaders["Simple"], modelMatrix);
  }

  // Render the camera target. This is useful for understanding where
  // the rotation point is, when moving in third-person camera mode.
  if (renderCameraTarget) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->getTargetPosition());
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
    RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
  }
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

void Tema2::OnKeyPress(int key, int mods) {
}

void Tema2::OnKeyRelease(int key, int mods) {
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
  renderCameraTarget = camera->onMouseMove(window, mouseX, mouseY, deltaX, deltaY);
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema2::OnWindowResize(int width, int height) {}
