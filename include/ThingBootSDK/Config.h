#ifndef THINGBOOT_SDK_CONFIG_H
#define THINGBOOT_SDK_CONFIG_H

class ThingBootDevice;

class ThingBootConfig {
private:
    ThingBootDevice* _device;

public:
    ThingBootConfig(ThingBootDevice* device = nullptr) : _device(device) {}

    // 添加设备配置项
    // pos 取值范围为 0~1999，实际存储位置会自动加 1000
    // hide 为 true 时，用户在读取全部配置（fetch）时看不到该配置
    // Add a device configuration item
    // pos: 0~1999, actual storage position will be pos + 1000
    // If hide is true, the item is omitted when fetching all configs
    uint16_t addConfig(const char* name, uint16_t pos, uint8_t length, const char* group = "", bool hide = false);

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
