# ThingBoot Device SDK - ESP-IDF 组件（预编译闭源分发）
idf_component_register(INCLUDE_DIRS "include")

# 功能变体选择（Kconfig）：CONFIG_TBD_ETHER 启用以太网库，CONFIG_TBD_GSM 启用 GSM/4G 库
if(CONFIG_TBD_GSM)
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}_gsm.a")
elseif(CONFIG_TBD_ETHER)
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}_ether.a")
else()
    set(_tbd_lib "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
endif()

if(NOT EXISTS "${_tbd_lib}")
    message(FATAL_ERROR "ThingBoot SDK 暂未提供该芯片/变体的预编译库: ${_tbd_lib}")
endif()

add_prebuilt_library(thingboot_device "${_tbd_lib}")
target_link_libraries(${COMPONENT_LIB} INTERFACE thingboot_device)

if(CONFIG_TBD_ETHER)
    # 公开头的 TBD_ETHER 接口段对使用者可见；链接 esp_eth 组件
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_ETHER)
    target_link_libraries(${COMPONENT_LIB} INTERFACE esp_eth)
endif()

if(CONFIG_TBD_GSM)
    # 公开头的 TBD_GSM 接口段对使用者可见；链接 esp_modem 组件（由 idf_component.yml 依赖拉取）
    target_compile_options(${COMPONENT_LIB} INTERFACE -DTBD_GSM)
    target_link_libraries(${COMPONENT_LIB} INTERFACE espressif__esp_modem)
endif()

# Arduino_JSON 兼容层使用 JSON.typeof 命名；新版 GCC（-std=gnu++2b）将 typeof 视为关键字，
# -fno-gnu-keywords 允许其作为标识符使用。INTERFACE 传播给使用者，兼容用户代码中的 JSON.typeof。
target_compile_options(${COMPONENT_LIB} INTERFACE -fno-gnu-keywords)
