<p align="right">
  <a href="./README_EN.md">English</a> | 中文
</p>

<h1 align="center">芯步设备 SDK · ESP-IDF 版</h1>
<p align="center">ThingBoot Device SDK for ESP-IDF</p>
<p align="center"><b>面向开发者的企业级免费 SDK —— 开箱即用，零学习成本</b></p>

---

> **授权与计费说明**
>
> - 本 SDK **免费**向开发者开放，以预编译库（`.a` + 头文件）形式分发，不限开发人数、不限编译次数。
> - 每个开发者帐号每年享有 **100 台设备免费接入额度**——几乎覆盖一个开发者团队全年产品开发涉及的样机量；设备在芯步控制台注册即可接入。
> - 通过开放平台调用 API 管理和控制设备按量收费（该部分主要面向终端客户，开发者通常无需使用）。
> - 仅在产品进入**量产阶段**时，才向工厂收取平台接入费，以及开放平台接口调用费（可选）。
> - 我们希望通过这个措施，鼓励开发者使用芯步标准来开发和改造硬件产品。
> - 未经授权，禁止以任何形式再分发、逆向工程、反编译本 SDK，或基于本 SDK 开发同类产品/平台。

---

## 特性

- **全栈网络接入**：内置 WiFi、以太网、4G Cat.1 及 WiFi Mesh 组网
- **平台直连**：开箱即用的 MQTT/HTTPS 平台连接，支持自动重连与 OTA 升级
- **局域网服务**：纯局域网模式下开放 HTTP/TCP 接口，支持无网本地控制
- **BLE 配网与控制**：蓝牙辅助配网 + 蓝牙本地控制（命令下发 / 事件上报 / 配置读写）
- **硬件极简**：开发者仅需编写 LED、继电器、传感器等硬件驱动，平台端定义物模型即可完成功能闭环
- **跨平台接口统一**：与芯步 Arduino 版 SDK 接口高度一致，应用代码可低成本跨平台迁移
- **预编译闭源**：以 `.a` 静态库 + 头文件分发，源码不开放

## 功能概览

### 接入与配网

- **WiFi 联网**：多候选连接（5 个候选 + 隐藏热点）、断线自动重连、僵尸热点（能连但无外网）识别与换网
- **AP 配网**：未配置时自动开放 `TBC-<设备ID>` 热点 + HTTP 配置接口，手机直连即配
- **BLE 配网与控制**（ESP-IDF 版）：蓝牙辅助配网 + 蓝牙本地控制（命令下发 / 事件上报 / 配置读写）
- **工程热点**：safe / factory / test / debug / config 五类工程热点自动识别——工厂激活、产线测试、开发调试零代码接入

### 网络形态

- **WiFi**：base 库内置，开箱即用
- **以太网 / GSM / BLE**：addon 按需启用（W5500 SPI 以太网、ML307 4G Cat.1）
- **WiFi Mesh 组网**：ESP-NOW 主从 / 网关、发现绑定（find/bind）、消息桥接、信道管理

### 平台连接

- **注册与激活**：reg/v4 签名协议、激活码校验、工作台归属
- **MQTT**：8 个下行主题订阅、遗嘱消息、QoS1、断线自动重连、上下行报文组包与分发
- **物模型**：命令（Order）/ 事件（Event）/ 状态（State）/ 配置（Config）全链路
- **OTA 升级**：三段式流程（签名下载 → 魔数预检烧写 → 重启 → 注册时上报结果），失败自动重试
- **NTP 对时**：注册顺带 + MQTT 请求双通路，时区管理

### 本地与私有化

- **局域网服务**：纯局域网模式开放 HTTP/TCP 接口，**无网也可本地控制**
- **私有化部署**：私有 broker（MQTT 参数 / 主题 / 注册路径替换）、私有网关（HTTP 同步应答 / 心跳）

### 网关（addon）

- **子设备表**：ID / 键 / 活动时间维护，持久化存储，在线状态自动判定（可配时限）
- **消息转发**：平台命令按子设备查表转发到产品传输层（RF / RS485 / Zigbee 等自定），子设备消息经网关上行
- **平台一致性**：变更即上报（增删 / 上下线事件）、上线即对账、平台增删查管理原语，SDK 内置零实现

### 开发体验

- **addon 模型**：base 库必链 + addon 按需追加（ether / gsm / ble / gateway），`install()` 即启用
- **调试日志**：全库恒带，`device.onDebug()` 注册即输出，按模块分类过滤，无需编译开关
- **外设框架**：按钮消抖 / 长按系统菜单（5s 配网 / 7s 安全模式）、LED 三态状态机
- **配置体系**：Config 声明式配置项（默认值 / 范围校验 / 配网与平台可读写）
- **工具链**：JSON 兼容层（Arduino_JSON 用法）、Timer 定时器、全量错误码、异常解码友好的启动日志

## 支持平台

| 平台 | 状态 |
|------|------|
| ESP32 | ✅ 支持 |
| ESP32-S3 | ✅ 支持 |
| ESP32-C6 | ✅ 支持 |
| ESP32-C3 | ✅ 支持 |
| ESP32-S2 / C2（ESP8684）等 | 计划支持 |

预编译库分两层，按 `IDF_TARGET` 自动选择：

- **base 库**（必链）：`libthingboot_device_<芯片>.a`，内含 WiFi 联网与全部平台能力
- **addon 库**（按需追加）：`libthingboot_addon_net_<模块>_<芯片>.a`，模块为 `ether` / `gsm` / `ble`；网关为 `libthingboot_addon_gateway_<芯片>.a`

### 联网扩展（addon）

以太网 / GSM / BLE 以 addon 形式按需启用，两步：

1. 在工程 `sdkconfig` 中打开 `CONFIG_TBD_ETHER` / `CONFIG_TBD_GSM` / `CONFIG_TBD_BLE`（组件 CMake 自动追加链接对应 addon 库）；
2. 在 `device.setup()` 之前调用对应安装函数注册驱动（成员写法为自由函数 `tb_addon_net_*_install()` 的转发版，等价）：

```cpp
device.Network.installEthernet();  // 以太网（W5500）
device.Network.installGSM();       // GSM/4G（ML307）
device.Network.installBLE();       // BLE 配网 + 控制
```

未安装驱动时调用相关 `Network` 接口返回 `ERR_NETWORK_DRIVER_MISSING`（20002）。

### 网关（addon）

网关类产品（子设备表维护 + 平台消息转发，与传输层无关）：开启 `CONFIG_TBD_GATEWAY`，并在 `device.setup()` 前调用 `device.Gateway.install()`（自由函数 `tb_addon_gateway_install()` 的转发版；install 即角色），再用 `device.Gateway.onChildOrder()` 注册子设备命令回调。详见官方文档「网关」章节。

## 快速开始

> **环境要求**：ESP-IDF **≥ 5.1**（已在 5.5.1 验证；ESP32-C6/C2 等新型号需 ≥ 5.1）。
> 低于 5.1 的版本不受支持（SDK 使用了 5.x 的 esp-mqtt / ESP-NOW / TWDT 等接口）。

### 方式一：作为 ESP-IDF 组件引入（推荐）

#### 1. 添加组件

在你的 ESP-IDF 工程中，以 git submodule 方式引入：

```bash
cd your-project
git submodule add https://github.com/ThingBoot/thingboot-device-esp-idf-sdk.git components/thingboot-device-esp-idf-sdk
```

或者在工程根目录的 `CMakeLists.txt` 中通过 `EXTRA_COMPONENT_DIRS` 指向本仓库：

```cmake
set(EXTRA_COMPONENT_DIRS "/path/to/thingboot-device-esp-idf-sdk")
```

#### 2. 包含头文件

```cpp
#include "ThingBootSDK.h"
```

#### 3. 编写应用

```cpp
ThingBootDevice device;

extern "C" void app_main(void)
{
    printf("ThingBoot SDK version: %s\n", device.getVersion().c_str());
}
```

#### 4. 编译

```bash
idf.py build
```

> **注意（任务栈大小）**：ESP-IDF 默认主任务/esp_timer 任务栈仅 3584 字节，
> 不足以运行本 SDK（C++ 调用链 + JSON/HTTP 操作），会导致启动崩溃（栈溢出）。
> 请在工程的 `sdkconfig.defaults` 中加入（本仓库示例工程已内置）：
>
> ```ini
> CONFIG_ESP_MAIN_TASK_STACK_SIZE=8192
> CONFIG_ESP_TIMER_TASK_STACK_SIZE=8192
> ```

### 方式二：PlatformIO

在项目的 `platformio.ini` 中：

```ini
[env:esp32]
platform = espressif32
board = esp32dev
framework = espidf
```

将本仓库放入工程的 `components/` 目录（或按方式一配置 `EXTRA_COMPONENT_DIRS`），然后执行 `pio run`。

完整示例见 [examples/GetVersion](examples/GetVersion)。

## 接口兼容性说明

本 SDK 与芯步 Arduino 版 SDK 接口高度一致，仅存在以下平台差异：

| 差异点 | Arduino 版 | ESP-IDF 版 |
|---|---|---|
| 字符串类型 | `String`（Arduino） | `std::string`（C++ 标准库） |
| 毫秒计时 | `millis()` | `tb_millis()` |
| 串口指定 | `HardwareSerial` 引用 | `uart_num` 端口号 |
| 联网扩展 | 编译期变体宏 | addon 库 + 运行期安装（见上文） |

完整差异说明见官方文档。

## 目录结构

```plain
thingboot-device-esp-idf-sdk/
├── CMakeLists.txt              # ESP-IDF 组件注册（链接预编译库）
├── idf_component.yml           # IDF 组件管理器清单
├── include/
│   ├── ThingBootSDK.h          # 公共 API 头文件
│   └── ThingBootSDK/           # 按模块拆分的公共头文件
├── lib/
│   ├── libthingboot_device_<芯片>.a          # base 预编译闭源库（必链）
│   └── libthingboot_addon_net_<模块>_<芯片>.a # addon 库（ether/gsm/ble 按需）
├── examples/
│   └── GetVersion/             # 最小示例工程
├── VERSION
├── README.md
├── README_EN.md
├── LICENSE.md
└── THIRD_PARTY_NOTICES.md
```

## 第三方开源软件声明

本 SDK 基于以下开源项目构建，其授权协议独立于本 SDK 的商业条款：

| 项目 | 仓库 | 许可证 |
|---|---|---|
| ESP-IDF | https://github.com/espressif/esp-idf | Apache-2.0 |

详见 [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md)。用户需确保最终固件符合所使用开源组件的许可证要求。

## 授权与计费

- **SDK 免费开放**：开发者可免费下载、编译、开发，不限开发人数和编译次数。
- **每年 100 台免费接入**：每个开发者帐号每年可免费接入 100 台设备（覆盖开发样机量），设备在 [芯步控制台](https://console.thingboot.com) 注册即可接入。
- **量产阶段计费**：产品进入量产阶段后，由工厂支付平台接入费；开放平台 API 调用（可选，主要面向终端客户）按量计费。
- **购买与咨询**：联系 `license@thingboot.com` 或通过芯步控制台。

## 技术支持

- 技术支持：`support@thingboot.com`
- 销售授权：`license@thingboot.com`
- 官方文档：[docs.thingboot.com](https://www.thingboot.com/document/fb9d5f99e09c8673/)

---

**版权所有 © 2026 芯步（ThingBoot）科技有限公司。保留所有权利。**
