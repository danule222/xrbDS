#include "input/input.h"

#include <nds.h>
#include <stdio.h>

// Static members
u32 Input::KeysHeldState = 0;
u32 Input::KeysDownState = 0;
u32 Input::KeysUpState = 0;

void Input::Update() {
  // Update key states
  scanKeys();
  KeysHeldState = keysHeld();
  KeysDownState = keysDown();
  KeysUpState = keysUp();
}

bool Input::IsKeyHeld(EKey key) { return KeysHeldState & key; }

bool Input::IsKeyDown(EKey key) { return KeysDownState & key; }

bool Input::IsKeyUp(EKey key) { return KeysUpState & key; }
