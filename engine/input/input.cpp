#include "input/input.h"

#include <nds.h>
#include <stdio.h>

// Static members
u32 Input::ButtonsHeldState = 0;
u32 Input::ButtonsDownState = 0;
u32 Input::ButtonsUpState = 0;

void Input::Update() {
  // Update key states
  scanKeys();
  ButtonsHeldState = keysHeld();
  ButtonsDownState = keysDown();
  ButtonsUpState = keysUp();
}

bool Input::IsButtonHeld(EButton key) { return ButtonsHeldState & key; }

bool Input::IsButtonDown(EButton key) { return ButtonsDownState & key; }

bool Input::IsButtonUp(EButton key) { return ButtonsUpState & key; }
