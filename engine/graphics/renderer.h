/**
 * @file renderer.h
 * @brief Header file for the Renderer class.
 * @copyright 2025 Daniel Ramirez Morilla
 *
 * This file contains the declaration of the Renderer class, which serves as
 * a base class for rendering operations. The Renderer class provides an
 * interface for managing frames, clearing the screen, and drawing objects.
 *
 * The class follows the singleton design pattern, ensuring that only one
 * instance of the Renderer exists throughout the application. It includes
 * methods for rendering frames, preparing and finalizing the rendering
 * process, and drawing graphical objects such as cubes.
 *
 * Usage:
 * - Use Renderer::GetInstance() to retrieve the singleton instance.
 * - Call render() to handle the rendering process.
 *
 * @author Daniel Ramirez Morilla
 * @date 2025-04-19
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

/**
 * @class Renderer
 * @brief A base class for rendering operations.
 *
 * The Renderer class provides an interface for rendering graphics, including
 * methods for managing frames, clearing the screen, and drawing objects.
 */
class Renderer {
public:
  static float pos;

  /**
   * @brief Virtual destructor for the Renderer class.
   *
   * Ensures proper cleanup of derived classes.
   */
  virtual ~Renderer() = default;

  /**
   * @brief Retrieve the singleton instance of the Engine.
   *
   * @return A unique pointer to a Renderer instance.
   */
  static std::unique_ptr<Renderer> &GetInstance();

  /**
   * @brief Renders the current frame.
   *
   * This method handles the rendering process, including frame management
   * and drawing operations.
   */
  void render();

private:
  /**
   * @brief Prepares the renderer for a new frame.
   *
   * This method is called at the beginning of the rendering process.
   */
  void beginFrame();

  /**
   * @brief Finalizes the rendering of the current frame.
   *
   * This method is called at the end of the rendering process.
   */
  void endFrame();

  /**
   * @brief Clears the screen to prepare for rendering.
   *
   * This method resets the screen to a default state, typically clearing
   * any previous drawings.
   */
  void clearScreen();

  /**
   * @brief Draws a cube of the specified size.
   *
   * @param size The size of the cube to be drawn.
   */
  void drawCube(float size);

  static std::unique_ptr<Renderer> Instance;

  /**
   * @brief Constructor for the Renderer class.
   *
   * The constructor is private to enforce the use of the Create() factory
   * method.
   */
  Renderer();
};

#endif // RENDERER_H