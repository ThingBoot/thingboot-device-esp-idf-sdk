#ifndef THINGBOOT_SDK_CONFIG_H
#define THINGBOOT_SDK_CONFIG_H

class ThingBootDevice;

// addConfig 的 pos 缺省值：配置项由 SDK 托管存储（免位置/长度）
// 各平台后端：ESP-IDF = 原生 NVS（namespace tbd_cfg）；Arduino = 不支持（返回 12013）
#define TB_CONFIG_AUTO 0xFFFF

class ThingBootConfig {
private:
    ThingBootDevice* _device;

public:
    ThingBootConfig(ThingBootDevice* device = nullptr) : _device(device) {}

    // 添加设备配置项
    // pos 传 TB_CONFIG_AUTO（缺省）时由 SDK 托管存储，无需指定位置和长度：
    //   ESP-IDF 版：值存原生 NVS（name ≤15 字符）；此时 length 语义为最大长度（0=默认 64）
    //   Arduino 版：不支持自动分配，必须显式指定 pos/length（否则返回 ERR_CONFIG_AUTO_UNSUPPORTED）
    // pos 显式指定时取值范围为 0~1999，实际存储位置会自动加 1000
    // hide 为 true 时，用户在读取全部配置（fetch）时看不到该配置
    // Add a device configuration item
    // pos: TB_CONFIG_AUTO (default) = SDK-managed storage; or 0~1999 (stored at pos + 1000)
    // If hide is true, the item is omitted when fetching all configs
    uint16_t addConfig(const char* name, uint16_t pos = TB_CONFIG_AUTO, uint8_t length = 0, const char* group = "", bool hide = false);

    // 按 name 读取设备配置值
    // 当 name 为空字符串时返回 default
    // Read device configuration value by name
    // Returns default when name is an empty string
    std::string readConfig(const char* name, const char* default_value = "");

    // 按 name 保存设备配置值
    // Save device configuration value by name
    uint16_t saveConfig(const char* name, const char* value);

    // 清空所有设备配置项的值
    // Clear all device configuration values
    uint16_t clearConfig();

    // 清空指定设备配置项的值
    // Reset the specified device configuration value to empty
    uint16_t resetConfig(const char* name);

    // 配置变化回调
    // Configuration change callback
    uint16_t onConfig(std::function<void(const char*, std::string)> config_callback);
};

#endif
