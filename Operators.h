/* 
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/* External operators */

#ifdef __HELIO_STORAGE_STRUCTURE_DATA_INTEGER
#ifndef __HELIO_TYPE_INT_IS_STATIC
_bool operator ==(_int a, const Storage::Structure::Data::Integer &b);
_bool operator !=(_int a, const Storage::Structure::Data::Integer &b);
_bool operator <(_int a, const Storage::Structure::Data::Integer &b);
_bool operator >(_int a, const Storage::Structure::Data::Integer &b);
_bool operator <=(_int a, const Storage::Structure::Data::Integer &b);
_bool operator >=(_int a, const Storage::Structure::Data::Integer &b);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
_bool operator ==(int a, const Storage::Structure::Data::Integer &b);
_bool operator !=(int a, const Storage::Structure::Data::Integer &b);
_bool operator <(int a, const Storage::Structure::Data::Integer &b);
_bool operator >(int a, const Storage::Structure::Data::Integer &b);
_bool operator <=(int a, const Storage::Structure::Data::Integer &b);
_bool operator >=(int a, const Storage::Structure::Data::Integer &b);
#endif

_bool operator ==(size_t a, const Storage::Structure::Data::Integer &b);
_bool operator !=(size_t a, const Storage::Structure::Data::Integer &b);
_bool operator <(size_t a, const Storage::Structure::Data::Integer &b);
_bool operator >(size_t a, const Storage::Structure::Data::Integer &b);
_bool operator <=(size_t a, const Storage::Structure::Data::Integer &b);
_bool operator >=(size_t a, const Storage::Structure::Data::Integer &b);

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Data::Integer operator +(_int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator -(_int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator *(_int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator /(_int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator %(_int a, const Storage::Structure::Data::Integer &b);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Data::Integer operator +(int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator -(int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator *(int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator /(int a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator %(int a, const Storage::Structure::Data::Integer &b);
#endif

const Storage::Structure::Data::Integer operator +(size_t a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator -(size_t a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator *(size_t a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator /(size_t a, const Storage::Structure::Data::Integer &b);
const Storage::Structure::Data::Integer operator %(size_t a, const Storage::Structure::Data::Integer &b);
#endif


#ifdef __HELIO_STORAGE_STRUCTURE_DATA_FLOAT
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
_bool operator ==(_float a, const Storage::Structure::Data::Float &b);
_bool operator !=(_float a, const Storage::Structure::Data::Float &b);
_bool operator <(_float a, const Storage::Structure::Data::Float &b);
_bool operator >(_float a, const Storage::Structure::Data::Float &b);
_bool operator <=(_float a, const Storage::Structure::Data::Float &b);
_bool operator >=(_float a, const Storage::Structure::Data::Float &b);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
_bool operator ==(double a, const Storage::Structure::Data::Float &b);
_bool operator !=(double a, const Storage::Structure::Data::Float &b);
_bool operator <(double a, const Storage::Structure::Data::Float &b);
_bool operator >(double a, const Storage::Structure::Data::Float &b);
_bool operator <=(double a, const Storage::Structure::Data::Float &b);
_bool operator >=(double a, const Storage::Structure::Data::Float &b);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Data::Float operator +(_float a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator -(_float a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator *(_float a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator /(_float a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator %(_float a, const Storage::Structure::Data::Float &b);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Data::Float operator +(double a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator -(double a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator *(double a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator /(double a, const Storage::Structure::Data::Float &b);
const Storage::Structure::Data::Float operator %(double a, const Storage::Structure::Data::Float &b);
#endif
#endif


#ifdef __HELIO_STORAGE_STRUCTURE_TEXT_STRINGBUFFER
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const Storage::Structure::Text::StringBuffer &sb);
const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Storage::Structure::Text::StringBuffer &sb);
const Storage::Structure::Text::StringBuffer operator +(const Character &c, const Storage::Structure::Text::StringBuffer &sb);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const Storage::Structure::Text::StringBuffer operator +(_char ch, const Storage::Structure::Text::StringBuffer &sb);
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(char ascii, const Storage::Structure::Text::StringBuffer &sb);
#endif

const Storage::Structure::Text::StringBuffer operator +(const Object &o, const Storage::Structure::Text::StringBuffer &sb);

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_int num, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(int num, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_float num, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(double num, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_bool b, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(bool b, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_pointer p, const Storage::Structure::Text::StringBuffer &sb);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(void *p, const Storage::Structure::Text::StringBuffer &sb);
#endif

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str1, const Storage::Structure::Data::String &str2);
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const char * ascii);
template <size_t N>
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const char (&ascii)[N])
{
   return (Storage::Structure::Text::StringBuffer)str + (const char *)ascii;
}
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const Character &c);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _char ch);
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, char ascii);
#endif

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const Object &o);

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _int num);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, int num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _float num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, double num);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _bool b);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, bool b);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _pointer p);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, void *p);
#endif


const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Storage::Structure::Data::String &str);
const Storage::Structure::Text::StringBuffer operator +(const Character &c, const Storage::Structure::Data::String &str);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const Storage::Structure::Text::StringBuffer operator +(_char ch, const Storage::Structure::Data::String &str);
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(char ascii, const Storage::Structure::Data::String &str);
#endif

const Storage::Structure::Text::StringBuffer operator +(const Object &o, const Storage::Structure::Data::String &str);

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_int num, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(int num, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_float num, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(double num, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_bool b, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(bool b, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_pointer p, const Storage::Structure::Data::String &str);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(void *p, const Storage::Structure::Data::String &str);
#endif


const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Character &c);
const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Object &o);
#endif

