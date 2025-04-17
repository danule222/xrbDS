#ifndef XRBDS_CORE_ENGINE_H
#define XRBDS_CORE_ENGINE_H

#include <string>

class Engine {
public:
  Engine();
  ~Engine();

  // Initialize the engine
  bool initialize(const std::string &title, int width, int height);

  // Run the main game loop
  void run();

  // Shutdown the engine
  void shutdown();

private:
  bool isRunning;

  // Internal methods for the game loop
  void processInput();
  void update();
  void render();
};

#endif // XRBDS_CORE_ENGINE_H