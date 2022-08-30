export CC= #absolute path to your gcc-11 or cross gcc-11
export CXX= #absolute path to your g++-11 or cross g++-11
export METER=  #EspMeter, IntelMeter and Ltc2946Meter are  applicable here
cmake .. 
make -j14
