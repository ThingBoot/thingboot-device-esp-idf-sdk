<p align="right">
  <a href="./README.md">中文</a> | English
</p>

<h1 align="center">ThingBoot Device SDK · ESP-IDF</h1>
<p align="center">ThingBoot Device SDK for ESP-IDF — Embedded IoT Development Library</p>

---

> **Licensing & Billing**
>
> - The SDK itself is **free of charge**, distributed as a precompiled closed-source library (`.a` + headers).
> - No license fees, no per-developer limits, no per-build limits.
> - When a device built with this SDK **connects to the ThingBoot cloud platform**, a per-device Platform Access Service fee applies.
> - Redistribution, reverse engineering, or decompilation of the SDK in any form, or using it to develop competing products/platforms, is prohibited without authorization.

---

## Current Status

This repository is the ESP-IDF port of the Arduino-based [thingboot-device-esp-arduino-sdk](https://github.com/ThingBoot/thingboot-device-esp-arduino-sdk). Porting is in progress.

Implemented (v1.3.0):

- **Core**: `getVersion`, `getSystemInfo`, `getDeviceID`, `getBenchID/setBenchID`, `getMasterID/setMasterID`, `getGatewayID/setGatewayID`, `getTimezone/setTimezone`, `getMode/setMode`, `restart`, `delay`, `millElapsed`, `setProduct`, `onSystemStateChange`, `onSystemProgress`, `onDebug`, `setup`, `loop`
- **Network**: `Network.getNetworkInfo`, `Network.connectWiFi` (multi/specific ssid), `Network.disconnectWiFi`, `Network.addWiFiConfig` (5 slots)/`updateWiFiConfig`/`deleteWiFiConfig`/`clearWiFiConfig`/`getWiFiConfig`, auto-reconnect, static IP
- **Config**: `Config.addConfig`, `Config.readConfig`, `Config.saveConfig`, `Config.clearConfig`, `Config.resetConfig`, `Config.onConfig`
- **Timer**: `Timer.addTimer` (based on esp_timer)
- **JSON compatibility layer**: `JSONVar`/`JSON`/`null`, same usage as Arduino_JSON (cJSON based)
- **Utilities**: `CS`/`C`/`CN`/`CL`/`CAT`, `str_repeat`/`str_pad`/`str_find`/`str_ends_with`/`str_split`/`str2hex`/`hex2str`, `md5`, `mill_elapsed`, `rand_num`
- **Persistent storage**: ROM config area (NVS backend, layout-compatible with the Arduino version's 4096-byte map)

Remaining interfaces (networking, platform connection, config, orders, events, messaging, peripherals, etc.) will be ported incrementally, keeping the API highly consistent with the Arduino version.

## Features (Planned)

- **Full-stack connectivity**: built-in WiFi, Ethernet, 4G Cat.1 and WiFi Mesh
- **Direct platform connection**: out-of-the-box MQTT/HTTPS cloud connection with auto-reconnect and OTA
- **LAN services**: HTTP/TCP interfaces in LAN-only mode for offline local control
- **Minimal hardware effort**: developers only write drivers for LEDs, relays, sensors; the platform-side thing model closes the loop
- **Consistent API**: highly consistent with the Arduino SDK, enabling low-cost migration of application code
- **Precompiled & closed-source**: distributed as `.a` static libraries + headers; source code is not open

## Supported Platforms

| Platform | Status |
|------|------|
| ESP32 | ✅ Build verified |
| ESP32-S2 / S3 / C3 / C6, etc. | Planned |

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

## API Differences from the Arduino Version

The API is highly consistent with the Arduino version. The only differences are platform-imposed:

| Item | Arduino | ESP-IDF |
|---|---|---|
| String type | `String` (Arduino) | `std::string` (C++ standard library) |

## Directory Structure

```plain
thingboot-device-esp-idf-sdk/
├── CMakeLists.txt              # ESP-IDF component registration (links prebuilt library)
├── idf_component.yml           # IDF component manager manifest
├── include/
│   ├── ThingBootSDK.h          # Public API header
│   └── ThingBootSDK/           # Public headers split by module
├── lib/
│   └── libthingboot_device_esp32.a   # Precompiled closed-source library (per chip)
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
- **Per-device billing**: a platform service fee applies per device connected to the ThingBoot cloud platform.
- **Device onboarding**: register devices on the [ThingBoot Console](https://console.thingboot.com).
- **Purchase & inquiries**: contact `license@thingboot.com` or purchase via the ThingBoot Console.

## Technical Support

- Technical support: `support@thingboot.com`
- Licensing: `license@thingboot.com`
- Documentation: [docs.thingboot.com](https://www.thingboot.com/document/fb9d5f99e09c8673/)

---

**Copyright © 2026 ThingBoot Technology Co., Ltd. All rights reserved.**
