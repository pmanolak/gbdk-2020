#include <gbdk/platform.h>
#include <stdint.h>
#ifndef MBC5_RUMBLE_H_
#define MBC5_RUMBLE_H_
#define MBC_RUMBLE_BIT_ON   0b00001000u
#define MBC_RUMBLE_BIT_OFF  0b00000000u
#define MBC5_RUMBLE_ON      SWITCH_RAM_MBC5(0 | MBC_RUMBLE_BIT_ON)
#define MBC5_RUMBLE_OFF     SWITCH_RAM_MBC5(0 | MBC_RUMBLE_BIT_OFF)
void MBC5_RUMBLE_LOW(void);
void MBC5_RUMBLE_MED(void);
void MBC5_RUMBLE_MAX(void);
#endif