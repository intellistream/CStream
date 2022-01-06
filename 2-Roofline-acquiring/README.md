# RoofLine tool
This tool can test the single-core roofline of your computer, and is portable for linux-based systems
## Environment
To fully use the perfTool util, please make sure that your kernel has enable the PERF_CONFIG, and you should run in root mode.

The perfTool is platform-independent, which means it can work in all linux with perf_events. However, since not all perf envents are supported in some machines, the invalid perf event will result in a 'NA' string in csv or print, but not block the whole program.

However, please be informed that the `instruction` option should be valid
## Energy Meters
So far we support two kinds of Meters: the USB Meter based on ESP32, and intel's msr meter.
You can specify one by set environment METER to one of following value, and kindly note they should be run under root
* EspMeter, you should also have the esp32_power.ko loaded
* IntelMeter, you should have the cpuid and msr driver loaded
### Dependencies for long term support

Currently and in the future, we need the `log4cxx` to log, and make sure your compiler can find it in `sysroot`. <br>
In a GNU compiler, there should be <br>

* the xxx.pc
* the xxx.so or xxx.dll
* We have just integrated the header files so they are not neccesary
* In ubuntu 16.04, just type sudo apt-get install -y liblog4cxx-dev

### Special tips for cross-compile

All dependencies above can be solved by buildroot, please just check and enable them in the
menuconfig. <br>
Visit https://buildroot.org/ for more details. <br>
The README.md in gbindata has offered ways on cross-compile, and it is in the same style as this software

## Compile, cross compile and non-standard compilers

This software requires compilers supporting C++20, a set of gcc and g++ in version 11 is good choice. <br>
The default compiler is `gcc` and `g++` just in your system path, However, you can set envronment varibles `CC`
and `CXX` to set up tool chain other than gcc and g++. Please make sure that they support C++20 <br>
For example, if you want cross-compiler for `aarch64` (e.g., the kiron970, the RK3399 etc.) with the
toolchain `aarch64-buildroot-linux-gnu` try following: <br>
`mkdir arm64_build && cd arm64_build` <br>
`export CC=aarch64-buildroot-linux-gnu-gcc && export CXX=aarch64-buildroot-linux-gnu-g++` <br>
`cmake .. && cmake ..` <br>
`make -j4` <br>
and all you need will be in `aarch64-buildroot-linux-gnu-gcc_build` <br>
Note that the CC and CXX should be full name, so that something like `clang` and `gcc-11` can also be accpted. <br>
In some systems(e.g., the ubuntu16.04), `cmake ..` may lead to inaccurate generate path, so do that twice. And the
programs will be generated under `$ENV{CC}_build` folder. <br>

### Note:

* Visit https://gcc.gnu.org/projects/cxx-status.html for details about how different versions of g++ support the CXX
  standard <br>
* If you have not installed the gcc and g++ in v.11 yet, following are steps for local set-up in ubuntu: <br>
  `sudo add-apt-repository 'deb http://mirrors.kernel.org/ubuntu hirsute main universe' `<br>
  `sudo apt-get update` <br>
  `sudo apt install gcc-11 g++-11` <br>
  `#(optional)` <br>
  `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 11` <br>
  `sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 11` <br>
* The buildroot can also help you build the cross-compiler in satisfying version, but `buildroot-2021.08-rc2` or higher
  version is required.

## Coding style in myself

* Current new namespace(s) : <br>
  ADB, short for aliancedb <br>
  FILE_SP, file support in user benchmark <br>

* Class or struture define :<br>
  By default, Uppercase for the beginning of each word, like `CompressionQuery`. <br>

* Variables or members define :<br>
  By default, use hump style, like `tEnd`, `runTest`, etc.. <br>

* Marco and enumurate define : <br>
  Full upper case, as `ADB::COMP` <br>

* Isolated function : <br>
  hump style, like `writeByteFile` <br>

* Legacy C function for data structures : <br>
  structrue name + _ + hump style function name <br>

## Other support:
We provide the python scripts to quickly draw the result, as well as the testing result on RK3399 (ARM big.LITTLE, 2*A72+4*A53) in the scripts folder
## Usage:
* ./roofLine : will testing the roofline in core0
* ./roofLine [num] :will testing the roofline in core [num] (be sure that it exits)
* ./roofLine [num] scan_freq :will testing the roofline in core [num] (be sure that it exits), trying all the avaliable frequency options on this core
* ./roofLine [num] set_freq [freq](in KHz): will testing the roofline in core [num] (be sure that it exits), trying to set the frequency most close to [freq]
* ./roofLine [num] mem : test the effect of mem address in u32 and u8