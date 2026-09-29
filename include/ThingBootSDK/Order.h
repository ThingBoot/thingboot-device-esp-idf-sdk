#ifndef THINGBOOT_SDK_ORDER_H
#define THINGBOOT_SDK_ORDER_H

class ThingBootDevice;

class ThingBootOrder {
private:
    ThingBootDevice* _device;

public:
    ThingBootOrder(ThingBootDevice* device = nullptr) : _device(device) {}

    // 设置命令回调（回调首参为消息 ID（mid），第二参为命令数据；
    // 应答时将同一个 mid 传给 replyMessage，平台据此关联命令与应答）
    // Set order callback (first arg is the message ID (mid), second is the order data;
    // pass the same mid to replyMessage so the platform can correlate the reply)
    uint16_t onOrder(std::function<void(const char*, JSONVar)> order_callback);

    // 命令应答（mid 为收到的命令消息 ID）
    // Reply to order (mid is the message ID of the received order)
    bool replyMessage(const char* mid, const char* data);
};

#endif
