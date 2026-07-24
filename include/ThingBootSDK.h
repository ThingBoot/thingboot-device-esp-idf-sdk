#ifndef THINGBOOT_SDK_H
#define THINGBOOT_SDK_H

#include "ThingBootSDK/Types.h"

// 内部实现类前向声明
class ThingBootDeviceImpl;

class ThingBootDevice {
private:
    ThingBootDeviceImpl* _impl;

public:
    // Core 核心接口（保持为 ThingBootDevice 直接成员）
    #include "ThingBootSDK/Core.h"

    ThingBootDevice();
    ~ThingBootDevice();

    ThingBootDevice(const ThingBootDevice&) = delete;
    ThingBootDevice& operator=(const ThingBootDevice&) = delete;
};

#endif
