# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# compile C with /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc
C_DEFINES = -DHAVE_CONFIG_H -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\" -DUNITY_INCLUDE_CONFIG_H -DWITH_POSIX

C_INCLUDES = -I/home/tony/esp/esp-idf/components/esp_pm/include -I/home/tony/esp/IOMTV4_power/build/config -I/home/tony/esp/esp-idf/components/newlib/platform_include -I/home/tony/esp/esp-idf/components/freertos/include -I/home/tony/esp/esp-idf/components/freertos/port/xtensa/include -I/home/tony/esp/esp-idf/components/esp_hw_support/include -I/home/tony/esp/esp-idf/components/esp_hw_support/port/esp32s2/. -I/home/tony/esp/esp-idf/components/esp_hw_support/port/esp32s2/private_include -I/home/tony/esp/esp-idf/components/heap/include -I/home/tony/esp/esp-idf/components/log/include -I/home/tony/esp/esp-idf/components/lwip/include/apps -I/home/tony/esp/esp-idf/components/lwip/include/apps/sntp -I/home/tony/esp/esp-idf/components/lwip/lwip/src/include -I/home/tony/esp/esp-idf/components/lwip/port/esp32/include -I/home/tony/esp/esp-idf/components/lwip/port/esp32/include/arch -I/home/tony/esp/esp-idf/components/soc/include -I/home/tony/esp/esp-idf/components/soc/esp32s2/. -I/home/tony/esp/esp-idf/components/soc/esp32s2/include -I/home/tony/esp/esp-idf/components/hal/esp32s2/include -I/home/tony/esp/esp-idf/components/hal/include -I/home/tony/esp/esp-idf/components/esp_rom/include -I/home/tony/esp/esp-idf/components/esp_rom/esp32s2 -I/home/tony/esp/esp-idf/components/esp_common/include -I/home/tony/esp/esp-idf/components/esp_system/include -I/home/tony/esp/esp-idf/components/esp32s2/include -I/home/tony/esp/esp-idf/components/driver/include -I/home/tony/esp/esp-idf/components/driver/esp32s2/include -I/home/tony/esp/esp-idf/components/esp_ringbuf/include -I/home/tony/esp/esp-idf/components/efuse/include -I/home/tony/esp/esp-idf/components/efuse/esp32s2/include -I/home/tony/esp/esp-idf/components/xtensa/include -I/home/tony/esp/esp-idf/components/xtensa/esp32s2/include -I/home/tony/esp/esp-idf/components/espcoredump/include -I/home/tony/esp/esp-idf/components/esp_timer/include -I/home/tony/esp/esp-idf/components/esp_ipc/include -I/home/tony/esp/esp-idf/components/vfs/include -I/home/tony/esp/esp-idf/components/esp_wifi/include -I/home/tony/esp/esp-idf/components/esp_wifi/esp32s2/include -I/home/tony/esp/esp-idf/components/esp_event/include -I/home/tony/esp/esp-idf/components/esp_netif/include -I/home/tony/esp/esp-idf/components/esp_eth/include -I/home/tony/esp/esp-idf/components/tcpip_adapter/include -I/home/tony/esp/esp-idf/components/app_trace/include -I/home/tony/esp/esp-idf/components/mbedtls/port/include -I/home/tony/esp/esp-idf/components/mbedtls/mbedtls/include -I/home/tony/esp/esp-idf/components/mbedtls/esp_crt_bundle/include -I/home/tony/esp/esp-idf/components/app_update/include -I/home/tony/esp/esp-idf/components/spi_flash/include -I/home/tony/esp/esp-idf/components/bootloader_support/include -I/home/tony/esp/esp-idf/components/nvs_flash/include -I/home/tony/esp/esp-idf/components/pthread/include -I/home/tony/esp/esp-idf/components/esp_gdbstub/include -I/home/tony/esp/esp-idf/components/esp_gdbstub/xtensa -I/home/tony/esp/esp-idf/components/esp_gdbstub/esp32s2 -I/home/tony/esp/esp-idf/components/wpa_supplicant/include -I/home/tony/esp/esp-idf/components/wpa_supplicant/port/include -I/home/tony/esp/esp-idf/components/wpa_supplicant/include/esp_supplicant -I/home/tony/esp/esp-idf/components/asio/asio/asio/include -I/home/tony/esp/esp-idf/components/asio/port/include -I/home/tony/esp/esp-idf/components/cbor/port/include -I/home/tony/esp/esp-idf/components/cfp/include -I/home/tony/esp/esp-idf/components/unity/include -I/home/tony/esp/esp-idf/components/unity/unity/src -I/home/tony/esp/esp-idf/components/cmock/CMock/src -I/home/tony/esp/esp-idf/components/coap/port/include -I/home/tony/esp/esp-idf/components/coap/port/include/coap -I/home/tony/esp/esp-idf/components/coap/libcoap/include -I/home/tony/esp/esp-idf/components/coap/libcoap/include/coap2 -I/home/tony/esp/esp-idf/components/console -I/home/tony/esp/esp-idf/components/nghttp/port/include -I/home/tony/esp/esp-idf/components/nghttp/nghttp2/lib/includes -I/home/tony/esp/esp-idf/components/esp-tls -I/home/tony/esp/esp-idf/components/esp-tls/esp-tls-crypto -I/home/tony/esp/esp-idf/components/esp_adc_cal/include -I/home/tony/esp/esp-idf/components/esp_hid/include -I/home/tony/esp/esp-idf/components/tcp_transport/include -I/home/tony/esp/esp-idf/components/esp_http_client/include -I/home/tony/esp/esp-idf/components/esp_http_server/include -I/home/tony/esp/esp-idf/components/esp_https_ota/include -I/home/tony/esp/esp-idf/components/protobuf-c/protobuf-c -I/home/tony/esp/esp-idf/components/protocomm/include/common -I/home/tony/esp/esp-idf/components/protocomm/include/security -I/home/tony/esp/esp-idf/components/protocomm/include/transports -I/home/tony/esp/esp-idf/components/mdns/include -I/home/tony/esp/esp-idf/components/esp_local_ctrl/include -I/home/tony/esp/esp-idf/components/sdmmc/include -I/home/tony/esp/esp-idf/components/esp_serial_slave_link/include -I/home/tony/esp/esp-idf/components/esp_websocket_client/include -I/home/tony/esp/esp-idf/components/expat/expat/expat/lib -I/home/tony/esp/esp-idf/components/expat/port/include -I/home/tony/esp/esp-idf/components/wear_levelling/include -I/home/tony/esp/esp-idf/components/fatfs/diskio -I/home/tony/esp/esp-idf/components/fatfs/vfs -I/home/tony/esp/esp-idf/components/fatfs/src -I/home/tony/esp/esp-idf/components/freemodbus/common/include -I/home/tony/esp/esp-idf/components/idf_test/include -I/home/tony/esp/esp-idf/components/idf_test/include/esp32s2 -I/home/tony/esp/esp-idf/components/jsmn/include -I/home/tony/esp/esp-idf/components/json/cJSON -I/home/tony/esp/esp-idf/components/libsodium/libsodium/src/libsodium/include -I/home/tony/esp/esp-idf/components/libsodium/port_include -I/home/tony/esp/esp-idf/components/mqtt/esp-mqtt/include -I/home/tony/esp/esp-idf/components/openssl/include -I/home/tony/esp/esp-idf/components/perfmon/include -I/home/tony/esp/esp-idf/components/spiffs/include -I/home/tony/esp/esp-idf/components/freertos/include/freertos -I/home/tony/esp/esp-idf/components/tinyusb/tinyusb/src -I/home/tony/esp/esp-idf/components/tinyusb/additions/include -I/home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/tony -I/home/tony/esp/esp-idf/components/touch_element/include -I/home/tony/esp/esp-idf/components/ulp/include -I/home/tony/esp/esp-idf/components/wifi_provisioning/include -I/home/tony/esp/IOMTV4_power/main/oled12864 -I/home/tony/esp/IOMTV4_power/main/mytimer -I/home/tony/esp/IOMTV4_power/main/keys -I/home/tony/esp/IOMTV4_power/main/tts -I/home/tony/esp/IOMTV4_power/main/usb -I/home/tony/esp/IOMTV4_power/main/ads131 -I/home/tony/esp/IOMTV4_power/main/wifi -I/home/tony/esp/IOMTV4_power/main/fs -I/home/tony/esp/IOMTV4_power/main/ina226 -I/home/tony/esp/IOMTV4_power/main/inadc -I/home/tony/esp/IOMTV4_power/main/lcd -I/home/tony/esp/IOMTV4_power/main/ble

C_FLAGS = -mlongcalls -Wall

