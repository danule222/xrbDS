#ifndef XRBDS_INPUT_H
#define XRBDS_INPUT_H

#include <calico/types.h>

class Input {
public:
  Input();

  void update();

  bool isKeyHeld(int key) const;

  bool isKeyDown(int key) const;

  bool isKeyUp(int key) const;

private:
  u32 keysHeldState = 0;
  u32 keysDownState = 0;
  u32 keysUpState = 0;
};

#endif // XRBDS_INPUT_H