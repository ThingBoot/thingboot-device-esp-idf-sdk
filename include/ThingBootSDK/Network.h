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

    // TODO: ETHER / GSM 接口（对应阶段，与 Arduino 版同为 TBD_ETHER / TBD_GSM 宏裁剪）
};

#endif
