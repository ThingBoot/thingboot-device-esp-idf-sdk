#ifndef THINGBOOT_SDK_EVENT_H
#define THINGBOOT_SDK_EVENT_H

class ThingBootDevice;

class ThingBootEvent {
private:
    ThingBootDevice* _device;

public:
    ThingBootEvent(ThingBootDevice* device = nullptr) : _device(device) {}

    // 注册属性变化事件
    // Register attribute change event
    uint16_t onAttributeChange(const char* name,
        std::function<void(const char* current, const char* previous)> callback,
        uint32_t debounce_ms = 100);

    // 设置属性值
    // Set attribute value
    uint16_t setAttribute(const char* name, const char* value);

    // 设置属性变化防抖时间
    // Set attribute change debounce time
    uint16_t setAttributeDebounce(const char* name, uint32_t debounce_ms);

    // 上报事件
    // Report event
    bool reportEvent(const char* name, const char* data);
    bool reportEvent(const char* name, JSONVar data);
};

#endif
