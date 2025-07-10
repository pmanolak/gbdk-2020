#include <gbdk/platform.h>
#include <stdint.h>
#define MBC_RUMBLE_BIT_ON   0b00001000u
#define MBC_RUMBLE_BIT_OFF  0b00000000u
#define MBC5_RUMBLE_ON      SWITCH_RAM_MBC5(0 | MBC_RUMBLE_BIT_ON)
#define MBC5_RUMBLE_OFF     SWITCH_RAM_MBC5(0 | MBC_RUMBLE_BIT_OFF)

uint8_t rumble_counter = 0;

void MBC5_RUMBLE_LOW(void)
{
    rumble_counter++;
    if(rumble_counter%4==0)MBC5_RUMBLE_ON;
    else MBC5_RUMBLE_OFF;
}
void MBC5_RUMBLE_MED(void)
{
    rumble_counter++;
    if(rumble_counter%2==0)MBC5_RUMBLE_ON;
    else MBC5_RUMBLE_OFF;
}

void MBC5_RUMBLE_MAX(void)
{
    MBC5_RUMBLE_ON;
}