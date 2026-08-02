#ifndef THINGBOOT_SDK_TIMER_H
#define THINGBOOT_SDK_TIMER_H

class ThingBootDevice;

class ThingBootTimer {
private:
    ThingBootDevice* _device;

public:
    ThingBootTimer(ThingBootDevice* device = nullptr) : _device(device) {}

    // 注册用户定时器
    // Register user timer
    uint16_t addTimer(uint32_t interval_ms, int32_t count,
        std::function<void()> callback);

    // 注册用户定时器（默认无限循环）
    // Register user timer (infinite loop by default)
    uint16_t addTimer(uint32_t interval_ms,
        std::function<void()> callback);
};

#endif
