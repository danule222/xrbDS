/**
 * @file input.h
 * @brief Provides the Input class and related enumerations for handling input
 * states.
 * @copyright 2025 Daniel Ramirez Morilla
 *
 * This header defines the Input class, which provides static methods to query
 * the state of keys (held, pressed, or released) on the system. It also defines
 * the EButton enumeration for representing individual keys.
 *
 * The Input class is designed as a utility class and cannot be instantiated.
 * It maintains internal states for keys and provides methods to update and
 * query these states.
 *
 * Usage:
 * - Call Input::Update() periodically to refresh the key states.
 * - Use Input::IsButtonHeld(), Input::IsButtonDown(), or Input::IsButtonUp() to
 * query the state of specific keys.
 *
 * @author Daniel Ramirez Morilla
 * @date 2025-04-19
 *
 * @note This class is specific to the NDS platform and relies on
 * platform-specific key definitions.
 */

#ifndef XRBDS_INPUT_H
#define XRBDS_INPUT_H

#include "core/types.h"

#include <memory>
#include <nds/input.h>

/**
 * @enum EButton
 * @brief Represents the keys available on the NDS platform.
 *
 * This enumeration defines constants for each key on the NDS system, mapping
 * them to their corresponding platform-specific key codes.
 *
 * The keys include standard buttons such as A, B, X, Y, L, R, directional
 * buttons (UP, DOWN, LEFT, RIGHT), and system buttons (START, SELECT, HINGE).
 *
 * Example usage:
 * @code
 * if (Input::IsButtonDown(EButton::A)) {
 *     // Handle A button press
 * }
 * @endcode
 *
 * @note These key codes are specific to the NDS platform and rely on the
 * platform's key definitions.
 */
enum EButton : u16 {
  A = KEY_A,
  B = KEY_B,
  X = KEY_X,
  Y = KEY_Y,
  L = KEY_L,
  R = KEY_R,
  UP = KEY_UP,
  DOWN = KEY_DOWN,
  LEFT = KEY_LEFT,
  RIGHT = KEY_RIGHT,
  START = KEY_START,
  SELECT = KEY_SELECT,
  HINGE = KEY_HINGE
};

/**
 * @class Input
 * @brief Provides static methods to handle input states for buttons.
 *
 * The Input class is a utility class that allows querying the state of buttons
 * (held, pressed, or released) using static methods. It is not meant to be
 * instantiated.
 */
class Input {
public:
  /**
   * @brief Updates the internal state of the input system.
   *
   * This method should be called periodically to refresh the button states.
   */
  static void Update();

  /**
   * @brief Checks if a specific button is currently being held down.
   * @param button The button to check.
   * @return True if the button is held down, false otherwise.
   */
  static bool IsButtonHeld(EButton button);

  /**
   * @brief Checks if a specific button was pressed in the current update cycle.
   * @param button The button to check.
   * @return True if the button was pressed, false otherwise.
   */
  static bool IsButtonDown(EButton button);

  /**
   * @brief Checks if a specific button was released in the current update
   * cycle.
   * @param button The button to check.
   * @return True if the button was released, false otherwise.
   */
  static bool IsButtonUp(EButton button);

private:
  /**
   * @brief Stores the state of buttons currently being held down.
   */
  static u32 ButtonsHeldState;

  /**
   * @brief Stores the state of buttons pressed in the current update cycle.
   */
  static u32 ButtonsDownState;

  /**
   * @brief Stores the state of buttons released in the current update cycle.
   */
  static u32 ButtonsUpState;

  /**
   * @brief Deleted constructor to prevent instantiation of the Input class.
   */
  Input() = delete;
};

#endif // XRBDS_INPUT_H