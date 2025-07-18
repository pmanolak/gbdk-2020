#include <gbdk/platform.h>
#include <stdint.h>
#include <stdio.h>
#include "mbc5_rumble.h"

void main(void)
{
    printf("GBDK Rumble Example.\n");
    printf("Press A for a strongRumble.\n");
    printf("Press B for a weak\nRumble.\n");
    while(1) {
        if(joypad() & J_A)
            MBC5_RUMBLE_MAX();
        else if (joypad() & J_B)
            MBC5_RUMBLE_LOW();
        else
            MBC5_RUMBLE_OFF;
        vsync();
    }
}
