#ifndef THINGBOOT_SDK_ORDER_H
#define THINGBOOT_SDK_ORDER_H

class ThingBootDevice;

class ThingBootOrder {
private:
    ThingBootDevice* _device;

public:
    ThingBootOrder(ThingBootDevice* device = nullptr) : _device(device) {}

    // 设置命令回调
    // Set order callback
    uint16_t onOrder(std::function<void(const char*, JSONVar)> order_callback);

    // 命令应答
    // Reply to order
    bool replyMessage(const char* data);
};

#endif
