# dataset tool for micro

## Function

This program can generate the micro data with varying characteristics

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



