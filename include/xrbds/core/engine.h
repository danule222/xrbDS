/**
 * @file engine.h
 * @brief Header file for the core Engine class, which manages the game loop
 *        and subsystems.
 * @copyright 2025 Daniel Ramirez Morilla
 *
 * This file defines the Engine class, a singleton responsible for handling
 * the main game loop, input processing, game state updates, and rendering.
 * It also includes the declaration of the VblankCallback function for
 * vertical blanking interval handling.
 *
 * The Engine class is designed to be the central component of the game
 * framework, coordinating various subsystems such as input, rendering, and
 * game logic.
 *
 * @author Daniel Ramirez Morilla
 * @date 2025-04-19
 */

#ifndef XRBDS_CORE_ENGINE_H
#define XRBDS_CORE_ENGINE_H

#include <memory>

#include "graphics/renderer.h"

class Input;
class MainLoop;
class Renderer;

/**
 * @class Engine
 * @brief Core engine class responsible for managing the game loop and
 * subsystems.
 */
class Engine {
public:
  /**
   * @brief Virtual destructor for proper cleanup in derived classes.
   */
  virtual ~Engine();

  /**
   * @brief Retrieve the singleton instance of the Engine.
   * @return A reference to the unique pointer holding the Engine instance.
   */
  static std::unique_ptr<Engine> &GetInstance();

  /**
   * @brief Run the main game loop.
   */
  void run();

private:
  /**
   * @brief Singleton instance of the Engine.
   */
  static std::unique_ptr<Engine> Instance;

  /**
   * @brief Callback function for vertical blanking interval.
   */
  static void VblankCallback();

  /**
   * @brief Process input events.
   */
  void processInput();

  /**
   * @brief Update the game state.
   */
  void update();

  /**
   * @brief Render the current frame.
   */
  void render();

  /**
   * @brief Private constructor to enforce the singleton pattern.
   */
  Engine();
};

#endif // XRBDS_CORE_ENGINE_H