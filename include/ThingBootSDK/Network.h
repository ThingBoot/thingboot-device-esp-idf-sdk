#ifndef THINGBOOT_SDK_NETWORK_H
#define THINGBOOT_SDK_NETWORK_H

class ThingBootDevice;

class ThingBootNetwork {
private:
    ThingBootDevice* _device;

public:
    ThingBootNetwork(ThingBootDevice* device = nullptr) : _device(device) {}

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

#ifdef TBD_ETHER
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
#endif

    // TODO: GSM 接口（对应阶段，与 Arduino 版同为 TBD_GSM 宏裁剪）
};

#endif
