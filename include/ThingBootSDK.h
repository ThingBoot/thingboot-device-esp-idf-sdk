#ifndef THINGBOOT_SDK_H
#define THINGBOOT_SDK_H

#include "ThingBootSDK/Types.h"
#include "ThingBootSDK/JSON.h"
#include "ThingBootSDK/Utils.h"

// 内部实现类前向声明
class ThingBootDeviceImpl;

// 先完整定义各子模块类，以便作为 ThingBootDevice 的成员对象
#include "ThingBootSDK/Config.h"
#include "ThingBootSDK/Order.h"
#include "ThingBootSDK/Event.h"
#include "ThingBootSDK/Message.h"
#include "ThingBootSDK/State.h"
#include "ThingBootSDK/Timer.h"
#include "ThingBootSDK/Peripheral.h"
#include "ThingBootSDK/Network.h"

class ThingBootDevice {
    // 允许子模块访问 _impl
    friend class ThingBootConfig;
    friend class ThingBootOrder;
    friend class ThingBootEvent;
    friend class ThingBootMessage;
    friend class ThingBootState;
    friend class ThingBootTimer;
    friend class ThingBootPeripheral;
    friend class ThingBootNetwork;

private:
    ThingBootDeviceImpl* _impl;

public:
    // Core 核心接口（保持为 ThingBootDevice 直接成员）
    #include "ThingBootSDK/Core.h"

    // 子模块对象（按功能分组，降低 API 密集感）
    ThingBootConfig Config;
    ThingBootOrder Order;
    ThingBootEvent Event;
    ThingBootMessage Message;
    ThingBootState State;
    ThingBootTimer Timer;
    ThingBootPeripheral Peripheral;
    ThingBootNetwork Network;

    ThingBootDevice();
    ~ThingBootDevice();

    ThingBootDevice(const ThingBootDevice&) = delete;
    ThingBootDevice& operator=(const ThingBootDevice&) = delete;
};

#endif
