/* 
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

// RTTI includes
#include <typeinfo>
// Variable arguments
#include <stdarg.h>
// size_t
#include <cstddef>
#undef NULL

/* Target settings */
#define __HELIO_TARGET_LITTLE_ENDIAN
//#define __HELIO_TARGET_BIG_ENDIAN

#define __HELIO_TARGET_GCC


/* Global macros */
#define __UNIQUE_NAME() \
      __unique_##__COUNTER__

#define __CHECK_TYPE(cond) \
      static_assert(cond, #cond)
//      typedef int __UNIQUE_NAME()[(cond) ? 1 : -1]

#define __CHECK_TYPE_BITS(type, bits) \
      __CHECK_TYPE(sizeof(type) == (bits)/8)

template <class Derived, class Base>
class __Base_Test_Template
{
public:
   template <class T> static char test(T *);
   template <class T> static long long test(...);
   static const bool result = sizeof(test<Base>(static_cast<Derived *>(0))) == 1;
};

#define __CHECK_BASE(derived, base) \
      __CHECK_TYPE((__Base_Test_Template<derived, base>::result))


/* Fixed size types (machine dependent) */
typedef unsigned char __uint8;
__CHECK_TYPE_BITS(__uint8, 8);
#define __HELIO_TYPE_UINT8_MIN   ((__uint8)0x00)
#define __HELIO_TYPE_UINT8_MAX   ((__uint8)0xFF)

typedef signed char __sint8;
__CHECK_TYPE_BITS(__sint8, 8);
#define __HELIO_TYPE_SINT8_MIN   ((__sint8)0x80)
#define __HELIO_TYPE_SINT8_MAX   ((__sint8)0x7F)

typedef unsigned short __uint16;
__CHECK_TYPE_BITS(__uint16, 16);
#define __HELIO_TYPE_UINT16_MIN  ((__uint16)0x0000)
#define __HELIO_TYPE_UINT16_MAX  ((__uint16)0xFFFF)

typedef signed short __sint16;
__CHECK_TYPE_BITS(__sint16, 16);
#define __HELIO_TYPE_SINT16_MIN  ((__sint16)0x8000)
#define __HELIO_TYPE_SINT16_MAX  ((__sint16)0x7FFF)

typedef unsigned int __uint32;
__CHECK_TYPE_BITS(__uint32, 32);
#define __HELIO_TYPE_UINT32_MIN  ((__uint32)0x00000000)
#define __HELIO_TYPE_UINT32_MAX  ((__uint32)0xFFFFFFFF)

typedef signed int __sint32;
__CHECK_TYPE_BITS(__sint32, 32);
#define __HELIO_TYPE_SINT32_MIN  ((__sint32)0x80000000)
#define __HELIO_TYPE_SINT32_MAX  ((__sint32)0x7FFFFFFF)

typedef unsigned long long __uint64;
__CHECK_TYPE_BITS(__uint64, 64);
#define __HELIO_TYPE_UINT64_MIN   ((__uint64)0x0000000000000000ULL)
#define __HELIO_TYPE_UINT64_MAX   ((__uint64)0xFFFFFFFFFFFFFFFFULL)

typedef signed long long __sint64;
__CHECK_TYPE_BITS(__sint64, 64);
#define __HELIO_TYPE_SINT64_MIN   ((__sint64)0x8000000000000000ULL)
#define __HELIO_TYPE_SINT64_MAX   ((__sint64)0x7FFFFFFFFFFFFFFFULL)


typedef float __float32;
#define __HELIO_TYPE_FLOAT32_MIN       __FLT_MIN__
#define __HELIO_TYPE_FLOAT32_MAX       __FLT_MAX__
#define __HELIO_TYPE_FLOAT32_EPSILON   __FLT_EPSILON__

typedef double __float64;
#define __HELIO_TYPE_FLOAT64_MIN       __DBL_MIN__
#define __HELIO_TYPE_FLOAT64_MAX       __DBL_MAX__
#define __HELIO_TYPE_FLOAT64_EPSILON   __DBL_EPSILON__

// long double is not well standardized


/* Standard types:
 * These are the types to use in the Helio implementation. 
 * The definition will vary depending on the target machine.
 *
 * Four kinds of types must be differed:
 * - Native: Compile defined; int, float...
 * - Static: Helio implementation; Integer, Float...
 * - Internal: Internally used by the statics: __int, __float...
 * - Standard: Used in Helio: _int, _float...
 *       The standard types can be defined from statics.
 */
typedef bool __bool;
typedef Storage::Structure::Data::Boolean _bool;
//#define __HELIO_TYPE_BOOL_IS_NATIVE
#define __HELIO_TYPE_BOOL_IS_STATIC

typedef __uint32 __char;
typedef Storage::Structure::Data::Character _char;
//#define __HELIO_TYPE_CHAR_IS_NATIVE
#define __HELIO_TYPE_CHAR_IS_STATIC
//#define __HELIO_TYPE_CHAR_IS_INTERNAL
//#define __HELIO_TYPE_CHAR_IS_8BITS
//#define __HELIO_TYPE_CHAR_IS_16BITS
//#define __HELIO_TYPE_CHAR_IS_32BITS

typedef __sint32 __int;
typedef Storage::Structure::Data::Integer _int;
//#define __HELIO_TYPE_INT_IS_NATIVE
#define __HELIO_TYPE_INT_IS_STATIC
#define __HELIO_TYPE_INT_MIN  __HELIO_TYPE_SINT16_MIN
#define __HELIO_TYPE_INT_MAX  __HELIO_TYPE_SINT16_MAX

typedef __float64 __float;
typedef Storage::Structure::Data::Float _float;
//#define __HELIO_TYPE_FLOAT_IS_NATIVE    // Note that the native of _float is "double"
#define __HELIO_TYPE_FLOAT_IS_STATIC
#define __HELIO_TYPE_FLOAT_MIN      __HELIO_TYPE_FLOAT32_MIN
#define __HELIO_TYPE_FLOAT_MAX      __HELIO_TYPE_FLOAT32_MAX
#define __HELIO_TYPE_FLOAT_EPSILON  __HELIO_TYPE_FLOAT32_EPSILON

typedef __uint64 __pointer;   // This type must be integer, not pointer
typedef Storage::Structure::Data::Pointer _pointer;
//#define __HELIO_TYPE_POINTER_IS_NATIVE
#define __HELIO_TYPE_POINTER_IS_STATIC

/* Constant static types (must be always native to avoid memory allocations)
 * Initialize at declaration */
#define const_bool      constexpr __bool
#define const_char      constexpr __char
#define const_int       constexpr __int
#define const_float     constexpr __float
#define const_pointer   constexpr __pointer
#define const_String    constexpr const char *

#define static_const_bool     constexpr static __bool
#define static_const_char     constexpr static __char
#define static_const_int      constexpr static __int
#define static_const_float    constexpr static __float
#define static_const_pointer  constexpr static __pointer
#define static_const_String   constexpr static const char *

/* Binary types
 * This types are always native, i.e. overflows and bit operations are allowed.
 */
typedef __uint8   _byte;
typedef __uint8   _uint8;
typedef __uint16  _uint16;
typedef __uint32  _uint32;
typedef __uint64  _uint64;

/* Null object or pointer */
#define null 0


/* General use packages */
using namespace Storage::Structure::Data;
using namespace Storage::Structure::Text;
using namespace Storage::Structure;
using namespace Component::Error;

