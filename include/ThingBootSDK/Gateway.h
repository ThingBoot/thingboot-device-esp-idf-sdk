#ifndef THINGBOOT_SDK_GATEWAY_H
#define THINGBOOT_SDK_GATEWAY_H

class ThingBootDevice;

// 网关 addon 安装函数（链接 addon_gateway 库后，在 device.setup() 前调用）
// install 即角色：按产品指定的最大子设备数分配表空间并加载设备表。
// 返回 ERR_OK 成功；ERR_SYSTEM_VALUE_NULL 容量为 0；ERR_MODULE_SYSTEM 分配失败；
// ERR_NETWORK_ABI_MISMATCH 表示 addon 与 base 版本不一致
uint16_t tb_addon_gateway_install(uint16_t maxChildren);

// 子设备记录（开发者可见）
// Child device record (developer-facing)
struct ThingBootChild {
    uint32_t id = 0;        // 子设备 ID
    char key[33] = "";      // 子设备键（32 字符 + \0）
    uint32_t active = 0;    // 最后活动时间（毫秒，millis 时基）
    bool online = false;    // 在线状态（由 SDK 按离线时限自动判定）
    char ext_str1[33] = ""; // 自定义字符串 1（如 IP 地址）
    char ext_str2[33] = ""; // 自定义字符串 2（预留）
    uint32_t ext_val1 = 0;  // 自定义整型 1（如 Zigbee 短地址）
    uint32_t ext_val2 = 0;  // 自定义整型 2（预留）
};

class ThingBootGateway {
private:
    ThingBootDevice* _device;

public:
    ThingBootGateway(ThingBootDevice* device = nullptr) : _device(device) {}

    // addon 安装（自由函数 tb_addon_gateway_install(maxChildren) 的成员转发版，完全等价，
    // 供编辑器提示发现；install 即角色，未链接 addon_gateway 库时不要调用。
    // maxChildren 为产品允许的最大子设备数，必须显式指定且大于 0）
    uint16_t install(uint16_t maxChildren) { return tb_addon_gateway_install(maxChildren); }

    // 添加子设备（已存在则刷新活动时间）。active 传 0 表示当前时间
    // Add a child (refreshes active time if it already exists). active=0 means now
    uint16_t addChild(uint32_t id, const char* key, uint32_t active = 0);

    // 查找子设备（按 ID 或按键），找到返回 true 并填充 child
    // Find a child by ID or by key; returns true and fills child on hit
    bool findChild(uint32_t id, ThingBootChild& child);
    bool findChild(const char* key, ThingBootChild& child);

    // 更新子设备活动时间（并置在线）
    // Update a child's active time (and mark it online)
    uint16_t updateChildActive(uint32_t id);

    // 更新子设备扩展字段（str1/str2/val1/val2 全部一并写入并持久化）
    // Update a child's extension fields (persisted). 20006=not found, 20004=driver missing
    uint16_t updateChildExt(uint32_t id, const char* str1, const char* str2, uint32_t val1, uint32_t val2);

    // 子设备列表：type 为 "all" / "online" / "offline"，返回 ID 数组
    // Child list: type is "all" / "online" / "offline", returns an ID array
    JSONVar childList(const char* type = "all");

    // 移除子设备
    // Remove a child
    uint16_t removeChild(uint32_t id);

    // 子设备数量
    // Number of children
    uint16_t countChildren();

    // 清空子设备表（恢复出厂/重新配网用）
    // Clear the child table (factory reset / re-commissioning)
    uint16_t clearChildren();

    // 判断子设备是否在线（最后活动时间在离线时限内）
    // Whether a child is online (last active time within the offline timeout)
    bool isChildOnline(uint32_t id);

    // 设定离线判定秒数（默认 60）：超过该秒数无活动判离线
    // Set the offline timeout in seconds (default 60)
    uint16_t setOfflineTimeout(uint16_t seconds);

    // 子设备命令回调：平台命令带 device 键时，网关查表命中后由此回调交给
    // 产品的传输层发送；子设备应答用 device.Message.publishMessage(data, id) 上行
    // Child order callback: when a platform order carries a device key and the child
    // is found in the table, this callback hands it to the product's transport;
    // uplink replies go through device.Message.publishMessage(data, id)
    uint16_t onChildOrder(std::function<void(uint32_t, SYS_TOPIC, const char*, JSONVar)> callback);

    // 子设备配置回调：平台配置消息（config 主题）带 device 键时，网关查表命中后
    // 由此回调交给产品的传输层发送（参数：子设备 ID、消息 mid、配置内容）
    // Child config callback: when a platform config message carries a device key,
    // this callback hands it to the product's transport (id, mid, data)
    uint16_t onChildConfig(std::function<void(uint32_t, const char*, JSONVar)> callback);

    // 候选设备入网上报（device_join 嵌套信封：data={gateway,name:"device_join",device:payload}，
    // 与平台监听服务（pusher parent.php）转发格式一致；仅上报候选，不入子设备表
    uint16_t reportDeviceJoin(JSONVar payload);

    // 平台 device_add 命令回调：要求绑定子设备（id/key/product/addr），
    // 产品在此执行传输层绑定与 addChild 入表；返回错误码（0=成功，SDK 按结果生成应答）
    uint16_t onDeviceAdd(std::function<uint16_t(uint32_t, const char*, uint32_t, uint32_t)> callback);

    // 平台 device_remove 命令回调：解绑子设备（id），返回错误码
    uint16_t onDeviceRemove(std::function<uint16_t(uint32_t)> callback);

    // 平台 device_clear 命令回调：清空全部绑定，返回错误码
    uint16_t onDeviceClear(std::function<uint16_t()> callback);

    // 平台 device_update 命令回调：更新子设备扩展信息（id, info），返回错误码
    uint16_t onDeviceUpdate(std::function<uint16_t(uint32_t, JSONVar)> callback);
};

#endif
