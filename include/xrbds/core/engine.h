#ifndef XRBDS_CORE_ENGINE_H
#define XRBDS_CORE_ENGINE_H

#include <memory>

#include "graphics/renderer.h"

class MainLoop;
class Renderer;

class Engine {
public:
  virtual ~Engine() = default;

  static std::unique_ptr<Engine> Create();

  // Run the main game loop
  void run();

  // Shutdown the engine
  void shutdown();

private:
  bool isRunning;

  // Internal methods for the game loop
  void processInput();
  void update();

  std::unique_ptr<Renderer> renderer;

  Engine();
};

#endif // XRBDS_CORE_ENGINE_H