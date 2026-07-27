#ifndef THINGBOOT_SDK_PERIPHERAL_H
#define THINGBOOT_SDK_PERIPHERAL_H

class ThingBootDevice;

class ThingBootPeripheral {
private:
    ThingBootDevice* _device;

public:
    ThingBootPeripheral(ThingBootDevice* device = nullptr) : _device(device) {}

    // 外设预初始化回调
    // Peripheral pre-initialization callback
    uint16_t onInitPre(std::function<void()> callback);

    // 外设初始化回调
    // Peripheral initialization callback
    uint16_t onInit(std::function<void()> callback);

    // 配置设备按钮
    // callback 中 keep 为按下持续时长，单位毫秒
    // Configure device button
    // callback: keep is press duration in milliseconds
    uint16_t setDeviceBtn(uint8_t num, uint8_t gpio_pin, bool trigger_level,
        std::function<void(uint8_t num, BTN_OPER oper, uint16_t keep)> callback);

    // 设定系统按钮
    // Set system button
    uint16_t setSystemBtn(uint8_t num);

    // 配置设备 LED
    // Configure device LED
    uint16_t setDeviceLed(uint8_t num, uint8_t gpio_pin, bool default_state = false, bool active_level = false);

    // 设定系统 LED
    // Set system LED
    uint16_t setSystemLed(uint8_t num);

    // 点亮 LED
    // Turn LED on
    uint16_t ledOn(uint8_t num);

    // 熄灭 LED
    // Turn LED off
    uint16_t ledOff(uint8_t num);

    // 翻转 LED 状态
    // Toggle LED state
    uint16_t ledToggle(uint8_t num);

    // 设置 LED 状态
    // Set LED state
    uint16_t ledToggle(uint8_t num, bool state);

    // LED 闪烁
    // duration_ms：点亮/熄灭时长，单位毫秒
    // interval_ms：闪烁间隔，单位毫秒
    // times：闪烁次数，0 表示无限循环
    // Blink LED
    uint16_t ledBlink(uint8_t num, uint16_t duration_ms);
    uint16_t ledBlinkInterval(uint8_t num, uint16_t interval_ms);
    uint16_t ledBlinkTimes(uint8_t num, uint16_t times);
};

#endif
