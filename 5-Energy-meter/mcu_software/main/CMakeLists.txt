set(COMPONENT_SRCS "hello_world_main.c"
        #"oled12864/o12864.c" "oled12864/ofont.o"
        "lcd/lcd.c"
        "ina226/ina226.c"
        "usb/myusb.c"
        "keys/mykeys.c"
        "mytimer/mytimer.c"
        #"tft13/oled.c"
        #"tts/myuart.c" "tts/syn6288.c" #tts module
        #"ads131/ads131.c" "ads131/hal.c" "ads131/fnirsdata.c" #ads131
        #"wifi/wifi.c"

        )

set(COMPONENT_ADD_INCLUDEDIRS "oled12864"
        "mytimer"
        "keys"
        "tts"
        "usb"
        "ads131"
        "wifi"
        "fs"
        "ina226"
        "inadc"
        "keys"
        "lcd"
        #"gaiacli"
        "ble"
        )


register_component()

