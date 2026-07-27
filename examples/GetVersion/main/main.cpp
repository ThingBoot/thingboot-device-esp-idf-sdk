#include <stdio.h>
#include "ThingBootSDK.h"

ThingBootDevice device;

extern "C" void app_main(void)
{
    printf("ThingBoot SDK version: %s\n", device.getVersion().c_str());
}
