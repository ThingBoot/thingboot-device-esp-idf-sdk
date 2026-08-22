# ThingBoot Device SDK - ESP-IDF 组件（预编译闭源分发）
# 架构：base 库（必链）+ addon 库（Kconfig 选链）。
# 使用以太网/GSM/BLE/网关时，除开启对应 Kconfig 外，还需在 app_main 中
# device.setup() 前调用 tb_addon_net_<模块>_install() / tb_addon_gateway_install()。

# addon 选择（Kconfig）：CONFIG_TBD_ETHER 以太网 / CONFIG_TBD_GSM GSM/4G / CONFIG_TBD_BLE 蓝牙配网+控制 / CONFIG_TBD_GATEWAY 网关
set(_tbd_requires "")
set(_tbd_addons "")

if(CONFIG_TBD_ETHER)
    list(APPEND _tbd_requires esp_eth)
    list(APPEND _tbd_addons "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_addon_net_ether_${IDF_TARGET}.a")
endif()
if(CONFIG_TBD_GSM)
    list(APPEND _tbd_requires espressif__esp_modem)
    list(APPEND _tbd_addons "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_addon_net_gsm_${IDF_TARGET}.a")
endif()
if(CONFIG_TBD_BLE)
    list(APPEND _tbd_requires wifi_provisioning bt protocomm)
    list(APPEND _tbd_addons "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_addon_net_ble_${IDF_TARGET}.a")
endif()
if(CONFIG_TBD_GATEWAY)
    list(APPEND _tbd_addons "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_addon_gateway_${IDF_TARGET}.a")
endif()

set(_tbd_base "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
if(NOT EXISTS "${_tbd_base}")
    message(FATAL_ERROR "ThingBoot SDK 暂未提供该芯片的预编译 base 库: ${_tbd_base}")
endif()
foreach(_addon IN LISTS _tbd_addons)
    if(NOT EXISTS "${_addon}")
        message(FATAL_ERROR "ThingBoot SDK 暂未提供该芯片的联网 addon 库: ${_addon}")
    endif()
endforeach()

# 依赖组件必须通过 REQUIRES 声明（而非 target_link_libraries 裸名），
# 否则其库目录不在链接路径中，报 cannot find -lbt / -lwifi_provisioning 等错误
idf_component_register(INCLUDE_DIRS "include" REQUIRES ${_tbd_requires})

# addon 先于 base 链接（约定；用户经 tb_addon_net_*_install() 显式引用 addon 符号）
add_prebuilt_library(thingboot_device "${_tbd_base}")
target_link_libraries(${COMPONENT_LIB} INTERFACE ${_tbd_addons} thingboot_device)

# 兼容用户代码中的 #ifdef TBD_*（公开头已不依赖这些宏）
if(CONFIG_TBD_ETHER)
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_ETHER)
endif()
if(CONFIG_TBD_GSM)
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_GSM)
endif()
if(CONFIG_TBD_BLE)
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_BLE)
endif()
if(CONFIG_TBD_GATEWAY)
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_GATEWAY)
endif()

# Arduino_JSON 兼容层使用 JSON.typeof 命名；新版 GCC（-std=gnu++2b）将 typeof 视为关键字，
# -fno-gnu-keywords 允许其作为标识符使用。INTERFACE 传播给使用者，兼容用户代码中的 JSON.typeof。
target_compile_options(${COMPONENT_LIB} INTERFACE -fno-gnu-keywords)
