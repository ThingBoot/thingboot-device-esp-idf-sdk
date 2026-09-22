#ifndef THINGBOOT_SDK_JSON_H
#define THINGBOOT_SDK_JSON_H

// JSONVar / JSON / null —— Arduino_JSON 兼容层（基于 cJSON 实现）
// 标识符与语义和 Arduino 版保持一致，用户代码零改动

#include <cstddef>
#include <string>
#include <memory>

struct cJSON;
struct cJSON_Deleter { void operator()(cJSON* p) const; };

class JSONVar {
public:
    JSONVar();                              // undefined
    JSONVar(std::nullptr_t);                // null
    JSONVar(bool);
    JSONVar(int);
    JSONVar(unsigned int);
    JSONVar(long);
    JSONVar(unsigned long);
    JSONVar(double);
    JSONVar(const char*);
    JSONVar(const std::string&);
    JSONVar(const JSONVar& other);          // 共享同一棵 JSON 树（与 Arduino_JSON 语义一致）
    JSONVar& operator=(const JSONVar& other);
    ~JSONVar() = default;

    // 对象访问：读不存在返回 undefined；写不存在自动创建（Arduino_JSON 语义）
    JSONVar operator[](const char* key);
    JSONVar operator[](const std::string& key);
    // 数组访问
    JSONVar operator[](int index);

    bool hasOwnProperty(const char* key) const;
    JSONVar keys() const;                   // 字符串数组
    size_t length() const;                  // 数组/对象元素数

    explicit operator bool() const;         // 真值：boolean 值；非 boolean 时为"已定义且非 null"
    operator const char*() const;           // 字符串值（非字符串返回 ""）

private:
    // 共享根节点所有权；node 指向树内当前节点（nullptr 表示 undefined）
    std::shared_ptr<cJSON> _root;
    cJSON* _node = nullptr;
    // 成员视图信息（用于赋值时写回父节点）
    cJSON* _parent = nullptr;
    std::string _key;
    int _index = -1;

    static JSONVar wrap(std::shared_ptr<cJSON> root, cJSON* node,
                        cJSON* parent = nullptr, const char* key = nullptr, int index = -1);
    // 以自有根节点构造（持有整棵树）
    static JSONVar make_own(cJSON* node);
    // 当 _node 为 undefined 但存在父对象时，物化为对象（支持 var["a"]["b"] 链式写入）
    static void materialize_object(JSONVar& v);

    friend class JSONClass;
};

class JSONClass {
public:
    JSONVar parse(const char* s);               // 解析失败返回 undefined
    std::string stringify(const JSONVar&);      // 紧凑输出
    std::string typeof(const JSONVar&);         // "undefined"/"null"/"boolean"/"number"/"string"/"array"/"object"
};

// 与 Arduino_JSON 用法一致：JSON.parse(...) / JSON.stringify(...) / JSON.typeof(...)
extern JSONClass JSON;

// 与 Arduino_JSON 用法一致：JSONVar dns = null;
extern const JSONVar null;

#endif
