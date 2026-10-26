#ifndef THINGBOOT_SDK_MESSAGE_H
#define THINGBOOT_SDK_MESSAGE_H

class ThingBootDevice;

class ThingBootMessage {
private:
    ThingBootDevice* _device;

public:
    ThingBootMessage(ThingBootDevice* device = nullptr) : _device(device) {}

    // 生成消息 ID（mid，8 位），与 SDK 内部同规则（md5 居中截 8 位），
    // 用于 publishMessage 的 mid 参数及消息关联
    // Generate a message ID (mid, 8 chars) with the same rule as the SDK
    // internals, for the mid parameter of publishMessage and message correlation
    std::string mid();

    // 向平台发布消息
    // Publish message to platform
    bool publishMessage(SYS_TOPIC topic, std::string mid, std::string data, uint32_t device = 0);
    bool publishMessage(SYS_TOPIC topic, std::string data, uint32_t device);
    bool publishMessage(SYS_TOPIC topic, std::string data);
};

#endif
