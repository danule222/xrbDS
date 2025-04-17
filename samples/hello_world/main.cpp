#include <nds.h>
#include <stdio.h>

#include "core/engine.h"

static volatile int frame = 0;

static void Vblank() { frame++; }

int main(void) {
  touchPosition touchXY;

  irqSet(IRQ_VBLANK, Vblank);

  consoleDemoInit();

  iprintf("\x1b[4;7HxrbDS Hello World\n");

  while (pmMainLoop()) {
    swiWaitForVBlank();
    scanKeys();
    int keys = keysDown();
    if (keys & KEY_START)
      break;

    touchRead(&touchXY);

    // print at using ansi escape sequence \x1b[line;columnH
    iprintf("\x1b[10;0HFrame = %d", frame);
    iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
    iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);
  }

  return 0;
}
