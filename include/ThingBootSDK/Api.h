#ifndef THINGBOOT_SDK_API_H
#define THINGBOOT_SDK_API_H

class ThingBootDevice;

// 云平台代发 HTTP 请求；设备同时只允许一个 pending 请求。
// The cloud platform sends HTTP requests on behalf of the device; only one request may be pending.
class ThingBootApi {
private:
    ThingBootDevice* _device;

public:
    ThingBootApi(ThingBootDevice* device = nullptr) : _device(device) {}

    // 发起请求，结果通过 onResponse 回调返回。
    // Start a request; the result is delivered to the onResponse callback.
    uint16_t request(const char* method, const char* url);
    uint16_t request(const char* method, const char* url,
        JSONVar headers, JSONVar body,
        const char* content_type = "application/json",
        uint32_t timeout_ms = 10000);

    // 注册响应回调：code 为平台/SDK 错误码，status 为 HTTP 状态码。
    // Register the response callback: code is the platform/SDK code, status is the HTTP status.
    uint16_t onResponse(std::function<void(uint16_t code, uint16_t status, JSONVar data, const char* msg)> callback);

    // 是否有等待响应或超时处理的请求。
    // Whether a request is waiting for a response or timeout handling.
    bool pending();
};

#endif
