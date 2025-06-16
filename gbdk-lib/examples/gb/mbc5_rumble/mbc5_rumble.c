#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#define RUMBLE_ON 0b00001000
#define RUMBLE_OFF 0b00000000

void main(void)
{
    printf("Press A to Rumble!");
    // Loop forever
    while(1) {

        if(joypad() & J_A)
		    SWITCH_RAM_MBC5(2 | RUMBLE_ON); // switch to bank 2 and enable rumble
        else
            SWITCH_RAM_MBC5(0 | RUMBLE_OFF); // switch to bank 0 and disable rumble
		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
