# GBDK example for using the Rumble motor on the Game Boy MBC5 Cartridge
This example demonstrates using the Rumble motor that can be on MBC5 cartridges
The Rumble motor was infamously used in Pokemon Pinball

# Makefile MBC
You need to use one of the following MBCs in the Makefile:
0x1C: ROM+MBC5+RUMBLE
0x1D: ROM+MBC5+RUMBLE+SRAM
0x1E: ROM+MBC5+RUMBLE+SRAM+BATT
In this example the last one is used. You can change it in the LCCFLAGS

# Emulators
Not every emulator supports Rumble, and most of the ones that do only work
when you plug a controller.