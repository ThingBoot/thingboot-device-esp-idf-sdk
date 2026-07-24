#ifndef THINGBOOT_SDK_ERRORS_H
#define THINGBOOT_SDK_ERRORS_H

// 错误码为纯宏定义，无平台依赖

// 成功
#define ERR_OK 0

// 功能块代码（从 10 开始，每块占 1000 个编号空间）
#define ERR_MODULE_SYSTEM       10
#define ERR_MODULE_SETUP        11
#define ERR_MODULE_CONFIG       12
#define ERR_MODULE_ORDER        13
#define ERR_MODULE_EVENT        14
#define ERR_MODULE_MESSAGE      15
#define ERR_MODULE_STATE        16
#define ERR_MODULE_TIMER        17
#define ERR_MODULE_PERIPHERAL   18
#define ERR_MODULE_DEBUG        19
#define ERR_MODULE_NETWORK      20

/* ============================================================
 *  系统核心（10xxx）
 * ============================================================ */
#define ERR_SYSTEM_OK                       0

/* ============================================================
 *  初始化设置（11xxx）
 * ============================================================ */
#define ERR_SETUP_OK                        0

/* ============================================================
 *  配置管理（12xxx）
 * ============================================================ */
#define ERR_CONFIG_OK                       0
#define ERR_CONFIG_NAME_EMPTY               12001
#define ERR_CONFIG_MAP_FULL                 12002
#define ERR_CONFIG_POS_INVALID              12003
#define ERR_CONFIG_LENGTH_ZERO              12004
#define ERR_CONFIG_NAME_CONFLICT            12005
#define ERR_CONFIG_NOT_FOUND                12010
#define ERR_CONFIG_VALUE_NULL               12011
#define ERR_CONFIG_WRITE_FAILED             12012

/* ============================================================
 *  命令处理（13xxx）
 * ============================================================ */
#define ERR_ORDER_OK                        0

/* ============================================================
 *  事件管理（14xxx）
 * ============================================================ */
#define ERR_EVENT_OK                        0
#define ERR_EVENT_NAME_EMPTY                14001
#define ERR_EVENT_CALLBACK_NULL             14002
#define ERR_EVENT_NO_SLOT                   14003
#define ERR_EVENT_VALUE_NULL                14011
#define ERR_EVENT_NOT_FOUND                 14020

/* ============================================================
 *  消息通信（15xxx）
 * ============================================================ */
#define ERR_MESSAGE_OK                      0

/* ============================================================
 *  状态管理（16xxx）
 * ============================================================ */
#define ERR_STATE_OK                        0
#define ERR_STATE_NAME_EMPTY                16001
#define ERR_STATE_CALLBACK_NULL             16002
#define ERR_STATE_INTERVAL_ZERO             16003
#define ERR_STATE_NO_SLOT                   16004

/* ============================================================
 *  定时器（17xxx）
 * ============================================================ */
#define ERR_TIMER_OK                        0
#define ERR_TIMER_INTERVAL_ZERO             17001
#define ERR_TIMER_CALLBACK_NULL             17002
#define ERR_TIMER_NO_SLOT                   17003

/* ============================================================
 *  外设控制（18xxx）
 * ============================================================ */
#define ERR_PERIPHERAL_OK                   0
#define ERR_PERIPHERAL_NUM_INVALID          18001
#define ERR_PERIPHERAL_NOT_CONFIGURED       18002

/* ============================================================
 *  桥接通信（21xxx）
 * ============================================================ */
#define ERR_BRIDGE_OK                       0
#define ERR_BRIDGE_NOT_INITIALIZED          21001
#define ERR_BRIDGE_PROTOCOL_INVALID         21002
#define ERR_BRIDGE_SEND_FAILED              21003
#define ERR_BRIDGE_PARAM_INVALID            21004

/* ============================================================
 *  调试（19xxx）
 * ============================================================ */
#define ERR_DEBUG_OK                        0

#endif
