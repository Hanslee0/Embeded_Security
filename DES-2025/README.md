## Clone the project as follow:
```
git clone --recurse-submodules https://github.com/jwseo-dku/DES-2025.git
```

## Get Arm toolchain
 
Get the toolchain from `https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads`.
Tested using `gcc-arm-none-eabi-8-2018-q4-major`.

```
wget "https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2019q3/RC1.1/gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2?revision=c34d758a-be0c-476e-a2de-af8c6e16a8a2?product=GNU%20Arm%20Embedded%20Toolchain,64-bit,,Linux,8-2019-q3-update" -O gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2

# Extract the archive
tar xvf gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2
```

## Build and start

- Update path to toolchain, CMSIS and Qemu in the Makefile.
- Compile using `make` and start with `make run`. Note: You might need to adjust
  `CMSIS_PATH`, `QEMU_PATH` and `TOOLCHAIN_PATH` if they are not at the same
  place.
- Debug using `make gdbserver` and (in another terminal) `make gdb`.


