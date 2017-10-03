#include "common.h"
#include <assert.h>

#include "mono.h"

void mono_thread_suspend_all_other_threads (void)
{
    assert(!"mono_thread_suspend_all_other_threads");
}
void mono_thread_pool_cleanup (void)
{
    assert(!"mono_thread_pool_cleanup");
}
void mono_threads_set_shutting_down (void)
{
    assert(!"mono_threads_set_shutting_down");
}
void mono_runtime_set_shutting_down (void)
{
    assert(!"mono_runtime_set_shutting_down");
}
gboolean mono_runtime_is_shutting_down (void)
{
    assert(!"mono_runtime_is_shutting_down");
    throw;
}
gboolean mono_domain_finalize (MonoDomain *domain, guint32 timeout) 
{
    assert(!"mono_domain_finalize");
    throw;
}
void mono_runtime_cleanup_handlers (void)
{
    assert(!"mono_runtime_cleanup");
}
MonoMethod* mono_object_get_virtual_method (MonoObject *obj, MonoMethod *method)
{
    assert(!"mono_object_get_virtual_method");
    throw;
}
void mono_unity_jit_cleanup (MonoDomain *domain)
{
    assert(!"mono_unity_jit_cleanup");
}
int  mono_jit_exec (MonoDomain *domain, MonoAssembly *assembly, int argc, char *argv[])
{
    assert(!"mono_jit_exec");
    throw;
}
gpointer mono_jit_info_get_code_start (MonoJitInfo* ji)
{
    assert(!"mono_jit_info_get_code_start");
    throw;
}
int mono_jit_info_get_code_size (MonoJitInfo* ji)
{
    assert(!"mono_jit_info_get_code_size");
    throw;
}
MonoClass * mono_class_from_name_case (MonoImage *image, const char* name_space, const char *name)
{
    assert(!"mono_class_from_name_case");
    throw;
}
MonoAssembly * mono_domain_assembly_open (MonoDomain *domain, const char *name)
{
    assert(!"mono_domain_assembly_open");
    throw;
}
static MonoAppDomain * mono_domain_create_appdomain_internal (char *friendly_name, MonoAppDomainSetup *setup)
{
    assert(!"mono_domain_create_appdomain");
}
void mono_domain_unload (MonoDomain *domain)
{
    assert(!"mono_domain_unload");
}
MonoObject * mono_object_new_from_token  (MonoDomain *domain, MonoImage *image, guint32 token)
{
    assert(!"mono_object_new");
    throw;
}
void mono_runtime_object_init (MonoObject *this_obj)
{
    assert(!"mono_runtime_object_init");
}
void mono_field_set_value (MonoObject *obj, MonoClassField *field, void *value)
{
    assert(!"mono_field_set_value");
}
MonoObject * mono_field_get_value_object (MonoDomain *domain, MonoClassField *field, MonoObject *obj)
{
    assert(!"mono_field_get_value");
    throw;
}
guint32 mono_field_get_offset (MonoClassField *field)
{
    assert(!"mono_field_get_offset");
    throw;
}
MonoClassField* mono_class_get_fields (MonoClass* klass, gpointer *iter)
{
    assert(!"mono_class_get_fields");
    throw;
}
MonoClass* mono_class_get_nested_types (MonoClass* klass, gpointer *iter)
{
    assert(!"mono_class_get_nested_types");
    throw;
}

MonoDomain* mono_get_root_domain (void)
{
    assert(!"mono_get_root_domain");
    throw;
}
gint32 mono_domain_get_id (MonoDomain *domain)
{
    assert(!"mono_domain_get_id");
    throw;
}
void mono_assembly_foreach (GFunc func, gpointer user_data)
{
    assert(!"mono_assembly_foreach");
}
MonoClass* mono_get_object_class (void)
{
    assert(!"mono_get_object_class");
    throw;
}
LONG mono_unity_seh_handler(EXCEPTION_POINTERS* ep)
{
    assert(!"mono_unity_seh_handler");
    throw;
}
void mono_unity_set_unhandled_exception_handler(void* handler)
{
    assert(!"mono_unity_set_unhandled_exception_handler");
}
MonoObject* mono_runtime_invoke_array (MonoMethod *method, void *obj, MonoArray *params, MonoObject **exc)
{
    assert(!"mono_runtime_invoke_array");
    throw;
}
char*  mono_array_addr_with_size (MonoArray* array, int size, uintptr_t idx)
{
    assert(!"mono_array_addr_with_size");
    throw;
}
gunichar2 * mono_string_to_utf16 (MonoString *s)
{
    assert(!"mono_string_to_utf16");
    throw;
}
const char* mono_field_get_name (MonoClassField *field)
{
    assert(!"mono_field_get_name");
    throw;
}
MonoClass* mono_field_get_parent (MonoClassField *field)
{
    assert(!"mono_field_get_parent");
    throw;
}
MonoType* mono_field_get_type (MonoClassField *field)
{
    assert(!"mono_field_get_type");
    throw;
}
static MonoType* mono_type_get_type_byval (MonoType *type)
{
    assert(!"mono_type_get_type");
}
char * mono_method_full_name (MonoMethod *method, gboolean signature)
{
    assert(!"mono_method_full_name");
    throw;
}
MonoClass* mono_method_get_class (MonoMethod *method)
{
    assert(!"mono_method_get_class");
    throw;
}
MonoClass* mono_object_get_class (MonoObject *obj)
{
    assert(!"mono_object_get_class");
    throw;
}
MonoObject * mono_object_isinst_mbyref (MonoObject *obj, MonoClass *klass)
{
    assert(!"mono_object_isinst");
    throw;
}
gboolean mono_class_is_valuetype (MonoClass *klass)
{
    assert(!"mono_class_is_valuetype");
    throw;
}
gboolean mono_class_is_blittable (MonoClass *klass)
{
    assert(!"mono_class_is_blittable");
    throw;
}
char * mono_string_to_utf8_mp (MonoMemPool *mp, MonoString *s, MonoError *error)
{
    assert(!"mono_string_to_utf8");
    throw;
}
MonoString* mono_unity_string_empty_wrapper ()
{
    assert(!"mono_unity_string_empty_wrapper");
    throw;
}
MonoString* mono_string_new_len (MonoDomain *domain, const char *text, guint length)
{
    assert(!"mono_string_new_len");
    throw;
}
MonoString * mono_string_from_utf16 (gunichar2 *data)
{
    assert(!"mono_string_from_utf16");
    throw;
}
char* mono_type_get_name (MonoType *type)
{
    assert(!"mono_type_get_name");
    throw;
}
MonoClass* mono_type_get_class (MonoType *type)
{
    assert(!"mono_type_get_class");
    throw;
}
MonoException * mono_exception_from_name_msg (MonoImage *image, const char *name_space, const char *name, const char *msg)
{
    assert(!"mono_exception_from_name_msg");
    throw;
}
MonoException * mono_exception_from_name_two_strings (MonoImage *image, const char *name_space, MonoString *a1, MonoString *a2)
{
    assert(!"mono_exception_from_name_two_strings");
    throw;
}
MonoException* mono_get_exception_argument_null (const char *arg)
{
    assert(!"mono_get_exception_argument_null");
    throw;
}
void mono_raise_exception (MonoException *ex) 
{
    assert(!"mono_raise_exception");
}
MonoClass* mono_get_exception_class (void)
{
    assert(!"mono_get_exception_class");
    throw;
}
MonoClass* mono_get_array_class (void)
{
    assert(!"mono_get_array_class");
    throw;
}
MonoClass* mono_get_string_class (void)
{
    assert(!"mono_get_string_class");
    throw;
}
MonoClass* mono_get_boolean_class (void)
{
    assert(!"mono_get_boolean_class");
    throw;
}
MonoClass* mono_get_byte_class (void)
{
    assert(!"mono_get_byte_class");
    throw;
}
MonoClass* mono_get_char_class (void)
{
    assert(!"mono_get_char_class");
    throw;
}
MonoClass* mono_get_int16_class (void)
{
    assert(!"mono_get_int16_class");
    throw;
}
MonoClass* mono_get_int32_class (void)
{
    assert(!"mono_get_int32_class");
    throw;
}
MonoClass* mono_get_int64_class (void)
{
    assert(!"mono_get_int64_class");
    throw;
}
MonoClass* mono_get_single_class (void)
{
    assert(!"mono_get_single_class");
    throw;
}
MonoClass* mono_get_double_class (void)
{
    assert(!"mono_get_double_class");
    throw;
}
MonoArray * mono_array_new_3 (MonoMethod *cm, guint32 length1, guint32 length2, guint32 length3)
{
    assert(!"mono_array_new");
    throw;
}
MonoArray* mono_unity_array_new_2d (MonoDomain *domain, MonoClass *eklass, size_t size0, size_t size1)
{
    assert(!"mono_unity_array_new_2d");
    throw;
}
MonoArray* mono_unity_array_new_3d (MonoDomain *domain, MonoClass *eklass, size_t size0, size_t size1, size_t size2)
{
    assert(!"mono_unity_array_new_3d");
    throw;
}
gint32 mono_class_array_element_size (MonoClass *klass)
{
    assert(!"mono_class_array_element_size");
    throw;
}
static void mono_thread_attach_cb (gsize tid, gpointer stack_start)
{
    assert(!"mono_thread_attach");
}
void mono_thread_detach (MonoThread *thread)
{
    assert(!"mono_thread_detach");
}
void mono_thread_exiting ()
{
    assert(!"mono_thread_exit");
}
void mono_security_enable_core_clr ()
{
    assert(!"mono_security_enable_core_clr");
}
MonoVTable * mono_class_vtable_full (MonoDomain *domain, MonoClass *klass, gboolean raise_on_error)
{
    assert(!"mono_class_vtable");
    throw;
}
MonoReflectionMethod* mono_method_get_object (MonoDomain *domain, MonoMethod *method, MonoClass *refclass)
{
    assert(!"mono_method_get_object");
    throw;
}
MonoType* mono_signature_get_params (MonoMethodSignature *sig, gpointer *iter)
{
    assert(!"mono_signature_get_params");
    throw;
}
void mono_debug_init_method (MonoCompile *cfg, MonoBasicBlock *start_block, guint32 breakpoint_id)
{
    assert(!"mono_debug_init");
}
gboolean mono_is_debugger_attached (void)
{
    assert(!"mono_is_debugger_attached");
    throw;
}
void mono_debug_open_image_from_memory (MonoImage *image, const guint8 *raw_contents, int size)
{
    assert(!"mono_debug_open_image_from_memory");
}
guint32 mono_field_get_flags (MonoClassField *field)
{
    assert(!"mono_field_get_flags");
    throw;
}
MonoImage * mono_image_open_from_data_full (char *data, guint32 data_len, gboolean need_copy, MonoImageOpenStatus *status, gboolean refonly)
{
    assert(!"mono_image_open_from_data_full");
    throw;
}
MonoAssembly* mono_assembly_load_from (MonoAssemblyName *aname,  gchar *filename, MonoImageOpenStatus *status, MonoBoolean refonly)
{
    assert(!"mono_assembly_load_from");
    throw;
}
gboolean mono_assembly_fill_assembly_name (MonoImage *image, MonoAssemblyName *aname)
{
    assert(!"mono_assembly_fill_assembly_name");
    throw;
}
gboolean mono_assembly_name_parse (const char *name, MonoAssemblyName *aname)
{
    assert(!"mono_assembly_name_parse");
    throw;
}
MonoAssembly* mono_assembly_loaded (MonoAssemblyName *aname)
{
    assert(!"mono_assembly_loaded");
    throw;
}
int mono_image_get_table_rows (MonoImage *image, int table_id)
{
    assert(!"mono_image_get_table_rows");
    throw;
}
MonoClass* mono_unity_class_get(MonoImage* image, guint32 type_token)
{
    assert(!"mono_unity_class_get");
    throw;
}
gboolean mono_metadata_signature_equal (MonoMethodSignature *sig1, MonoMethodSignature *sig2)
{
    assert(!"mono_metadata_signature_equal");
    throw;
}
MonoObject * mono_value_box (MonoDomain *domain, MonoClass *klass, gpointer value)
{
    assert(!"mono_value_box");
    throw;
}
MonoMethod* mono_method_get_last_managed (void)
{
    assert(!"mono_method_get_last_managed");
    throw;
}
MonoType* mono_class_get_byref_type (MonoClass *klass)
{
    assert(!"mono_class_get_byref_type");
    throw;
}
void mono_field_static_get_value (MonoVTable *vt, MonoClassField *field, void *value)
{
    assert(!"mono_field_static_get_value");
}
MonoObject* mono_gchandle_get_target (guint32 gchandle)
{
    assert(!"mono_gchandle_get_target");
    throw;
}
guint32 mono_gchandle_new_weakref (MonoObject *obj, gboolean track_resurrection)
{
    assert(!"mono_gchandle_new_weakref");
    throw;
}
gboolean mono_gchandle_is_in_domain (guint32 gchandle, MonoDomain *domain)
{
    assert(!"mono_gchandle_is_in_domain");
    throw;
}
MonoReflectionAssembly* mono_assembly_get_object (MonoDomain *domain, MonoAssembly *assembly)
{
    assert(!"mono_assembly_get_object");
    throw;
}
void mono_gchandle_free_domain (MonoDomain *domain)
{
    assert(!"mono_gchandle_free");
}
void mono_stack_walk_no_il (MonoStackWalk func, gpointer user_data)
{
    assert(!"mono_stack_walk");
}
char * mono_pmip (void *ip)
{
    assert(!"mono_pmip");
    throw;
}
MonoObject* mono_runtime_delegate_invoke (MonoObject *delegate, void **params, MonoObject **exc)
{
    assert(!"mono_runtime_delegate_invoke");
    throw;
}
MonoJitInfo* mono_jit_info_table_find (MonoDomain *domain, char *addr)
{
    assert(!"mono_jit_info_table_find");
    throw;
}
MonoDebugSourceLocation * mono_debug_lookup_source_location (MonoMethod *method, guint32 address, MonoDomain *domain)
{
    assert(!"mono_debug_lookup_source_location");
    throw;
}
void mono_debug_free_source_location (MonoDebugSourceLocation *location)
{
    assert(!"mono_debug_free_source_location");
}
MonoProperty* mono_class_get_properties (MonoClass* klass, gpointer *iter)
{
    assert(!"mono_class_get_properties");
    throw;
}
MonoMethod* mono_property_get_get_method (MonoProperty *prop)
{
    assert(!"mono_property_get_get_method");
    throw;
}
int mono_gc_collection_count (int generation)
{
    assert(!"mono_gc_collect");
    throw;
}
gint64 mono_gc_get_used_size (void)
{
    assert(!"mono_gc_get_used_size");
    throw;
}
gint64 mono_gc_get_heap_size (void)
{
    assert(!"mono_gc_get_heap_size");
    throw;
}
void mono_gc_wbarrier_generic_store (gpointer ptr, MonoObject* value)
{
    assert(!"mono_gc_wbarrier_generic_store");
}
MonoAssembly*  mono_image_get_assembly (MonoImage *image)
{
    assert(!"mono_image_get_assembly");
    throw;
}
MonoAssembly * mono_assembly_open (const char *filename, MonoImageOpenStatus *status)
{
    assert(!"mono_assembly_open");
    throw;
}
gboolean mono_class_is_enum (MonoClass *klass)
{
    assert(!"mono_class_is_enum");
    throw;
}
MonoType* mono_class_enum_basetype (MonoClass *klass)
{
    assert(!"mono_class_enum_basetype");
    throw;
}
gint32 mono_class_instance_size (MonoClass *klass)
{
    assert(!"mono_class_instance_size");
    throw;
}
guint mono_object_get_size (MonoObject* o)
{
    assert(!"mono_object_get_size");
    throw;
}
guint32 mono_class_get_type_token (MonoClass *klass)
{
    assert(!"mono_class_get_type_token");
    throw;
}
const char* mono_image_get_filename (MonoImage *image)
{
    assert(!"mono_image_get_filename");
    throw;
}
MonoClass* mono_class_get_interfaces (MonoClass* klass, gpointer *iter)
{
    assert(!"mono_class_get_interfaces");
    throw;
}
void mono_assembly_close (MonoAssembly *assembly)
{
    assert(!"mono_assembly_close");
}
MonoProperty* mono_class_get_property_from_name (MonoClass *klass, const char *name)
{
    assert(!"mono_class_get_property_from_name");
    throw;
}
MonoMethod * mono_class_get_method_from_name_flags (MonoClass *klass, const char *name, int param_count, int flags)
{
    assert(!"mono_class_get_method_from_name");
    throw;
}
MonoClass * mono_class_from_mono_type (MonoType *type)
{
    assert(!"mono_class_from_mono_type");
    throw;
}
int mono_class_get_rank (MonoClass *klass)
{
    assert(!"mono_class_get_rank");
    throw;
}

gint32 mono_array_element_size (MonoClass *ac)
{
    assert(!"mono_array_element_size");
    throw;
}
void mono_domain_set_internal (MonoDomain *domain)
{
    assert(!"mono_domain_set");
}
void  mono_thread_push_appdomain_ref (MonoDomain *domain)
{
    assert(!"mono_thread_push_appdomain_ref");
}
void mono_thread_pop_appdomain_ref (void)
{
    assert(!"mono_thread_pop_appdomain_ref");
}
int mono_runtime_exec_main (MonoMethod *method, MonoArray *args, MonoObject **exc)
{
    assert(!"mono_runtime_exec_main");
    throw;
}
MonoClassField * mono_class_get_field_from_name_full (MonoClass *klass, const char *name, MonoType *type)
{
    assert(!"mono_class_get_field_from_name");
    throw;
}
guint32 mono_class_get_flags (MonoClass *klass)
{
    assert(!"mono_class_get_flags");
    throw;
}
void mono_config_parse_publisher_policy (const gchar *filename, MonoAssemblyBindingInfo *info)
{
    assert(!"mono_config_parse");
}
void mono_set_break_policy (MonoBreakPolicyFunc policy_callback)
{
    assert(!"mono_set_break_policy");
}
void mono_jit_parse_options (int argc, char * argv[])
{
    assert(!"mono_jit_parse_options");
}
gpointer mono_object_unbox (MonoObject *obj)
{
    assert(!"mono_object_unbox");
    throw;
}
void mono_unity_set_vprintf_func (vprintf_func func)
{
    assert(!"mono_unity_set_vprintf_func");
}

MonoMethod* unity_mono_reflection_method_get_method(MonoReflectionMethod* mrf)
{
    assert(!"unity_mono_reflection_method_get_method");
    throw;
}
void mono_unity_g_free (void* ptr)
{
    assert(!"mono_unity_g_free");
}
void  mono_trace_set_level_string (const char *value)
{
    assert(!"mono_trace_set_level_string");
}
void  mono_trace_set_mask_string (char *value)
{
    assert(!"mono_trace_set_mask_string");
}

MonoClassField *
mono_class_get_field_from_name(MonoClass *klass, const char *name)
{
    assert(!"mono_class_get_field_from_name");
    throw;
}

MonoMethod *
mono_class_get_method_from_name(MonoClass *klass, const char *name, int param_count)
{
    assert(!"mono_class_get_method_from_name");
    throw;
}

void*
mono_class_get_userdata(MonoClass *klass)
{
    assert(!"mono_class_get_userdata");
    throw;
}

MonoArray*
mono_custom_attrs_construct(MonoCustomAttrInfo *cinfo)
{
    assert(!"mono_custom_attrs_construct");
    throw;
}

void
mono_debug_init(MonoDebugFormat format)
{
    assert(!"mono_debug_init");
}

MonoDomain *
mono_domain_create_appdomain(char *friendly_name, char *configuration_file)
{
    assert(!"mono_domain_create_appdomain");
    throw;
}

gboolean
mono_domain_set(MonoDomain *domain, gboolean force)
{
    assert(!"mono_domain_set");
    throw;
}

void
mono_field_get_value(MonoObject *obj, MonoClassField *field, void *value)
{
    assert(!"mono_field_get_value");
}

MonoVTable *
mono_class_vtable(MonoDomain *domain, MonoClass *klass)
{
    assert(!"mono_class_vtable");
    throw;
}

void
mono_gchandle_free(guint32 gchandle)
{
    assert(!"mono_gchandle_free");
}

MonoObject *
mono_object_isinst(MonoObject *obj, MonoClass *klass)
{
    assert(!"mono_object_isinst");
    throw;
}

MonoObject *
mono_object_new(MonoDomain *domain, MonoClass *klass)
{
    assert(!"mono_object_new");
    throw;
}

MonoObject *
mono_object_new_alloc_specific(MonoVTable *vtable)
{
    assert(!"mono_object_new_alloc_specific");
    throw;
}

MonoObject *
mono_object_new_specific(MonoVTable *vtable)
{
    assert(!"mono_object_new_specific");
    throw;
}

void
mono_runtime_cleanup(MonoDomain *domain)
{
    assert(!"mono_runtime_cleanup");
}

void
mono_stack_walk(MonoStackWalk func, gpointer user_data)
{
    assert(!"mono_stack_walk");
}

char *
mono_string_to_utf8(MonoString *s)
{
    assert(!"mono_string_to_utf8");
    throw;
}

char*
mono_stringify_assembly_name(MonoAssemblyName *aname)
{
    assert(!"mono_stringify_assembly_name");
    throw;
}

MonoThread *
mono_thread_attach(MonoDomain *domain)
{
    assert(!"mono_thread_attach");
    throw;
}

void
mono_thread_exit()
{
    assert(!"mono_thread_exit");
}

int
mono_type_get_type(MonoType *type)
{
    assert(!"mono_type_get_type");
    throw;
}

std::ofstream logger("1.log");
std::wofstream wlogger("1w.log");
