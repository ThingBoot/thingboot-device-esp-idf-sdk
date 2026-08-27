#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "ThingBootSDK.h"

ThingBootDevice device;

//调试信息打印回调
void onDebug(const char* category, const char* message)
{
    printf("[%s] %s\n", category, message);
}

//命令回调
void onOrder(const char* mid, JSONVar data)
{
    printf("order mid=%s data=%s\n", mid, JSON.stringify(data).c_str());
    device.Order.replyMessage(mid, "{\"result\":\"ok\"}");
}

extern "C" void app_main(void)
{
    //调试信息打印
    device.onDebug(onDebug);

    //产品信息，请到芯步产品中心定义和查看
    device.setProduct(
        "your-product-key",    //产品代号[Key]
        "your-product-secret", //产品密码[Secret]
        "board",               //适配PCB板，自由定义
        "esp32",               //适配MCU
        "1.0.0"                //当前固件版本号
    );

    //在开发阶段，请打开下面的链接免费获取设备接入激活码
    //在量产阶段，烧录工具软件将自动写入激活码。所以量产后可注释下方代码（或者不理会）
    //please open the link to generate a active code for this device
    //https://www.thingboot.com/developer/center/access/
    device.setActiveCode("xxxxxxxxxxxxx");

    //配置 WiFi
    device.Network.addWiFiConfig("your-ssid", "your-password");

    //注册平台命令回调
    device.Order.onOrder(onOrder);

    //设备状态获取回调（每次上线后 SDK 拉取并上报）
    device.State.onFetch([]() -> JSONVar {
        JSONVar state;
        state["power"] = "1";
        return state;
    });

    //定时状态上报（每 60 秒）
    device.State.onState("heartbeat", 60, [](const char* name) {
        device.State.reportState(name, "{\"alive\":1}");
    });

    //系统初始化：连网 → 注册平台 → 连接 MQTT
    device.setup();

    //NTP 对时（平台注册时顺带获取，未同步时回退为开机毫秒）
    printf("timestamp: %lu ms: %llu\n", (unsigned long)device.getTimestamp(),
           (unsigned long long)device.getTimestampMs());
    printf("time: %s\n", device.getTimeString().c_str());

    while (true)
    {
        device.loop();  // 注册/MQTT 维持、消息收发
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
