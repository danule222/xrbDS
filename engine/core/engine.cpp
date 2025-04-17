#include "core/engine.h"

#include <nds.h>
#include <stdio.h>
#include <memory>

// Main program function
int main(void) {
  // Initialize engine
  std::unique_ptr<Engine> engine = Engine::Create();
  if (!engine)
    exit(1);

  engine->run();
  engine->shutdown();

  return 0;
}

std::unique_ptr<Engine> Engine::Create() {
  return std::unique_ptr<Engine>(new Engine());
}

void Engine::run() {
  isRunning = true;

  while (pmMainLoop()) {
    processInput();
    update();
    renderer->render();

    swiWaitForVBlank();
  }
}

void Engine::shutdown() { isRunning = false; }

void Engine::processInput() {
  scanKeys();
  int keys = keysDown();
}

void Engine::update() {
  // Update
}

Engine::Engine() {
  isRunning = false;

  // Debug
  // consoleDemoInit();

  // Initialize the graphics renderer
  renderer = Renderer::Create();
  if (!renderer)
    exit(2);
}