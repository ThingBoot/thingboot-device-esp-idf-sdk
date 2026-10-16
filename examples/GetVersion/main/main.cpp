#include <stdio.h>
#include "ThingBootSDK.h"

ThingBootDevice device;

extern "C" void app_main(void)
{
    printf("ThingBoot SDK version: %s\n", device.getVersion().c_str());

    // 链接完整性哨兵：引用 Gateway/公开符号，防止模块实现漏进 base 库
    // （未 install gateway addon 时返回 0，无运行时副作用）
    (void)device.Gateway.countChildren();
    (void)device.Message.mid();
}
