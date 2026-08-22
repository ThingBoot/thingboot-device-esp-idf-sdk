#ifndef THINGBOOT_SDK_NETWORK_H
#define THINGBOOT_SDK_NETWORK_H

class ThingBootDevice;

// ---- 联网 addon 安装函数（链接对应 addon 库后，在 device.setup() 前调用）----
// 返回 ERR_OK 成功；ERR_NETWORK_ABI_MISMATCH 表示 addon 与 base 版本不一致。
// 也可经成员转发版 Network.installEthernet()/installGSM()/installBLE() 调用（等价）
uint16_t tb_addon_net_ether_install();
uint16_t tb_addon_net_gsm_install();
uint16_t tb_addon_net_ble_install();

class ThingBootNetwork {
private:
    ThingBootDevice* _device;

public:
    ThingBootNetwork(ThingBootDevice* device = nullptr) : _device(device) {}

    // addon 安装（自由函数 tb_addon_net_*_install() 的成员转发版，完全等价，
    // 供编辑器提示发现；未链接对应 addon 库时不要调用）
    uint16_t installEthernet() { return tb_addon_net_ether_install(); }
    uint16_t installGSM() { return tb_addon_net_gsm_install(); }
    uint16_t installBLE() { return tb_addon_net_ble_install(); }

    // 获取当前网络信息（JSON 字符串）
    // Get current network information as JSON string
    std::string getNetworkInfo();

    // 连接 WiFi
    // Connect to WiFi
    void connectWiFi();
    bool connectWiFi(const char* ssid, const char* psk);
    void disconnectWiFi();
    void clearWiFiConfig();
    bool addWiFiConfig(const char* ssid, const char* psk);
    bool addWiFiConfig(const char* ssid, const char* psk, uint8_t pos);
    bool updateWiFiConfig(const char* ssid, const char* psk);
    bool deleteWiFiConfig(const char* ssid);
    bool deleteWiFiConfig(uint8_t pos);
    std::string getWiFiConfig();

    // ---- 以太网（需链接 addon_net_ether；未注册驱动时返回 ERR_NETWORK_DRIVER_MISSING）----
    // 设置以太网芯片型号（预留多芯片支持，当前: "w5500"，默认）
    // Set Ethernet chip type (reserved for future chip support, currently: "w5500", default)
    uint16_t setEthernetChip(const char* chip);

    // 设置以太网 SPI 片选引脚和复位引脚
    // Set Ethernet SPI CS and reset pins
    void setEthernetPin(uint8_t cs, int8_t rst = -1);

    // 尝试连接以太网
    // Try to connect Ethernet
    std::string tryConnectEthernet();

    // 连接以太网
    // Connect Ethernet
    bool connectEthernet();

    // 断开以太网
    // Disconnect Ethernet
    void disconnectEthernet();

    // ---- GSM/4G（需链接 addon_net_gsm；未注册驱动时返回 ERR_NETWORK_DRIVER_MISSING）----
    // 设置 GSM 模组芯片型号（预留多芯片支持，当前: "ml307"，默认）
    // Set GSM modem chip type (reserved for future chip support, currently: "ml307", default)
    uint16_t setGSMChip(const char* chip);

    // 设置 GSM 串口与波特率
    // 开发者需确保对应 UART 引脚可用
    // Set the GSM UART port, pins and baud rate
    void setGSMSerialPort(uint8_t uart_num, int8_t tx_pin, int8_t rx_pin, uint32_t baud = 115200);

    // 尝试连接 GSM
    // Try to connect GSM
    std::string tryConnectGSM();

    // 连接 GSM
    // Connect GSM
    bool connectGSM();

    // 断开 GSM
    // Disconnect GSM
    void disconnectGSM();
};

#endif
