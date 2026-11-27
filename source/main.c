#include <3ds.h>
#include <stdio.h>
#include "xavrx/core.h"

int main(void)
{
    XavrxCoreState state = XAVRX_STATE_COLD;

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("\\x1b[1;1HXAVRX CFW");
    printf("\\x1b[3;1HCore startup diagnostic");
    printf("\\x1b[5;1HNew Nintendo 2DS XL");
    printf("\\x1b[7;1HCore state: ");

    if (xavrx_core_transition(state, XAVRX_STATE_VALIDATING)) {
        state = XAVRX_STATE_VALIDATING;
    }

    if (state == XAVRX_STATE_VALIDATING &&
        xavrx_core_transition(state, XAVRX_STATE_READY)) {
        state = XAVRX_STATE_READY;
    }

    printf("%s", state == XAVRX_STATE_READY ? "READY" : "FAILED");
    printf("\\x1b[10;1HUser-mode diagnostic only.");
    printf("\\x1b[12;1HNot installed custom firmware.");
    printf("\\x1b[15;1HPress START to exit.");

    while (aptMainLoop()) {
        hidScanInput();
        if (hidKeysDown() & KEY_START) {
            break;
        }
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
