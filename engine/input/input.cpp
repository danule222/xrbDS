#include "input/input.h"

#include <nds.h>
#include <stdio.h>

Input::Input() {
  // Initialize input system
  scanKeys();
}

std::unique_ptr<Input> Input::Create() {
  return std::unique_ptr<Input>(new Input());
}

void Input::update() {
  // Update key states
  scanKeys();
  keysHeldState = keysHeld();
  keysDownState = keysDown();
  keysUpState = keysUp();
}

bool Input::isKeyHeld(EKey key) const { return keysHeldState & key; }

bool Input::isKeyDown(EKey key) const { return keysDownState & key; }

bool Input::isKeyUp(EKey key) const { return keysUpState & key; }
