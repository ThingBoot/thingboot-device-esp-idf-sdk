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
    device.Order.replyMessage("{\"result\":\"ok\"}");
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

    while (true)
    {
        device.loop();  // 注册/MQTT 维持、消息收发
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
