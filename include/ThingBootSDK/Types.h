#ifndef THINGBOOT_SDK_TYPES_H
#define THINGBOOT_SDK_TYPES_H

#include <cstdint>
#include <string>
#include <functional>

#define THINGBOOT_SDK_NAME "esp-idf"
#define THINGBOOT_SDK_VERSION "1.24.0"

#include <ThingBootSDK/Enums.h>
#include <ThingBootSDK/Errors.h>

// 外设最大数量（ESP32 系列固定为 8）
#define BTN_MAX     8
#define LED_MAX     8

// ROM 配置映射最大项数（128 个；多路控制器类产品需要，与 Arduino 版统一，见 uni-kzq）
#define ROM_DEVICE_MAX 128

class ThingBootDeviceImpl;

#endif
