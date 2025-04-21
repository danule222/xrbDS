#include "core/engine.h"

#include <memory>

#include <nds.h>
#include <stdio.h>

#include "input/input.h"
#include "component_manager.h"
#include "object.h"
#include "components/transform.h"
#include "components/mesh_filter.h"
#include "graphics/renderer.h"

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
  // Initialize the main loop
  // - VBlank IRQ
  irqSet(IRQ_VBLANK, Engine::VblankCallback);
  VblankCallback();

  // TEST - Create an entity and add a component
  FEntity entity = ComponentManager::GetInstance()->newEntity();
  Transform transform({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
                      {1.0f, 1.0f, 1.0f});
  ComponentManager::GetInstance()->addComponent(entity, transform);
  MeshFilter meshFilter("example_mesh");
  ComponentManager::GetInstance()->addComponent(entity, meshFilter);

  // TEST - Loop trough selected components
  auto view = ComponentManager::GetInstance()->view<MeshFilter, Transform>();

  for (auto &[entity, mesh, transform] : view) {
    printf("Entity: %d, Mesh: %p, Transform: %p\n", entity, mesh, transform);
  }

  while (pmMainLoop()) {
    processInput();
    update();
  }
}

void Engine::processInput() { Input::Update(); }

void Engine::update() {
  // Update
}

void Engine::render() { Renderer::GetInstance()->render(); }

void Engine::VblankCallback() { Engine::GetInstance()->render(); }

Engine::Engine() {}