#ifndef XRBDS_INPUT_H
#define XRBDS_INPUT_H

#include <memory>

#include <calico/types.h>
#include <nds/input.h>

enum EKey : u16 {
  A = KEY_A,
  B = KEY_B,
  X = KEY_X,
  Y = KEY_Y,
  L = KEY_L,
  R = KEY_R,
  START = KEY_START,
  SELECT = KEY_SELECT,
  EKEY_COUNT
};

class Input {
public:
  virtual ~Input() = default;

  static std::unique_ptr<Input> Create();

  void update();

  bool isKeyHeld(EKey key) const;

  bool isKeyDown(EKey key) const;

  bool isKeyUp(EKey key) const;

private:
  u32 keysHeldState = 0;
  u32 keysDownState = 0;
  u32 keysUpState = 0;

  Input();
};

#endif // XRBDS_INPUT_H