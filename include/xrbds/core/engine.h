#ifndef XRBDS_CORE_ENGINE_H
#define XRBDS_CORE_ENGINE_H

#include <memory>

#include "graphics/renderer.h"

class Input;
class MainLoop;
class Renderer;

class Engine {
public:
  virtual ~Engine() = default;

  static std::unique_ptr<Engine> Create();

  // Run the main game loop
  void run();

private:
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<Input> input;

  // Internal methods for the game loop
  void processInput();
  void update();
  void render();

  Engine();
};

#endif // XRBDS_CORE_ENGINE_H