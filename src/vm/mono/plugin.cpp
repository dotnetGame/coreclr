#include "common.h"
#include "mono.h"

// https://github.com/dotnetGame/coreclr/issues/3
// 该函数为Unity调用的第一个函数,该函数传入一个函数指针
// const char*(*unity_find_plugin_callback)(const char*)
// 
// 当发起pinvoke call时，需要进行依赖的dll / so搜索
// 首先mono会获取该dll / so的名字
// 如果存在被设置的函数指针，那么将mono获取的名字替换为调用该函数返回的名字
// 细节 : 该函数返回的char*不会被mono所持有，需要做strdup
const char*(*s_unity_find_plugin_callback)(const char*) = nullptr;

void mono_set_find_plugin_callback (gconstpointer find)
{
    s_unity_find_plugin_callback = reinterpret_cast<decltype(s_unity_find_plugin_callback)>(find);
}
