// 获取 SDK 版本号
// Get SDK version string
std::string getVersion();

// 获取系统信息（JSON 字符串）
// Get system information as JSON string
std::string getSystemInfo();

// 获取设备 ID
// Get device ID
uint32_t getDeviceID();

// 获取工作台 ID
// Get bench ID
uint16_t getBenchID();

// 设置工作台 ID
// Set bench ID
uint16_t setBenchID(uint16_t benchID);

// 获取主设备 ID
// Get master device ID
uint32_t getMasterID();

// 设置主设备 ID
// Set master device ID
uint16_t setMasterID(uint32_t masterDeviceID);

// 获取网关设备 ID
// Get gateway device ID
uint32_t getGatewayID();

// 设置网关设备 ID
// Set gateway device ID
uint16_t setGatewayID(uint32_t gatewayDeviceID);

// 获取时区
// Get timezone
std::string getTimezone();

// 设置时区
// Set timezone
uint16_t setTimezone(const char* timezone);

// 获取当前运行模式
// Get current running mode
std::string getMode();

// 设置运行模式
// Set running mode
uint16_t setMode(const char* mode);

// 重启设备
// Restart device
uint16_t restart(uint32_t delay_ms = 0);

// 延时指定毫秒数
// Delay for the specified milliseconds
void delay(uint32_t ms);

// 计算从某个 tb_millis() 时间点到当前时刻经过的毫秒数
// Calculate elapsed milliseconds since a given tb_millis() timestamp
uint32_t millElapsed(uint32_t since);

// 获取当前时间戳（秒）
// Get current timestamp in seconds
uint32_t getTimestamp();

// 获取当前时间戳（毫秒）
// Get current timestamp in milliseconds
uint64_t getTimestampMs();

// 获取格式化后的当前时间字符串
// Get formatted current time string
std::string getTimeString(const char* format = "%Y-%m-%d %H:%M:%S");

// 设置产品信息
// Set product information
uint16_t setProduct(const char* key, const char* secret,
    const char* board, const char* mcu, const char* firmware);

// 设置激活码（设备未激活时，注册激活接口的 code 参数；需在 setup() 前调用）
// Set activation code (the code parameter of the activation request for
// inactive devices; call before setup())
uint16_t setActiveCode(const char* code);

// 系统状态变化回调
// System state change callback
uint16_t onSystemStateChange(
    std::function<void(SYS_STATE current, SYS_STATE previous)> callback);

// 系统初始化进度变化回调
// System initialization progress change callback
uint16_t onSystemProgress(
    std::function<void(const char* desc, float progress)> callback);

// 设置调试日志回调
// Set debug log callback
uint16_t onDebug(
    std::function<void(const char* category, const char* message)> callback);

// 系统初始化
// Initialize system
void setup();

// 系统主循环，需在 app_main 的任务循环中调用
// System main loop, call in the app_main task loop
void loop();
