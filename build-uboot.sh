#!/bin/sh

export CROSS_COMPILE=arm-linux-gnueabi-
cd /src && make insect_release_config && make u-boot.elf
