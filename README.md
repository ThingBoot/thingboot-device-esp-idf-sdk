<p align="right">
  <a href="./README_EN.md">English</a> | 中文
</p>

<h1 align="center">芯步设备 SDK · ESP-IDF 版</h1>
<p align="center">ThingBoot Device SDK for ESP-IDF — 嵌入式物联网开发库</p>

---

> **授权与计费说明**
>
> - 本 SDK **本身免费**向开发者提供，以预编译闭源库（`.a` + 头文件）形式分发。
> - SDK 不收取任何授权费用、不限开发人数、不限编译次数。
> - 当设备通过本 SDK **连接芯步（ThingBoot）云平台**时，按接入设备数量收取平台接入服务费。
> - 未经授权，禁止以任何形式再分发、逆向工程、反编译本 SDK，或基于本 SDK 开发同类产品/平台。

---

## 当前状态

本仓库为 Arduino 版 [thingboot-device-esp-arduino-sdk](https://github.com/ThingBoot/thingboot-device-esp-arduino-sdk) 的 ESP-IDF 移植版本，正在分阶段移植中。

已实现（v1.10.0）：

- **Core 核心**：`getVersion`、`getSystemInfo`、`getDeviceID`、`getBenchID/setBenchID`、`getMasterID/setMasterID`、`getGatewayID/setGatewayID`、`getTimezone/setTimezone`、`getMode/setMode`、`restart`、`delay`、`millElapsed`、`setProduct`、`onSystemStateChange`、`onSystemProgress`、`onDebug`、`setup`、`loop`
- **Network 网络**：`Network.getNetworkInfo`、`Network.connectWiFi`（multi/指定 ssid）、`Network.disconnectWiFi`、`Network.addWiFiConfig`（5 槽位）/`updateWiFiConfig`/`deleteWiFiConfig`/`clearWiFiConfig`/`getWiFiConfig`、自动重连、静态 IP
- **平台连接**：设备注册（reg/v3 签名协议）、MQTT 连接（遗嘱、QoS1 订阅、自动重连）、上行报文/下行分发
- **NTP 对时**：平台双通路对时（注册顺带 + MQTT 请求）、时区、`getTimestamp`/`getTimestampMs`/`getTimeString`
- **OTA 升级**：平台 OTA 命令、签名下载、烧写校验、状态上报、三段式流程
- **Order 命令**：`Order.onOrder`、`Order.replyMessage`
- **Event 事件**：`Event.onAttributeChange`、`Event.setAttribute`、`Event.setAttributeDebounce`、`Event.reportEvent`
- **Message 消息**：`Message.publishMessage`、`Message.onDeviceMessageReceive`
- **State 状态**：`State.onState`、`State.reportState`、`State.onFetch`
- **LAN 服务**：裸 TCP HTTP 服务（AP 配网接口、私有化网关接口）
- **AP 配网**：`TBC-<设备ID>` 热点、HTTP 配置接口（设备信息/网络/WiFi/重启）
- **工程热点**：safe/factory/test/debug/config 扫描识别、工厂激活、配置下发
- **GSM/4G**：ML307 模组（esp_modem PPPoS，`Network.setGSMChip`/`setGSMSerialPort`/`tryConnectGSM`/`connectGSM`/`disconnectGSM`，Kconfig `CONFIG_TBD_GSM` 启用变体库）
- **以太网**：W5500 SPI 以太网（`Network.setEthernetPin`/`tryConnectEthernet`/`connectEthernet`/`disconnectEthernet`，Kconfig `CONFIG_TBD_ETHER` 启用变体库）
- **Mesh 组网**：ESP-NOW 主从/网关组网、发现绑定（master find/bind）、消息桥接、信道管理、mesh 配网求助
- **私有化**：broker（MQTT 参数/主题/注册路径替换）、gateway（HTTP 同步应答/上行队列/心跳）
- **Peripheral 外设**：`Peripheral.onInitPre`/`onInit`、`setDeviceBtn`（消抖/长按）/`setSystemBtn`（系统菜单）、`setDeviceLed`/`setSystemLed`、`ledOn`/`ledOff`/`ledToggle`/`ledBlink` 系列
- **Config 配置**：`Config.addConfig`、`Config.readConfig`、`Config.saveConfig`、`Config.clearConfig`、`Config.resetConfig`、`Config.onConfig`
- **Timer 定时器**：`Timer.addTimer`（基于 esp_timer）
- **JSON 兼容层**：`JSONVar`/`JSON`/`null`，与 Arduino_JSON 用法一致（cJSON 实现）
- **工具函数**：`CS`/`C`/`CN`/`CL`/`CAT`、`str_repeat`/`str_pad`/`str_find`/`str_ends_with`/`str_split`/`str2hex`/`hex2str`、`md5`、`mill_elapsed`、`rand_num`
- **持久化存储**：ROM 配置区（NVS 后端，与 Arduino 版 4096 字节布局兼容）

其余接口（网络、平台连接、配置、命令、事件、消息、外设等）将陆续移植，接口形态与 Arduino 版保持高度一致。

## 特性（规划）

- **全栈网络接入**：内置 WiFi、以太网、4G Cat.1 及 WiFi Mesh 组网
- **平台直连**：开箱即用的 MQTT/HTTPS 平台连接，支持自动重连与 OTA 升级
- **局域网服务**：纯局域网模式下开放 HTTP/TCP 接口，支持无网本地控制
- **硬件极简**：开发者仅需编写 LED、继电器、传感器等硬件驱动，平台端定义物模型即可完成功能闭环
- **接口一致**：与 Arduino 版 SDK 接口高度一致，应用代码可低成本迁移
- **预编译闭源**：以 `.a` 静态库 + 头文件分发，源码不开放

## 支持平台

| 平台 | 状态 |
|------|------|
| ESP32 | ✅ 编译验证通过 |
| ESP32-S2 / S3 / C3 / C6 等 | 计划支持 |

## 快速开始

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

## 与 Arduino 版的接口差异

接口函数与 Arduino 版保持高度一致，仅存在以下因平台能力导致的差异：

| 差异点 | Arduino 版 | ESP-IDF 版 |
|---|---|---|
| 字符串类型 | `String`（Arduino） | `std::string`（C++ 标准库） |

## 目录结构

```plain
thingboot-device-esp-idf-sdk/
├── CMakeLists.txt              # ESP-IDF 组件注册（链接预编译库）
├── idf_component.yml           # IDF 组件管理器清单
├── include/
│   ├── ThingBootSDK.h          # 公共 API 头文件
│   └── ThingBootSDK/           # 按模块拆分的公共头文件
├── lib/
│   └── libthingboot_device_esp32.a   # 预编译闭源库（按芯片区分）
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

- **SDK 本身免费**：开发者可免费下载、编译、开发，不限制开发人数和编译次数。
- **按设备接入计费**：设备通过本 SDK 连接芯步云平台时，按接入设备数量收取平台服务费。
- **设备接入方式**：设备在 [芯步控制台](https://console.thingboot.com) 注册并接入。
- **购买与咨询**：联系 `license@thingboot.com` 或通过芯步控制台购买。

## 技术支持

- 技术支持：`support@thingboot.com`
- 销售授权：`license@thingboot.com`
- 官方文档：[docs.thingboot.com](https://www.thingboot.com/document/fb9d5f99e09c8673/)

---

**版权所有 © 2026 芯步（ThingBoot）科技有限公司。保留所有权利。**
