# Finge-grained stages
This is used to evaluate each stage in the paper
## Environment

To fully use the perfTool util, please make sure that your kernel has enable the PERF_CONFIG, and you should run in root
mode.

The perfTool is platform-independent, which means it can work in all linux with perf_events. However, since not all perf
envents are supported in some machines, the invalid perf event will result in a 'NA' string in csv or print, but not
block the whole program.

## Energy Meters

So far we support three kinds of Meters: the USB Meter based on ESP32, Ltc2946, and intel's msr meter. You can specify one by set
environment METER to one of following value, and kindly note they should be run under root

* EspMeter, you should also have the esp32_power.ko loaded
* Ltc2946Meter, refer to the Ltc2946 Evaluation kit with IIC, please make sure that your IIC works
* IntelMeter, you should have the cpuid and msr driver loaded

## Dependencies

### Dependencies for long term support

Currently and in the future, we need the `log4cxx` to log, and make sure your compiler can find it in `sysroot`. <br>
In a GNU compiler, there should be <br>

* the xxx.pc
* the xxx.so or xxx.dll
* We have just integrated the header files so they are not neccesary
* In ubuntu 16.04, just type sudo apt-get install -y liblog4cxx-dev

### Dependencies for now

Since this version have not integrated the compression algorithms yet, we should install following dependencies:

* The liblz4:
  `sudo apt-get install liblz4-dev`
* The zlib:
  `sudo apt-get install zlib1g` <br>
  `sudo apt-get install zlib1g.dev` <br>
* Other functions in gbindata (Optional):
  `git clone -b safe https://gitee.com/tonyskyz/gbindata.git` <br>
  `cd gbindata` <br>
  `export CC=gcc` <br>
  `mkdir build && cd build && cmake -DMAKE_LIB=ON ..` <br>
  `sudo make install` <br>

### Special tips for cross-compile

Except gbindata, all dependencies above can be solved by buildroot, please just check and enable them in the
menuconfig. <br>
Visit https://buildroot.org/ for more details. <br>
The README.md in gbindata has offered ways on cross-compile, and it is in the same style as this software

## Compile, cross compile and non-standard compilers

This software requires compilers supporting C++20, a set of gcc and g++ in version 11 is good choice. <br>
The default compiler is `gcc` and `g++` just in your system path, However, you can set envronment varibles `CC`
and `CXX` to set up tool chain other than gcc and g++. Please make sure that they support C++20 <br>
We have provide a template a64build.sh in a64build folder, please fill and run it according to notes <br>

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

