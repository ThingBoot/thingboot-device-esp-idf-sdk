# ThingBoot Device SDK - ESP-IDF 组件（预编译闭源分发）
idf_component_register(INCLUDE_DIRS "include")

# 按目标芯片选择预编译库
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
    message(FATAL_ERROR "ThingBoot SDK 暂未提供 ${IDF_TARGET} 芯片的预编译库")
endif()

add_prebuilt_library(thingboot_device "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
target_link_libraries(${COMPONENT_LIB} INTERFACE thingboot_device)

# Arduino_JSON 兼容层使用 JSON.typeof 命名；新版 GCC（-std=gnu++2b）将 typeof 视为关键字，
# -fno-gnu-keywords 允许其作为标识符使用。INTERFACE 传播给使用者，兼容用户代码中的 JSON.typeof。
target_compile_options(${COMPONENT_LIB} INTERFACE -fno-gnu-keywords)
