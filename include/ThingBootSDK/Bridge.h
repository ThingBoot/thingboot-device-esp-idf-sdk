#ifndef THINGBOOT_SDK_BRIDGE_H
#define THINGBOOT_SDK_BRIDGE_H

class ThingBootDevice;

#ifndef NO_BRIDGE

class ThingBootBridge {
private:
    ThingBootDevice* _device;

public:
    ThingBootBridge(ThingBootDevice* device = nullptr) : _device(device) {}

    // 配置并启动 UART 桥接
    // Configure and start UART bridge
    uint16_t setupUart(uint8_t uart_num, uint32_t baud,
                       int8_t rxPin = -1, int8_t txPin = -1);

    // 配置并启动 SPI 桥接
    // Configure and start SPI bridge
    uint16_t setupSpi(int8_t sck, int8_t miso, int8_t mosi, int8_t cs,
                      uint32_t speed = 1000000);

    // 发送原始字节数据
    // Send raw bytes
    uint16_t send(const uint8_t* data, uint16_t len);

    // 发送字符串（不含换行符）
    // Send string (without newline)
    uint16_t sendString(const char* str);

    // 发送格式化字符串
    // Send formatted string
    uint16_t sendPrintf(const char* fmt, ...);

    // 接收数据
    // timeout_ms = 0 表示非阻塞；> 0 表示最多等待指定毫秒
    // Receive data; timeout_ms = 0 for non-blocking
    uint16_t receive(uint8_t* buffer, uint16_t len, uint32_t timeout_ms = 0);

    // 查询当前可读取的字节数（仅 UART 有效）
    // Query available bytes (UART only)
    uint16_t available();

    // 主循环调用，用于处理接收数据（UART 模式必须周期性调用）
    // Call in loop() to handle incoming data (required for UART)
    uint16_t handle();

    // 设置数据接收回调
    // Set data receive callback
    uint16_t setOnReceive(std::function<void(const uint8_t* data, uint16_t len)> cb);

    // 设置错误回调
    // Set error callback
    uint16_t setOnError(std::function<void(uint16_t code)> cb);

    // 获取统计信息
    // Get statistics
    uint16_t getStats(uint32_t* txBytes, uint32_t* rxBytes,
                      uint32_t* rxOverflow, uint32_t* txError);
};

#endif // NO_BRIDGE

#endif
