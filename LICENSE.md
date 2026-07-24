# ThingBoot Device SDK — License and Terms of Use

Copyright (c) 2026 芯步（ThingBoot）科技有限公司 / ThingBoot Technology Co., Ltd.  
All rights reserved.

---

## 1. Definitions

- **"SDK"** means the precompiled static libraries (`.a`), header files (`.h`), example code, scripts, and documentation provided in this repository.
- **"Licensed Device"** means a single hardware unit whose firmware links with the SDK and connects to the ThingBoot cloud platform.
- **"Licensee"** means the individual or entity downloading or using the SDK.
- **"Platform Access Service"** means the cloud-based device management, messaging, OTA, and other services provided by ThingBoot.

## 2. SDK Grant of License

ThingBoot grants Licensee a **non-exclusive, non-transferable, revocable, royalty-free license** to:

- Download and use the SDK for software development and firmware compilation.
- Link the SDK into firmware for hardware devices.
- Distribute firmware binaries that incorporate the SDK to end users.

The SDK itself is **free of charge**. There is no per-developer fee, no per-build fee, and no upfront license fee for using the SDK.

## 3. Platform Access Fee

When a device that includes the SDK connects to the **ThingBoot cloud platform**, a per-device Platform Access Service fee applies. This fee is separate from the SDK license and is billed according to the purchase agreement or platform subscription tier selected by Licensee.

- Each Licensed Device must be registered and activated on the ThingBoot platform.
- Unlicensed or unpaid devices may be refused connection or remotely disabled by the platform.
- Devices used in purely offline / LAN-only mode are not subject to the cloud Platform Access Service fee.

## 4. Restrictions

Licensee **shall not**:

- Decompile, disassemble, reverse engineer, or attempt to derive the source code of the SDK.
- Redistribute, sublicense, sell, lease, or transfer the SDK (in whole or in part) to any third party as a standalone library or development kit.
- Remove or alter any proprietary notices, copyright notices, or labels on the SDK.
- Use the SDK to develop competing IoT platforms, device-management clouds, or SDK products that replicate the core functions of the ThingBoot platform or SDK.
- Use the SDK in violation of any applicable law or regulation.

## 5. Ownership

The SDK and all intellectual property rights therein are and shall remain the exclusive property of ThingBoot. This Agreement does not convey any ownership interest or source-code rights.

## 6. Termination

ThingBoot may terminate this Agreement immediately if Licensee breaches any term. Upon termination, Licensee must cease all use of the SDK and destroy all copies.

## 7. Disclaimer & Limitation of Liability

THE SDK IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT. IN NO EVENT SHALL THINGBOOT BE LIABLE FOR ANY DAMAGES ARISING FROM THE USE OF THE SDK.

## 8. Governing Law

This Agreement shall be governed by the laws of the People's Republic of China.

## 9. Third-Party Software Notice

This SDK is built for the Espressif ESP-IDF platform and uses third-party open-source software. The proprietary license terms above apply **only to ThingBoot's own SDK code** (the precompiled static libraries, headers, examples, and scripts created by ThingBoot).

Third-party components — including but not limited to ESP-IDF and its bundled components — are governed by their own open-source licenses (Apache-2.0, MIT, BSD, LGPL, etc.). These licenses are independent of the commercial terms above.

**A complete list of third-party dependencies and their licenses is provided in `THIRD_PARTY_NOTICES.md`.** Licensee is responsible for ensuring compliance with all applicable third-party licenses in the final firmware.

ThingBoot does not claim that the entire SDK or any third-party component is released under the same proprietary terms. Nothing in this Agreement shall be construed as modifying or overriding the license terms of any third-party open-source software.

---

For licensing inquiries, contact: `license@thingboot.com`  
For technical support, contact: `support@thingboot.com`
