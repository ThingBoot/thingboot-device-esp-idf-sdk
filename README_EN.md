<p align="right">
  <a href="./README.md">中文</a> | English
</p>

<h1 align="center">ThingBoot Device SDK · ESP-IDF</h1>
<p align="center">ThingBoot Device SDK for ESP-IDF</p>
<p align="center"><b>Enterprise-grade free SDK for developers — works out of the box, zero learning curve</b></p>

---

> **Licensing & Billing**
>
> - The SDK is **free** for developers, distributed as a precompiled library (`.a` + headers), with no per-developer or per-build limits.
> - Each developer account gets **100 free device connections per year** — enough to cover a dev team's annual prototyping volume. Devices simply register on the ThingBoot Console.
> - Managing and controlling devices via the Open Platform API is metered and billed (mainly used by end customers; developers typically don't need it).
> - Fees apply only when a product enters **mass production**: the factory pays the platform access fee, plus optional Open Platform API usage fees.
> - With this policy, we hope to encourage developers to build and retrofit hardware products on the ThingBoot standard.
> - Redistribution, reverse engineering, or decompilation of the SDK in any form, or using it to develop competing products/platforms, is prohibited without authorization.

---

## Features

- **Full-stack connectivity**: built-in WiFi, Ethernet, 4G Cat.1 and WiFi Mesh
- **Direct platform connection**: out-of-the-box MQTT/HTTPS cloud connection with auto-reconnect and OTA
- **LAN services**: HTTP/TCP interfaces in LAN-only mode for offline local control
- **BLE provisioning & control**: BLE-assisted WiFi provisioning + BLE local control (orders / events / config)
- **Minimal hardware effort**: developers only write drivers for LEDs, relays, sensors; the platform-side thing model closes the loop
- **Unified cross-platform API**: highly consistent with the ThingBoot Arduino SDK, enabling low-cost migration of application code
- **Precompiled & closed-source**: distributed as `.a` static libraries + headers; source code is not open

## Capability Overview

- **Core**: `getVersion`, `getSystemInfo`, `getDeviceID`, `getBenchID/setBenchID`, `getMasterID/setMasterID`, `getGatewayID/setGatewayID`, `getTimezone/setTimezone`, `getMode/setMode`, `restart`, `delay`, `millElapsed`, `setProduct`, `setActiveCode`, `onSystemStateChange`, `onSystemProgress`, `onDebug`, `setup`, `loop`
- **Network**: `Network.getNetworkInfo`, `Network.connectWiFi` (multi/specific ssid), `Network.disconnectWiFi`, `Network.addWiFiConfig` (5 slots)/`updateWiFiConfig`/`deleteWiFiConfig`/`clearWiFiConfig`/`getWiFiConfig`, auto-reconnect, static IP
- **Platform connection**: device registration (reg/v3 signing protocol), MQTT connection (last will, QoS1 subscribe, auto-reconnect), uplink messages/downlink dispatch
- **NTP**: platform time sync (via registration + MQTT), timezone, `getTimestamp`/`getTimestampMs`/`getTimeString`
- **OTA**: platform OTA orders, signed download, flash verification, status reporting
- **Order**: `Order.onOrder`, `Order.replyMessage`
- **Event**: `Event.onAttributeChange`, `Event.setAttribute`, `Event.setAttributeDebounce`, `Event.reportEvent`
- **Message**: `Message.publishMessage`
- **State**: `State.onState`, `State.reportState`, `State.onFetch`
- **LAN services**: raw TCP HTTP service (AP config portal, private gateway API)
- **AP provisioning**: `TBC-<deviceID>` hotspot, HTTP config API (info/network/WiFi/restart)
- **Engineering hotspots**: safe/factory/test/debug/config scan & connect, factory activation, config pull
- **BLE provisioning & control**: wifi_provisioning BLE scheme (TBC-<deviceID> service name, PoP from activation code, tbd-config endpoint); NimBLE GATT control service (order write/event notify/config read+write), enable via Kconfig `CONFIG_TBD_BLE`
- **GSM/4G**: ML307 modem (esp_modem PPPoS, `Network.setGSMChip`/`setGSMSerialPort`/`tryConnectGSM`/`connectGSM`/`disconnectGSM`, enable via Kconfig `CONFIG_TBD_GSM`)
- **Ethernet**: W5500 SPI Ethernet (`Network.setEthernetPin`/`tryConnectEthernet`/`connectEthernet`/`disconnectEthernet`, enable via Kconfig `CONFIG_TBD_ETHER`)
- **Mesh**: ESP-NOW master/slave/gateway networking, discovery & binding (master find/bind), message bridging, channel management, mesh WiFi provisioning
- **Private deployment**: broker (MQTT credentials/topics/reg path override), gateway (HTTP sync response/uplink queue/heartbeat)
- **Peripheral**: `Peripheral.onInitPre`/`onInit`, `setDeviceBtn` (debounce/long-press)/`setSystemBtn` (system menu), `setDeviceLed`/`setSystemLed`, `ledOn`/`ledOff`/`ledToggle`/`ledBlink` family
- **Config**: `Config.addConfig`, `Config.readConfig`, `Config.saveConfig`, `Config.clearConfig`, `Config.resetConfig`, `Config.onConfig`
- **Timer**: `Timer.addTimer` (based on esp_timer)
- **JSON compatibility layer**: `JSONVar`/`JSON`/`null`, same usage as Arduino_JSON (cJSON based)
- **Utilities**: `CS`/`C`/`CN`/`CL`/`CAT`, `str_repeat`/`str_pad`/`str_find`/`str_ends_with`/`str_split`/`str2hex`/`hex2str`, `md5`, `mill_elapsed`, `rand_num`
- **Persistent storage**: ROM config area (NVS backend, 4096-byte layout, data-compatible with the Arduino version)

## Supported Platforms

| Platform | Status |
|------|------|
| ESP32 | ✅ Supported |
| ESP32-S3 | ✅ Supported |
| ESP32-C6 | ✅ Supported |
| ESP32-C3 | ✅ Supported |
| ESP32-S2 / C2 (ESP8684), etc. | Planned |

Precompiled libraries come in two layers, selected automatically via `IDF_TARGET`:

- **Base library** (always linked): `libthingboot_device_<chip>.a` — includes WiFi connectivity and all platform capabilities
- **Addon libraries** (linked on demand): `libthingboot_addon_net_<module>_<chip>.a`, modules: `ether` / `gsm` / `ble`

### Connectivity Addons

Ethernet / GSM / BLE are enabled on demand in two steps:

1. Enable `CONFIG_TBD_ETHER` / `CONFIG_TBD_GSM` / `CONFIG_TBD_BLE` in the project's `sdkconfig` (the component CMake links the matching addon library automatically);
2. Call the matching install function to register the driver before `device.setup()` (member-style calls are equivalent wrappers of the free functions `tb_addon_net_*_install()`):

```cpp
device.Network.installEthernet();  // Ethernet (W5500)
device.Network.installGSM();       // GSM/4G (ML307)
device.Network.installBLE();       // BLE provisioning + control
```

Calling the related `Network` APIs without an installed driver returns `ERR_NETWORK_DRIVER_MISSING` (20002).

### Gateway Addon

For gateway products (child device table maintenance + platform message forwarding, transport-agnostic): enable `CONFIG_TBD_GATEWAY` and call `device.Gateway.install()` before `device.setup()` (a wrapper of the free function `tb_addon_gateway_install()`; install declares the role), then register the child order callback via `device.Gateway.onChildOrder()`. See the "Gateway" chapter of the official documentation.

## Quick Start

### Option 1: As an ESP-IDF Component (Recommended)

#### 1. Add the component

In your ESP-IDF project, add it as a git submodule:

```bash
cd your-project
git submodule add https://github.com/ThingBoot/thingboot-device-esp-idf-sdk.git components/thingboot-device-esp-idf-sdk
```

Or point `EXTRA_COMPONENT_DIRS` to this repository in your project's root `CMakeLists.txt`:

```cmake
set(EXTRA_COMPONENT_DIRS "/path/to/thingboot-device-esp-idf-sdk")
```

#### 2. Include the header

```cpp
#include "ThingBootSDK.h"
```

#### 3. Write the application

```cpp
ThingBootDevice device;

extern "C" void app_main(void)
{
    printf("ThingBoot SDK version: %s\n", device.getVersion().c_str());
}
```

#### 4. Build

```bash
idf.py build
```

> **Note (task stack sizes)**: ESP-IDF defaults the main task / esp_timer task stacks
> to only 3584 bytes, which is too small for this SDK (C++ call chains + JSON/HTTP work)
> and will crash at startup (stack overflow). Add to your project's `sdkconfig.defaults`
> (already included in this repo's examples):
>
> ```ini
> CONFIG_ESP_MAIN_TASK_STACK_SIZE=8192
> CONFIG_ESP_TIMER_TASK_STACK_SIZE=8192
> ```

### Option 2: PlatformIO

In your project's `platformio.ini`:

```ini
[env:esp32]
platform = espressif32
board = esp32dev
framework = espidf
```

Place this repository under your project's `components/` directory (or configure `EXTRA_COMPONENT_DIRS` as in Option 1), then run `pio run`.

See the full example in [examples/GetVersion](examples/GetVersion).

## API Compatibility Notes

This SDK is highly consistent with the ThingBoot Arduino SDK. The only differences are platform-imposed:

| Item | Arduino | ESP-IDF |
|---|---|---|
| String type | `String` (Arduino) | `std::string` (C++ standard library) |
| Millisecond timing | `millis()` | `tb_millis()` |
| Serial port selection | `HardwareSerial` reference | `uart_num` port number |
| Connectivity extensions | Compile-time variant macros | Addon libraries + runtime install (see above) |

See the official documentation for the full list.

## Directory Structure

```plain
thingboot-device-esp-idf-sdk/
├── CMakeLists.txt              # ESP-IDF component registration (links prebuilt library)
├── idf_component.yml           # IDF component manager manifest
├── include/
│   ├── ThingBootSDK.h          # Public API header
│   └── ThingBootSDK/           # Public headers split by module
├── lib/
│   ├── libthingboot_device_<chip>.a          # Base precompiled library (always linked)
│   └── libthingboot_addon_net_<module>_<chip>.a # Addon libraries (ether/gsm/ble, on demand)
├── examples/
│   └── GetVersion/             # Minimal example project
├── VERSION
├── README.md
├── README_EN.md
├── LICENSE.md
└── THIRD_PARTY_NOTICES.md
```

## Third-Party Open Source Notice

This SDK is built on the following open source projects, whose licenses are independent of the SDK's commercial terms:

| Project | Repository | License |
|---|---|---|
| ESP-IDF | https://github.com/espressif/esp-idf | Apache-2.0 |

See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md) for details. You are responsible for ensuring your final firmware complies with the licenses of all open source components used.

## Licensing & Billing

- **Free SDK**: free to download, compile and develop with; no per-developer or per-build limits.
- **100 free devices per year**: each developer account can connect 100 devices per year at no charge (covers prototyping volume); register devices on the [ThingBoot Console](https://console.thingboot.com).
- **Production-stage billing**: once a product enters mass production, the factory pays the platform access fee; Open Platform API usage (optional, mainly for end customers) is metered separately.
- **Purchase & inquiries**: contact `license@thingboot.com` or purchase via the ThingBoot Console.

## Technical Support

- Technical support: `support@thingboot.com`
- Licensing: `license@thingboot.com`
- Documentation: [docs.thingboot.com](https://www.thingboot.com/document/fb9d5f99e09c8673/)

---

**Copyright © 2026 ThingBoot Technology Co., Ltd. All rights reserved.**
