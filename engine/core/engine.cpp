#include "core/engine.h"

#include <memory>

#include <nds.h>
#include <filesystem.h>

#include "input/input.h"
#include "component_manager.h"
#include "components/transform.h"
#include "components/mesh_filter.h"
#include "graphics/renderer.h"
#include "scene/3d/node_3d.h"
#include "utils/file.h"
#include "scene/3d/mesh_instance_3d.h"

/////////////////////////////////////////////////////////
// Main function
/////////////////////////////////////////////////////////

int main(void) {
  // Initialize engine
  PtrUnq<Engine> &engine = Engine::GetInstance();
  if (!engine)
    exit(1);

  // Main loop
  engine->run();

  return 0;
}

/////////////////////////////////////////////////////////

PtrUnq<Engine> Engine::Instance;

Engine::~Engine() { irqSet(IRQ_VBLANK, nullptr); }

PtrUnq<Engine> &Engine::GetInstance() {
  if (!Instance)
    Instance = PtrUnq<Engine>(new Engine());

  return Instance;
}

void Engine::run() {
  Renderer::GetInstance();

  // TEST ------------------------
  // Create a MeshInstance3D
  PtrShr<MeshInstance3D> meshInstance =
      NewNode<MeshInstance3D>("meshes/mococo/mococo.obj");

  // PtrShr<MeshInstance3D> meshIPnstance =
  //     NewNode<MeshInstance3D>("meshes/cube/cube-tex.obj");

  // PtrShr<MeshInstance3D> meshInstance =
  //     NewNode<MeshInstance3D>("meshes/quad/quad.obj");

  // -----------------------------

  while (pmMainLoop()) {
    processInput();
    update();
    render();
  }
}

void Engine::processInput() { Input::Update(); }

void Engine::update() {
  // Update
  if (Input::IsButtonDown(EButton::A)) {
    iprintf("A button pressed\n");
  }
}

void Engine::render() {
  if (!ComponentManager::GetInstance())
    return;
  PtrUnq<Renderer> &renderer = Renderer::GetInstance();

  renderer->beginFrame();

  auto view = ComponentManager::GetInstance()->view<Transform, MeshFilter>();
  for (auto &[entity, transform, meshFilter] : view) {
    renderer->render(*transform, *meshFilter);
  }

  renderer->endFrame();

  swiWaitForVBlank();
}

Engine::Engine() {
  // Initialize nitroFS
  char nitroFSPath[] = {"assets"};
  char *nitroFSPathptr = nitroFSPath;
  if (!nitroFSInit(&nitroFSPathptr))
    exit(-1);
}