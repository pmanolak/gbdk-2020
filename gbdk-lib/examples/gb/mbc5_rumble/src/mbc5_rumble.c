#include <gbdk/platform.h>

void RUMBLE_WITH_DELAY(uint8_t delay)
{
    rRAMB = 0b00001000;
    if(delay != 0)
        for(uint8_t i = 0;i<=delay;i++)
            rRAMB = 0b00000000;
}


void RUMBLE_OFF()
{
    rRAMB = 0b00000000;
}