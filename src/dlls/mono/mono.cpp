#include <assert.h>
#include <Windows.h>

typedef int gboolean;
typedef int            gint;
typedef unsigned int   guint;
typedef short          gshort;
typedef unsigned short gushort;
typedef long           glong;
typedef unsigned long  gulong;
typedef void *         gpointer;
typedef const void *   gconstpointer;
typedef char           gchar;
typedef unsigned char  guchar;

typedef signed long SInt32;
typedef unsigned long UInt32;
typedef signed short SInt16;
typedef unsigned short UInt16;
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef unsigned long long UInt64;
typedef signed long long SInt64;

typedef __int8				gint8;
typedef unsigned __int8		guint8;
typedef __int16				gint16;
typedef unsigned __int16	guint16;
typedef unsigned __int64	guint64;
typedef float				gfloat;
typedef double				gdouble;
typedef unsigned __int16	gunichar2;

typedef uintptr_t gsize;

typedef gboolean(*MonoCoreClrPlatformCB) (const char *image_name);

struct MonoException;
struct MonoAssembly;
struct MonoObject;
struct MonoClassField;
struct MonoClass;
struct MonoDomain;
struct MonoImage;
struct MonoType;
struct MonoMethodSignature;
struct MonoArray;
struct MonoThread;
struct MonoVTable;
struct MonoProperty;
struct MonoReflectionAssembly;
struct MonoReflectionMethod;
struct MonoAppDomain;
struct MonoCustomAttrInfo;

struct MonoReflectionType { UInt32 offset[2]; MonoType* type; };

typedef const void* gconstpointer;
typedef void* gpointer;
typedef int gboolean;
typedef unsigned int guint32;
typedef int gint32;
typedef long gint64;
typedef unsigned char   guchar;
typedef UInt16 gunichar2;
struct MonoString
{
    gint32 monoObjectPart1;
    gint32 monoObjectPart2;
    gint32 length;
    gunichar2 firstCharacter;
};

struct MonoMethod {
    UInt16 flags;
    UInt16 iflags;
};

typedef enum
{
    MONO_VERIFIER_MODE_OFF,
    MONO_VERIFIER_MODE_VALID,
    MONO_VERIFIER_MODE_VERIFIABLE,
    MONO_VERIFIER_MODE_STRICT
} MiniVerifierMode;

typedef enum {
    MONO_SECURITY_MODE_NONE,
    MONO_SECURITY_MODE_CORE_CLR,
    MONO_SECURITY_MODE_CAS,
    MONO_SECURITY_MODE_SMCS_HACK
} MonoSecurityMode;

typedef void GFuncRef(void*, void*);
typedef GFuncRef* GFunc;

typedef enum {
    MONO_UNHANDLED_POLICY_LEGACY,
    MONO_UNHANDLED_POLICY_CURRENT
} MonoRuntimeUnhandledExceptionPolicy;

struct MonoMethodDesc {
    char *namespace2;
    char *klass;
    char *name;
    char *args1;
    UInt32 num_args;
    gboolean include_namespace, klass_glob, name_glob;
};

typedef struct _MonoMemPool MonoMemPool;
typedef struct _MonoJitInfo MonoJitInfo;

struct MonoAppDomainSetup;

typedef struct {
    unsigned short error_code;
    unsigned short hidden_0; /*DON'T TOUCH */

    void *hidden_1[12]; /*DON'T TOUCH */
    char hidden_2[128]; /*DON'T TOUCH */
} MonoError;

struct MonoCompile;

typedef struct MonoBasicBlock MonoBasicBlock;

#define MONO_PUBLIC_KEY_TOKEN_LENGTH	17

typedef struct {
    const char *name;
    const char *culture;
    const char *hash_value;
    const guint8* public_key;
    // string of 16 hex chars + 1 NULL
    guchar public_key_token[MONO_PUBLIC_KEY_TOKEN_LENGTH];
    guint32 hash_alg;
    guint32 hash_len;
    guint32 flags;
    guint16 major, minor, build, revision;
} MonoAssemblyName;

typedef enum {
    MONO_IMAGE_OK,
    MONO_IMAGE_ERROR_ERRNO,
    MONO_IMAGE_MISSING_ASSEMBLYREF,
    MONO_IMAGE_IMAGE_INVALID
} MonoImageOpenStatus;

typedef gboolean(*MonoStackWalk)     (MonoMethod *method, gint32 native_offset, gint32 il_offset, gboolean managed, gpointer data);

typedef guchar MonoBoolean;

typedef struct _MonoDebugSourceLocation		MonoDebugSourceLocation;

typedef struct _MonoAssemblyBindingInfo MonoAssemblyBindingInfo;

typedef struct MonoDlFallbackHandler MonoDlFallbackHandler;

typedef enum {
    /* the default is to always obey the breakpoint */
    MONO_BREAK_POLICY_ALWAYS,
    /* a nop is inserted instead of a breakpoint */
    MONO_BREAK_POLICY_NEVER,
    /* the breakpoint is executed only if the program has ben started under
    * the debugger (that is if a debugger was attached at the time the method
    * was compiled).
    */
    MONO_BREAK_POLICY_ON_DBG
} MonoBreakPolicy;
typedef MonoBreakPolicy(*MonoBreakPolicyFunc) (MonoMethod *method);

typedef void* (*MonoDlFallbackLoad) (const char *name, int flags, char **err, void *user_data);
typedef void* (*MonoDlFallbackSymbol) (void *handle, const char *name, char **err, void *user_data);
typedef void* (*MonoDlFallbackClose) (void *handle, void *user_data);

typedef void(*vprintf_func)(const char* msg, va_list args);

typedef void(*register_object_callback)(gpointer* arr, int size, void* callback_userdata);
typedef void(*WorldStateChanged)();
typedef struct _LivenessState LivenessState;

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
void mono_security_set_mode (MonoSecurityMode mode)
{
    assert(!"mono_security_set_mode");
}
void mono_add_internal_call (const char *name, gconstpointer method)
{
    assert(!"mono_add_internal_call");
}
void mono_unity_jit_cleanup (MonoDomain *domain)
{
    assert(!"mono_unity_jit_cleanup");
}
MonoDomain *  mono_jit_init_version (const char *domain_name, const char *runtime_version)
{
    assert(!"mono_jit_init");
    throw;
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
MonoClass * mono_class_from_name (MonoImage *image, const char* name_space, const char *name)
{
    assert(!"mono_class_from_name");
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
MonoObject* mono_runtime_invoke (MonoMethod *method, void *obj, MonoObject *params, MonoObject **exc)
{
    assert(!"mono_runtime_invoke");
    throw;
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
MonoMethod* mono_class_get_methods (MonoClass* klass, gpointer *iter)
{
    assert(!"mono_class_get_methods");
    throw;
}
int mono_class_get_userdata_offset ()
{
    assert(!"mono_class_get_userdata_offset");
    throw;
}

void mono_class_set_userdata (MonoClass *klass, void* userdata)
{
    assert(!"mono_class_set_userdata");
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
void mono_image_close (MonoImage *image)
{
    assert(!"mono_image_close");
}
void mono_unity_socket_security_enabled_set (gboolean enabled)
{
    assert(!"mono_unity_socket_security_enabled_set");
}
const char* mono_image_get_name (MonoImage *image)
{
    assert(!"mono_image_get_name");
    throw;
}
MonoClass* mono_get_object_class (void)
{
    assert(!"mono_get_object_class");
    throw;
}
void mono_set_signal_chaining (gboolean chain_signals)
{
    assert(!"mono_set_signal_chaining");
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
void mono_unity_runtime_set_main_args (int argc, const char* argv[])
{
    assert(!"mono_unity_runtime_set_main_args");
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
const char* mono_method_get_name (MonoMethod *method)
{
    assert(!"mono_method_get_name");
    throw;
}
char * mono_method_full_name (MonoMethod *method, gboolean signature)
{
    assert(!"mono_method_full_name");
    throw;
}
MonoImage* mono_assembly_get_image (MonoAssembly *assembly)
{
    assert(!"mono_assembly_get_image");
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
guint32 mono_signature_get_param_count (MonoMethodSignature *sig)
{
    assert(!"mono_signature_get_param_count");
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
MonoString* mono_string_new_wrapper (const char *text)
{
    assert(!"mono_string_new_wrapper");
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
MonoClass* mono_class_get_parent (MonoClass *klass)
{
    assert(!"mono_class_get_parent");
    throw;
}
const char* mono_class_get_namespace (MonoClass *klass)
{
    assert(!"mono_class_get_namespace");
    throw;
}
gboolean mono_class_is_subclass_of (MonoClass *klass, MonoClass *klassc, gboolean check_interfaces)
{
    assert(!"mono_class_is_subclass_of");
    throw;
}
const char* mono_class_get_name (MonoClass *klass)
{
    assert(!"mono_class_get_name");
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
MonoClass * mono_array_class_get (MonoClass *eclass, guint32 rank)
{
    assert(!"mono_array_class_get");
    throw;
}
gint32 mono_class_array_element_size (MonoClass *klass)
{
    assert(!"mono_class_array_element_size");
    throw;
}
MonoReflectionType* mono_type_get_object (MonoDomain *domain, MonoType *type)
{
    assert(!"mono_type_get_object");
    throw;
}
gboolean mono_class_is_generic (MonoClass *klass)
{
    assert(!"mono_class_is_generic");
    throw;
}
gboolean mono_class_is_inflated (MonoClass *klass)
{
    assert(!"mono_class_is_inflated");
    throw;
}
gboolean unity_mono_method_is_generic (MonoMethod* method)
{
    assert(!"unity_mono_method_is_generic");
    throw;
}
gboolean unity_mono_method_is_inflated (MonoMethod* method)
{
    assert(!"unity_mono_method_is_inflated");
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
void mono_thread_current_check_pending_interrupt ()
{
    assert(!"mono_thread_current");
}
void mono_thread_set_main (MonoThread *thread)
{
    assert(!"mono_thread_set_main");
}
void mono_set_find_plugin_callback (gconstpointer find)
{
    assert(!"mono_set_find_plugin_callback");
}
void mono_security_enable_core_clr ()
{
    assert(!"mono_security_enable_core_clr");
}
void mono_security_set_core_clr_platform_callback (MonoCoreClrPlatformCB callback)
{
    assert(!"mono_security_set_core_clr_platform_callback");
}
void mono_runtime_unhandled_exception_policy_set (MonoRuntimeUnhandledExceptionPolicy policy) 
{
    assert(!"mono_runtime_unhandled_exception_policy_set");
}
MonoClass* mono_class_get_nesting_type (MonoClass *klass)
{
    assert(!"mono_class_get_nesting_type");
    throw;
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
MonoMethodSignature* mono_method_signature (MonoMethod *m)
{
    assert(!"mono_method_signature");
    throw;
}
MonoType* mono_signature_get_params (MonoMethodSignature *sig, gpointer *iter)
{
    assert(!"mono_signature_get_params");
    throw;
}
guint32 mono_class_get_type (MonoClass *klass)
{
    assert(!"mono_class_get_type");
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
MonoImage * mono_image_open_from_data_with_name (char *data, guint32 data_len, gboolean need_copy, MonoImageOpenStatus *status, gboolean refonly, const char *name)
{
    assert(!"mono_image_open_from_data_with_name");
    throw;
}
static MonoAssembly* mono_assembly_load_from_gac (MonoAssemblyName *aname,  gchar *filename, MonoImageOpenStatus *status, MonoBoolean refonly)
{
    assert(!"mono_assembly_load_from");
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
MonoImage* mono_class_get_image (MonoClass *klass)
{
    assert(!"mono_class_get_image");
    throw;
}
gboolean mono_signature_is_instance (MonoMethodSignature *sig)
{
    assert(!"mono_signature_is_instance");
    throw;
}
MonoMethod* mono_method_get_last_managed (void)
{
    assert(!"mono_method_get_last_managed");
    throw;
}
MonoClass* mono_get_enum_class (void)
{
    assert(!"mono_get_enum_class");
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
void mono_unity_set_embeddinghostname(const char* name)
{
    assert(!"mono_unity_set_embeddinghostname");
}
void mono_set_assemblies_path (const char* path)
{
    assert(!"mono_set_assemblies_path");
}
guint32 mono_gchandle_new (MonoObject *obj, gboolean pinned)
{
    assert(!"mono_gchandle_new");
    throw;
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
int mono_gc_max_generation (void)
{
    assert(!"mono_gc_max_generation");
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
MonoAssembly * mono_assembly_load_from_full (MonoImage *image, const char*fname, MonoImageOpenStatus *status,gboolean refonly)
{
    assert(!"mono_assembly_load_from_full");
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
MonoClass* mono_class_get_element_class (MonoClass *klass)
{
    assert(!"mono_class_get_element_class");
    throw;
}
gboolean mono_unity_class_is_interface (MonoClass* klass)
{
    assert(!"mono_unity_class_is_interface");
    throw;
}
gboolean mono_unity_class_is_abstract (MonoClass* klass)
{
    assert(!"mono_unity_class_is_abstract");
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
void mono_unity_domain_set_config (MonoDomain *domain, const char *base_dir, const char *config_file_name)
{
    assert(!"mono_unity_domain_set_config");
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
MonoImage* mono_get_corlib (void)
{
    assert(!"mono_get_corlib");
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
int mono_parse_default_optimizations (const char* p)
{
    assert(!"mono_parse_default_optimizations");
    throw;
}
void mono_set_defaults (int verbose_level, guint32 opts)
{
    assert(!"mono_set_defaults");
}
void mono_config_parse_publisher_policy (const gchar *filename, MonoAssemblyBindingInfo *info)
{
    assert(!"mono_config_parse");
}
void mono_set_dirs (const char *assembly_dir, const char *config_dir)
{
    assert(!"mono_set_dirs");
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
MonoObject* mono_custom_attrs_get_attr (MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    assert(!"mono_custom_attrs_get_attr");
    throw;
}
static MonoArray* mono_custom_attrs_construct_by_type (MonoCustomAttrInfo *cinfo, MonoClass *attr_klass)
{
    assert(!"mono_custom_attrs_construct");
}
gboolean mono_custom_attrs_has_attr (MonoCustomAttrInfo *ainfo, MonoClass *attr_klass)
{
    assert(!"mono_custom_attrs_has_attr");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_field (MonoClass *klass, MonoClassField *field)
{
    assert(!"mono_custom_attrs_from_field");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_method (MonoMethod *method)
{
    assert(!"mono_custom_attrs_from_method");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_class (MonoClass *klass)
{
    assert(!"mono_custom_attrs_from_class");
    throw;
}
MonoCustomAttrInfo* mono_custom_attrs_from_assembly (MonoAssembly *assembly)
{
    assert(!"mono_custom_attrs_from_assembly");
    throw;
}
MonoArray* mono_reflection_get_custom_attrs_by_type (MonoObject *obj, MonoClass *attr_klass)
{
    assert(!"mono_reflection_get_custom_attrs_by_type");
    throw;
}
void mono_custom_attrs_free (MonoCustomAttrInfo *ainfo)
{
    assert(!"mono_custom_attrs_free");
}
MonoException* mono_unity_loader_get_last_error_and_error_prepare_exception ()
{
    assert(!"mono_unity_loader_get_last_error_and_error_prepare_exception");
    throw;
}
MonoDlFallbackHandler * mono_dl_fallback_register (MonoDlFallbackLoad load_func, MonoDlFallbackSymbol symbol_func, MonoDlFallbackClose close_func, void *user_data)
{
    assert(!"mono_dl_fallback_register");
    throw;
}
void mono_dl_fallback_unregister (MonoDlFallbackHandler *handler)
{
    assert(!"mono_dl_fallback_unregister");
}
void mono_unity_set_vprintf_func (vprintf_func func)
{
    assert(!"mono_unity_set_vprintf_func");
}
void mono_unity_liveness_stop_gc_world (LivenessState* state)
{
    assert(!"mono_unity_liveness_stop_gc_world");
}
void mono_unity_liveness_finalize (LivenessState* state)
{
    assert(!"mono_unity_liveness_finalize");
}
void mono_unity_liveness_start_gc_world (LivenessState* state)
{
    assert(!"mono_unity_liveness_start_gc_world");
}
void mono_unity_liveness_free_struct (LivenessState* state)
{
    assert(!"mono_unity_liveness_free_struct");
}
LivenessState* mono_unity_liveness_calculation_begin (MonoClass* filter, guint max_count, register_object_callback callback, void* callback_userdata, WorldStateChanged onWorldStartCallback, WorldStateChanged onWorldStopCallback)
{
    assert(!"mono_unity_liveness_calculation_begin");
    throw;
}
void mono_unity_liveness_calculation_end (LivenessState* state)
{
    assert(!"mono_unity_liveness_calculation_end");
}
gpointer mono_unity_liveness_calculation_from_root_managed(gpointer root_handle, gpointer filter_handle, WorldStateChanged onWorldStartCallback, WorldStateChanged onWorldStopCallback)
{
    assert(!"mono_unity_liveness_calculation_from_root");
    throw;
}
gpointer mono_unity_liveness_calculation_from_statics_managed(gpointer filter_handle, WorldStateChanged onWorldStartCallback, WorldStateChanged onWorldStopCallback)
{
    assert(!"mono_unity_liveness_calculation_from_statics");
    throw;
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
