# Summary

Meraki provide the source code for u-boot for the Z3 upon request, however they do not provide the cross compilation toolchain.

The default make target will build a Ubuntu 16.04 build environment (GCC5) and then build u-boot according to the instructions from Meraki.

# Building

Run `make` and let Docker take care of the rest. At the end of the build you should have `U-boot.Z3/u-boot.bin` and `U-boot.Z3/u-boot.elf`.
