# Third-Party Notices

ThingBoot Device SDK for ESP-IDF（以下简称"本 SDK"）在编译和运行过程中依赖若干第三方开源项目。
本文件用于说明这些依赖及其许可证信息，方便最终开发者在固件中遵守相应的开源许可义务。

> **免责声明**：本文件仅作技术信息汇总，不构成法律意见。具体的许可证合规要求请咨询专业律师。

---

## 1. 平台/框架依赖

本 SDK 面向乐鑫 ESP-IDF 平台开发，最终固件会链接到 ESP-IDF 框架及其内置组件。

| 项目 | 仓库 | 许可证 | 用途 |
|---|---|---|---|
| ESP-IDF | https://github.com/espressif/esp-idf | Apache-2.0（部分组件为 MIT/BSD/LGPL/GPL，详见其仓库许可说明） | ESP32 系列芯片物联网开发框架 |

> **说明**：本 SDK 本身没有复制或修改 ESP-IDF 的源代码，仅通过 `#include` 使用其公共头文件，并在编译时由 ESP-IDF 构建系统（CMake）链接到对应框架组件。

---

## 2. 本 SDK 直接依赖的库

当前版本除 ESP-IDF 框架本身外，未直接依赖或打包其他第三方库。

后续版本如引入新的第三方依赖，将在此文件中列出其名称、仓库与许可证。

---

## 3. 最终固件开发者的义务

- ESP-IDF 中包含少量 LGPL/GPL 许可的组件（如部分库），最终产品固件的开发者应遵守相应许可证关于源代码/对象文件提供、许可声明、修改告知等义务。
- ThingBoot 仅提供 SDK 层面的依赖信息，最终固件的合规责任由最终开发者承担。

---

## 4. 许可证原文链接

- Apache-2.0: https://www.apache.org/licenses/LICENSE-2.0
- MIT: https://opensource.org/licenses/MIT
- LGPL-2.1: https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
- LGPL-3.0: https://www.gnu.org/licenses/lgpl-3.0.html
- GPL-3.0: https://www.gnu.org/licenses/gpl-3.0.html
