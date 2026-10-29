#ifndef THINGBOOT_SDK_ENUMS_H
#define THINGBOOT_SDK_ENUMS_H

#include <cstdint>

// 系统状态
enum SYS_STATE : uint8_t {
    SYS_STATE_IDLE = 0,  // 系统空闲，不上报状态
    SYS_STATE_BOOT,      // 启动
    SYS_STATE_LOOP,      // 进入主循环，最终设备会留在这里
    SYS_STATE_ONLINE,    // 在线
    SYS_STATE_OFFLINE    // 离线
};

// 系统消息主题
enum SYS_TOPIC : uint8_t {
    TOPIC_UNKNOWN = 0,
    TOPIC_ORDER,
    TOPIC_EVENT,
    TOPIC_STATE,
    TOPIC_CONFIG,
    TOPIC_NTP,
    TOPIC_OTA,
    TOPIC_API,
    TOPIC_DEBUG,
    TOPIC_COUNT  // 主题数量 / Topic count
};

// 按钮操作
enum BTN_OPER : uint8_t {
    BTN_IDLE = 0,
    BTN_DOWN,
    BTN_UP
};

// 网络变化事件（Network.onNetworkChange 回调）
enum NETWORK_EVENT : uint8_t {
    NETWORK_EVENT_OFFLINE = 0,  // 网络断开（失去可用 IP）
    NETWORK_EVENT_ONLINE,       // 网络就绪（拿到 IP / PPP 拨号成功）
    NETWORK_EVENT_TYPE_CHANGED  // 联网类型切换（wifi/ether/gsm），附新类型
};

#endif
