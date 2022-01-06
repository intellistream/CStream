# defconfig for build root

## instructions

* 1.Get a build root under 2021-08-rc2 onwards version
* 2.copy the xxx_defconfig to the configs folder
* 3.make PC_AMP_defconfig && make menuconfig && make -j4
* 4.get the *.img at output/images, and write it to sd card

## known issues

* The gcc-11 may fail to compile u-boot, if that happens, please merge our 'out' folder with your build root, which
  contains the pre-compiled u-boot by gcc-10
