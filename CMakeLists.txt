# ThingBoot Device SDK - ESP-IDF 组件（预编译闭源分发）

# 功能变体选择（Kconfig）：CONFIG_TBD_ETHER 启用以太网库，CONFIG_TBD_GSM 启用 GSM/4G 库，CONFIG_TBD_BLE 启用蓝牙配网库
set(_tbd_requires "")
if(CONFIG_TBD_GSM)
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}_gsm.a")
    list(APPEND _tbd_requires espressif__esp_modem)
elseif(CONFIG_TBD_ETHER)
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}_ether.a")
    list(APPEND _tbd_requires esp_eth)
elseif(CONFIG_TBD_BLE)
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}_ble.a")
    list(APPEND _tbd_requires wifi_provisioning bt protocomm)
else()
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
endif()

if(NOT EXISTS "${_tbd_lib}")
    message(FATAL_ERROR "ThingBoot SDK 暂未提供该芯片/变体的预编译库: ${_tbd_lib}")
endif()

# 依赖组件必须通过 REQUIRES 声明（而非 target_link_libraries 裸名），
# 否则其库目录不在链接路径中，报 cannot find -lbt / -lwifi_provisioning 等错误
idf_component_register(INCLUDE_DIRS "include" REQUIRES ${_tbd_requires})

add_prebuilt_library(thingboot_device "${_tbd_lib}")
target_link_libraries(${COMPONENT_LIB} INTERFACE thingboot_device)

if(CONFIG_TBD_ETHER)
    # 公开头的 TBD_ETHER 接口段对使用者可见
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_ETHER)
endif()

if(CONFIG_TBD_GSM)
    # 公开头的 TBD_GSM 接口段对使用者可见
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_GSM)
endif()

if(CONFIG_TBD_BLE)
    # 公开头/内部的 TBD_BLE 段对使用者可见
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_BLE)
endif()

# Arduino_JSON 兼容层使用 JSON.typeof 命名；新版 GCC（-std=gnu++2b）将 typeof 视为关键字，
# -fno-gnu-keywords 允许其作为标识符使用。INTERFACE 传播给使用者，兼容用户代码中的 JSON.typeof。
target_compile_options(${COMPONENT_LIB} INTERFACE -fno-gnu-keywords)
