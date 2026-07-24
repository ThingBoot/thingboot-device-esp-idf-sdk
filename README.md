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

已实现（v1.1.0）：

- **Core 核心**：`getVersion`、`getSystemInfo`、`getDeviceID`、`getBenchID/setBenchID`、`getMasterID/setMasterID`、`getGatewayID/setGatewayID`、`getTimezone/setTimezone`、`getMode/setMode`、`restart`、`delay`、`millElapsed`、`setProduct`、`onSystemStateChange`、`onSystemProgress`、`onDebug`、`setup`、`loop`
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
