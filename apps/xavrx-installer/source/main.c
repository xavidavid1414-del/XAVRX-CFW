#include <3ds.h>
#include <stdio.h>
#include <string.h>

#define TITLE_LIMIT 256
#define PAGE_SIZE 18

static u64 title_ids[TITLE_LIMIT];
static u32 title_count;
static u32 selected;

static void draw_error(Result result)
{
    consoleClear();
    printf("Xavrx Installer\n");
    printf("------------------------------\n");
    printf("Could not read SD titles.\n\n");
    printf("AM result: 0x%08lX\n", (unsigned long)result);
    printf("\nB: Exit");
}

static void draw_titles(void)
{
    consoleClear();
    printf("Xavrx Installer\n");
    printf("Installed titles on SD\n");
    printf("------------------------------\n");

    if (title_count == 0) {
        printf("\nNo SD titles were reported.\n");
    } else {
        u32 page_start = (selected / PAGE_SIZE) * PAGE_SIZE;
        u32 page_end = page_start + PAGE_SIZE;
        if (page_end > title_count) page_end = title_count;

        printf("Titles: %lu    Selected: %lu\n\n",
               (unsigned long)title_count,
               (unsigned long)(selected + 1));

        for (u32 i = page_start; i < page_end; ++i) {
            printf("%c %08lX%08lX\n",
                   i == selected ? '>' : ' ',
                   (unsigned long)(title_ids[i] >> 32),
                   (unsigned long)(title_ids[i] & 0xFFFFFFFFu));
        }
    }

    printf("\nUP/DOWN: Select   B: Exit\n");
    printf("Read-only preview; no titles changed.\n");
}

int main(void)
{
    Result result;
    bool am_ready = false;

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    result = amInit();
    if (R_FAILED(result)) {
        draw_error(result);
        goto main_loop;
    }
    am_ready = true;

    result = AM_GetTitleCount(MEDIATYPE_SD, &title_count);
    if (R_FAILED(result)) {
        draw_error(result);
        goto main_loop;
    }

    if (title_count > TITLE_LIMIT) title_count = TITLE_LIMIT;

    if (title_count > 0) {
        u32 titles_read = 0;
        result = AM_GetTitleList(&titles_read, MEDIATYPE_SD,
                                 title_count, title_ids);
        if (R_FAILED(result)) {
            draw_error(result);
            goto main_loop;
        }
        title_count = titles_read;
    }

    draw_titles();

main_loop:
    while (aptMainLoop()) {
        hidScanInput();
        u32 down = hidKeysDown();

        if (down & KEY_B) break;

        if (title_count > 0) {
            if ((down & KEY_DOWN) && selected + 1 < title_count) {
                ++selected;
                draw_titles();
            }
            if ((down & KEY_UP) && selected > 0) {
                --selected;
                draw_titles();
            }
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    if (am_ready) amExit();
    gfxExit();
    return 0;
}
