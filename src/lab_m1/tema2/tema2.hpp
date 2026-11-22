
#pragma once

#include "components/simple_scene.h"
#include "tema2/camera/camera.hpp"
#include "tema2/entities/spaceship/cockpit/cockpit.hpp"
#include "tema2/properties/renderable/renderable.hpp"

namespace m1 {
using namespace tema2;

class Tema2 : public gfxc::SimpleScene {
public:
  Tema2();
  ~Tema2();

  void Init() override;

private:
  void FrameStart() override;
  void Update(float deltaTimeSeconds) override;
  void FrameEnd() override;

  void RenderMesh(Mesh *mesh, Shader *shader,
                  const glm::mat4 &modelMatrix) override;

  void OnInputUpdate(float deltaTime, int mods) override;
  void OnKeyPress(int key, int mods) override;
  void OnKeyRelease(int key, int mods) override;
  void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
  void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
  void OnWindowResize(int width, int height) override;

protected:
  tema2::camera::Camera *camera;
  glm::mat4 projectionMatrix;
  bool renderCameraTarget;

  entities::Cockpit *cockpit;
  properties::RenderFunction RenderByName;

};
} // namespace m1
