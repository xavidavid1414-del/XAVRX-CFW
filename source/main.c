#include <3ds.h>
#include <stdio.h>

int main(void)
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("\x1b[1;1HXAVRX CFW");
    printf("\x1b[3;1HDevelopment diagnostic");
    printf("\x1b[5;1HThis is a homebrew test app,");
    printf("\x1b[6;1Hnot an installed custom firmware.");
    printf("\x1b[9;1HTarget: New Nintendo 2DS XL");
    printf("\x1b[10;1HBuild: Version 0.1");
    printf("\x1b[13;1HPress START to exit.");

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
