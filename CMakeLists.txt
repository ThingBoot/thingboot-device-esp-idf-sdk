# ThingBoot Device SDK - ESP-IDF 组件（预编译闭源分发）
idf_component_register(INCLUDE_DIRS "include")

# 按目标芯片选择预编译库
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
    message(FATAL_ERROR "ThingBoot SDK 暂未提供 ${IDF_TARGET} 芯片的预编译库")
endif()

add_prebuilt_library(thingboot_device "${CMAKE_CURRENT_LIST_DIR}/lib/libthingboot_device_${IDF_TARGET}.a")
target_link_libraries(${COMPONENT_LIB} INTERFACE thingboot_device)
