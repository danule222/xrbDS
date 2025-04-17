#include "input/input.h"

#include <nds.h>

Input::Input() {
  // Initialize input system
  scanKeys();
}
void Input::update() {
  // Update key states
  scanKeys();
  keysHeldState = keysHeld();
  keysDownState = keysDown();
  keysUpState = keysUp();
}

bool Input::isKeyHeld(int key) const { return keysHeldState & key; }

bool Input::isKeyDown(int key) const { return keysDownState & key; }

bool Input::isKeyUp(int key) const { return keysUpState & key; }
