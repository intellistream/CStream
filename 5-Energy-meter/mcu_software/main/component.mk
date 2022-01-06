#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
COMPONENT_LIBRARIES +=/home/tony/esp/prebuilds/libtdp.a
COMPONENT_LDFLAGS += -L/home/tony/esp/prebuilds/libtdp.a
