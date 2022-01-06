# defconfig for linux

## preparations

* assume you have already maintained the cross-compile tool chain, this can be done by build root. By our build root
  config file, the tool chain is aarch64-buildroot-linux-gnu-, and you may wish to add it to system path

## instructions

* 1.Get the mainline linux with version 5.10 onwards
* 2.copy the xxx_defconfig to the arch/arm64/configs folder, copy the insmod.sh to the root of linux source file
* 3.export ARCH=arm64 CROSS_COMPILE=aarch64-buildroot-linux-gnu- && make PC_AMP_defconfig && make menuconfig && make -j4
* 4.get the Image at arch/arm64/boot, install the driver and device tree by insmod.sh

