#include "common.h"
#include "mono.h"

// https://github.com/dotnetGame/coreclr/issues/3
// �ú���ΪUnity���õĵ�һ������,�ú�������һ������ָ��
// const char*(*unity_find_plugin_callback)(const char*)
// 
// ������pinvoke callʱ����Ҫ����������dll / so����
// ����mono���ȡ��dll / so������
// ������ڱ����õĺ���ָ�룬��ô��mono��ȡ�������滻Ϊ���øú������ص�����
// ϸ�� : �ú������ص�char*���ᱻmono�����У���Ҫ��strdup
const char*(*s_unity_find_plugin_callback)(const char*) = nullptr;

void mono_set_find_plugin_callback (gconstpointer find)
{
    s_unity_find_plugin_callback = reinterpret_cast<decltype(s_unity_find_plugin_callback)>(find);
}
