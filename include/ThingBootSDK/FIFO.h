#ifndef THINGBOOT_SDK_FIFO_H
#define THINGBOOT_SDK_FIFO_H

#include <cstddef>
#include <cstdlib>

// 泛型先进先出队列（环形缓冲，一次性 malloc）
// 与 SDK 内部 MQTT/Mesh 接收队列同款实现
// Generic FIFO queue (ring buffer, single malloc). Same implementation as the
// SDK's internal MQTT/Mesh receive queues.
//
// 用法 / Usage:
//   TbFIFO<MyStruct> q(10);     // 容量 10
//   q.push(item);               // 满返回 false
//   if (q.pop(item)) { ... }    // 空返回 false
//
// 注意：构造函数在内存不足时死循环（ESP 上 malloc 失败无更好出路，请按容量合理规划）
template<typename T>
class TbFIFO {
public:
    /* 构造函数：传入最大长度，失败会 panic（ESP 默认 abort）*/
    explicit TbFIFO(size_t max_len)
        : max(max_len), buf(static_cast<T*>(malloc(sizeof(T) * max_len))),
          head(0), tail(0), count(0) {
        if (!buf) while (1); // 内存不足，可自行改抛异常
    }

    /* 析构：释放一次性申请的缓冲区 */
    ~TbFIFO() { free(buf); }

    /* 压入：满返回 false */
    bool push(const T& item) {
        if (count == max) return false;
        buf[head] = item;
        head = (head + 1) % max;
        ++count;
        return true;
    }

    /* 弹出：空返回 false */
    bool pop(T& out) {
        if (count == 0) return false;
        out = buf[tail];
        tail = (tail + 1) % max;
        --count;
        return true;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    bool full() const { return count == max; }

private:
    const size_t max;   // 容量
    T* const buf;       // 一次性 malloc 的缓冲区
    size_t head;        // 下一次写入
    size_t tail;        // 最早元素
    size_t count;       // 当前元素个数
};

#endif
