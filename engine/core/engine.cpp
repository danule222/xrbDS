#include "core/engine.h"

#include <memory>

#include <nds.h>
#include <stdio.h>

#include "input/input.h"

// Main program function
int main(void) {
  // Initialize engine
  std::unique_ptr<Engine> engine = Engine::Create();
  if (!engine)
    exit(1);

  engine->run();

  return 0;
}

std::unique_ptr<Engine> Engine::Create() {
  return std::unique_ptr<Engine>(new Engine());
}

void Engine::run() {
  while (pmMainLoop()) {
    processInput();
    update();
    render();

    swiWaitForVBlank();
  }
}

void Engine::processInput() { input->update(); }

void Engine::update() {
  // Update
}

void Engine::render() { renderer->render(); }

Engine::Engine() {
  // Initialize the graphics renderer
  renderer = Renderer::Create();
  if (!renderer)
    exit(2);

  // Initialize the input system
  input = Input::Create();
  if (!input)
    exit(3);

  // Debug
  consoleDemoInit();
}