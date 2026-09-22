#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "ThingBootSDK.h"

ThingBootDevice device;

extern "C" void app_main(void)
{
    //调试信息打印
    device.onDebug([](const char* category, const char* message) {
        printf("[%s] %s\n", category, message);
    });

    //产品信息
    device.setProduct("product_key", "product_secret", "board", "esp32", "1.0.0");

    //在开发阶段，请打开下面的链接免费获取设备接入激活码
    //在量产阶段，烧录工具软件将自动写入激活码。所以量产后可注释下方代码（或者不理会）
    //please open the link to generate a active code for this device
    //https://www.thingboot.com/developer/center/access/
    device.setActiveCode("xxxxxxxxxxxxx");

    //配置 WiFi 热点（5 槽位，SSID 以 hex 编码存储于 NVS）
    device.Network.addWiFiConfig("your-ssid", "your-password");

    //系统初始化：wifi_init + network_setup，自动连接已配置热点
    device.setup();

    //当前网络信息
    printf("network info: %s\n", device.Network.getNetworkInfo().c_str());

    //已保存的 WiFi 配置
    printf("wifi config: %s\n", device.Network.getWiFiConfig().c_str());

    while (true)
    {
        device.loop();  // 网络检查与自动重连
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
