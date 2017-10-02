#ifndef MONO_H_
#define MONO_H_

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
// typedef unsigned long UInt32;
typedef signed short SInt16;
// typedef unsigned short UInt16;
typedef unsigned char UInt8;
typedef signed char SInt8;
// typedef unsigned long long UInt64;
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
typedef Assembly MonoAssembly;
typedef Object MonoObject;
struct MonoClassField;
typedef MethodTable MonoClass;
typedef AppDomain MonoDomain;
typedef PEAssembly MonoImage;
struct MonoType;
typedef MethodDesc MonoMethodSignature;
typedef Object MonoArray;
typedef Thread MonoThread;
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
typedef StringObject MonoString;

typedef MethodDesc MonoMethod;

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

typedef guint32 mono_array_size_t;

typedef enum {
    MONO_DEBUG_FORMAT_NONE,
    MONO_DEBUG_FORMAT_MONO,
    MONO_DEBUG_FORMAT_DEBUGGER
} MonoDebugFormat;

#include <fstream>
extern std::ofstream logger;
extern std::wofstream wlogger;

#endif
