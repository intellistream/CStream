file(REMOVE_RECURSE
        "IOMTV3.bin"
        "IOMTV3.map"
        "bootloader/bootloader.bin"
        "bootloader/bootloader.elf"
        "bootloader/bootloader.map"
        "config/sdkconfig.cmake"
        "config/sdkconfig.h"
        "flash_project_args"
        "project_elf_src_esp32s2.c"
        "CMakeFiles/dfu-list"
        )

# Per-language clean rules from dependency scanning.
foreach (lang)
    include(CMakeFiles/dfu-list.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach ()
