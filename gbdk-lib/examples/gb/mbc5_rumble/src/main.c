#include <gbdk/platform.h>
#include <stdint.h>
#include <stdio.h>
#include "mbc5_rumble.h"

void main(void)
{
    printf("GBDK Rumble Example.\n");
    printf("Press A for a strongRumble.\n");
    printf("Press B for a weak\nRumble.\n");
    // Loop forever
    while(1) {
        if(joypad() & J_A)
            RUMBLE_WITH_DELAY(0);
        else if (joypad() & J_B)
            RUMBLE_WITH_DELAY(100);
        else
            RUMBLE_OFF();
		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
