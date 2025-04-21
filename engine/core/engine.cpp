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

  // TEST ------------------------

  PtrShr<Node3D> node = NewNode<Node3D>();
  node->getComponent<Transform>()->position = {1.0f, 2.0f, 3.0f};

  FString ahuevo = Utils::File::ReadTextFile("hola.txt");
  iprintf("ahuevo: %s\n", ahuevo.c_str());

  // -----------------------------

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

Engine::Engine() {
  // Initialize nitroFS
  char nitroFSPath[32];
  strcpy(nitroFSPath, "assets");
  char *nitroFSPathptr = nitroFSPath;
  if (!nitroFSInit(&nitroFSPathptr))
    exit(-1);
}