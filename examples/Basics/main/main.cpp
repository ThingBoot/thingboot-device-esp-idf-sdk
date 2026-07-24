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

extern "C" void app_main(void)
{
    //调试信息打印
    device.onDebug(onDebug);

    //SDK 版本
    printf("version: %s\n", device.getVersion().c_str());

    //JSON 兼容层（与 Arduino_JSON 用法一致）
    JSONVar data = JSON.parse("{\"power\":1,\"name\":\"relay\"}");
    if (data.hasOwnProperty("power"))
    {
        printf("parse power=%d name=%s\n", CN(data["power"]), (const char*)data["name"]);
    }
    JSONVar ret;
    ret["power"] = "1";
    ret["online"] = true;
    printf("stringify: %s typeof: %s\n", JSON.stringify(ret).c_str(), JSON.typeof(ret).c_str());

    //产品信息
    device.setProduct("product_key", "product_secret", "board", "esp32", "1.0.0");

    //系统初始化
    device.setup();

    //系统信息
    printf("system info: %s\n", device.getSystemInfo().c_str());

    //ROM 持久化（重启后保持）
    device.setBenchID(88);
    printf("bench: %d mode: %s timezone: %s\n",
           device.getBenchID(), device.getMode().c_str(), device.getTimezone().c_str());

    //用户定时器：每 1 秒执行一次，共 5 次
    device.Timer.addTimer(1000, 5, []() {
        printf("timer tick\n");
    });

    while (true)
    {
        device.loop();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
