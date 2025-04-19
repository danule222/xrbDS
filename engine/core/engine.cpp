#include "core/engine.h"

#include <memory>

#include <nds.h>
#include <stdio.h>

#include "input/input.h"

/////////////////////////////////////////////////////////
// Main function
/////////////////////////////////////////////////////////

int main(void) {
  // Initialize engine
  std::unique_ptr<Engine> &engine = Engine::GetInstance();
  if (!engine)
    exit(1);

  engine->run();

  return 0;
}

/////////////////////////////////////////////////////////

std::unique_ptr<Engine> Engine::Instance;

Engine::~Engine() { irqSet(IRQ_VBLANK, nullptr); }

std::unique_ptr<Engine> &Engine::GetInstance() {
  if (!Instance)
    Instance = std::unique_ptr<Engine>(new Engine());

  return Instance;
}

void Engine::run() {
  // Initialize the main loop
  irqSet(IRQ_VBLANK, Engine::VblankCallback);

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