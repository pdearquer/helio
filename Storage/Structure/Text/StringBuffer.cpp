/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

StringBuffer::StringBuffer()
{
}

StringBuffer::StringBuffer(const StringBuffer &other)
{
   add(other);
}

StringBuffer::StringBuffer(const Buffer *buf)
{
   add(buf);
}

StringBuffer::StringBuffer(const __char *data, _int len)
{
   add(data, len);
}

StringBuffer::StringBuffer(const String &str)
{
   add(str);
}

StringBuffer::StringBuffer(const char *ascii)
{
   add(ascii);
}

StringBuffer::StringBuffer(const Character &c)
{
   add(c);
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
StringBuffer::StringBuffer(_char c)
{
   add(c);
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
StringBuffer::StringBuffer(char ascii)
{
   Character c = ascii;
   add(c);
}
#endif

StringBuffer::StringBuffer(const Object &o)
{
   add(o.toString());
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
StringBuffer::StringBuffer(_int num)
{
   add(Integer(num).toString());
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
StringBuffer::StringBuffer(int num)
{
   add(Integer(num).toString());
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
StringBuffer::StringBuffer(_float num)
{
   add(Float(num).toString());
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
StringBuffer::StringBuffer(double num)
{
   add(Float(num).toString());
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
StringBuffer::StringBuffer(_bool b)
{
   add(Boolean(b).toString());
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
StringBuffer::StringBuffer(bool b)
{
   add(Boolean(b).toString());
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
StringBuffer::StringBuffer(_pointer p)
{
   add(Pointer(p).toString());
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
StringBuffer::StringBuffer(void *p)
{
   add(Pointer(p).toString());
}
#endif


StringBuffer StringBuffer::sub(_int length) const
{
   _int actual_len = length;
   if(length <= 0)
      actual_len = _length + length;

   if(actual_len < 0 || actual_len > _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("sub.length", length);
      ex->addInt("sub.actual", actual_len);
      ex->addInt("length", _length);
      throw ex;
   }
      
   StringBuffer ret(_data, actual_len);
   return ret;
}
   
StringBuffer StringBuffer::sub(_int start, _int length) const
{
   _int actual_len = length;
   if(length <= 0)
      actual_len = _length - start + length;

   if(start < 0 || actual_len < 0 || start + actual_len > _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("sub.length", length);
      ex->addInt("sub.actual", actual_len);
      ex->addInt("length", _length);
      throw ex;
   }

   StringBuffer ret(&_data[start], actual_len);
   return ret;
}
   

void StringBuffer::operator =(const StringBuffer &other)
{
   // Please consider the case &other == this
   if(&other != this)
   {
      clear();
      add(other);
   }
}

void StringBuffer::operator =(const char *ascii)
{
   clear();
   add(ascii);
}


_bool StringBuffer::operator ==(const StringBuffer &other) const
{
   return equals(&other);
}

_bool StringBuffer::operator !=(const StringBuffer &other) const
{
   return !equals(&other);
}

_bool StringBuffer::operator <(const StringBuffer &other) const
{
   return (compare(&other) < 0);
}

_bool StringBuffer::operator >(const StringBuffer &other) const
{
   return (compare(&other) > 0);
}

_bool StringBuffer::operator <=(const StringBuffer &other) const
{
   return (compare(&other) <= 0);
}

_bool StringBuffer::operator >=(const StringBuffer &other) const
{
   return (compare(&other) >= 0);
}

_bool StringBuffer::operator ==(const char *ascii) const
{
   StringBuffer other = ascii;
   return equals(&other);
}

_bool StringBuffer::operator !=(const char *ascii) const
{
   StringBuffer other = ascii;
   return !equals(&other);
}

_bool StringBuffer::operator <(const char *ascii) const
{
   StringBuffer other = ascii;
   return (compare(&other) < 0);
}

_bool StringBuffer::operator >(const char *ascii) const
{
   StringBuffer other = ascii;
   return (compare(&other) > 0);
}

_bool StringBuffer::operator <=(const char *ascii) const
{
   StringBuffer other = ascii;
   return (compare(&other) <= 0);
}

_bool StringBuffer::operator >=(const char *ascii) const
{
   StringBuffer other = ascii;
   return (compare(&other) >= 0);
}


void StringBuffer::operator +=(const StringBuffer &other)
{
   add(other);
}

void StringBuffer::operator +=(const String &str)
{
   add(str);
}

void StringBuffer::operator +=(const char *ascii)
{
   add(ascii);
}

void StringBuffer::operator +=(const Character &c)
{
   add(c);
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
void StringBuffer::operator +=(_char ch)
{
   add(Character(ch));
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
void StringBuffer::operator +=(char ascii)
{
   add(Character(ascii));
}
#endif

void StringBuffer::operator +=(const Object &o)
{
   add(o.toString());
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
void StringBuffer::operator +=(_int num)
{
   add(Integer(num).toString());
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
void StringBuffer::operator +=(int num)
{
   add(Integer(num).toString());
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
void StringBuffer::operator +=(_float num)
{
   add(Float(num).toString());
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
void StringBuffer::operator +=(double num)
{
   add(Float(num).toString());
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
void StringBuffer::operator +=(_bool b)
{
   add(Boolean(b).toString());
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
void StringBuffer::operator +=(bool b)
{
   add(Boolean(b).toString());
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
void StringBuffer::operator +=(_pointer p)
{
   add(Pointer(p).toString());
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
void StringBuffer::operator +=(void *p)
{
   add(Pointer(p).toString());
}
#endif


const StringBuffer StringBuffer::operator +(const StringBuffer &other) const
{
   StringBuffer ret(*this);
   ret.add(other);
   return ret;
}

const StringBuffer StringBuffer::operator +(const String &str) const
{
   StringBuffer ret(*this);
   ret.add(str);
   return ret;
}

const StringBuffer StringBuffer::operator +(const char *ascii) const
{
   StringBuffer ret(*this);
   ret.add(ascii);
   return ret;
}

const StringBuffer StringBuffer::operator +(const Character &c) const
{
   StringBuffer ret(*this);
   ret.add(c);
   return ret;
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const StringBuffer StringBuffer::operator +(_char ch) const
{
   StringBuffer ret(*this);
   ret.add(Character(ch));
   return ret;
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const StringBuffer StringBuffer::operator +(char ascii) const
{
   StringBuffer ret(*this);
   ret.add(Character(ascii));
   return ret;
}
#endif

const StringBuffer StringBuffer::operator +(const Object &o) const
{
   StringBuffer ret(*this);
   ret.add(o.toString());
   return ret;
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
const StringBuffer StringBuffer::operator +(_int num) const
{
   StringBuffer ret(*this);
   ret.add(Integer(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const StringBuffer StringBuffer::operator +(int num) const
{
   StringBuffer ret(*this);
   ret.add(Integer(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const StringBuffer StringBuffer::operator +(_float num) const
{
   StringBuffer ret(*this);
   ret.add(Float(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const StringBuffer StringBuffer::operator +(double num) const
{
   StringBuffer ret(*this);
   ret.add(Float(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const StringBuffer StringBuffer::operator +(_bool b) const
{
   StringBuffer ret(*this);
   ret.add(Boolean(b).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const StringBuffer StringBuffer::operator +(bool b) const
{
   StringBuffer ret(*this);
   ret.add(Boolean(b).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const StringBuffer StringBuffer::operator +(_pointer p) const
{
   StringBuffer ret(*this);
   ret.add(Pointer(p).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const StringBuffer StringBuffer::operator +(void *p) const
{
   StringBuffer ret(*this);
   ret.add(Pointer(p).toString());
   return ret;
}
#endif

} } }

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(sb);
   return ret;
}

const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(ascii);
   ret.add(sb);
   return ret;
}

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::Character &c, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(c);
   ret.add(sb);
   return ret;
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const Storage::Structure::Text::StringBuffer operator +(_char ch, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(ch);
   ret.add(sb);
   return ret;
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(char ascii, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(ascii);
   ret.add(sb);
   return ret;
}
#endif

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::Object &o, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(o);
   ret.add(sb);
   return ret;
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_int num, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(num);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(int num, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(num);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_float num, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(num);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(double num, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(num);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_bool b, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(b);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(bool b, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(b);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_pointer p, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(p);
   ret.add(sb);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(void *p, const Storage::Structure::Text::StringBuffer &sb)
{
   Storage::Structure::Text::StringBuffer ret(p);
   ret.add(sb);
   return ret;
}
#endif


const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str1, const Storage::Structure::Data::String &str2)
{
   Storage::Structure::Text::StringBuffer ret(str1);
   ret.add(str2);
   return ret;
}

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const char *ascii)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(ascii);
   return ret;
}

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const Storage::Structure::Data::Character &c)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(c);
   return ret;
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _char ch)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Character(ch));
   return ret;
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, char ascii)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Character(ascii));
   return ret;
}
#endif

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, const Object &o)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(o.toString());
   return ret;
}


#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _int num)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Integer(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, int num)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Integer(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _float num)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Float(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, double num)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Float(num).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _bool b)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Boolean(b).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, bool b)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Boolean(b).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, _pointer p)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Pointer(p).toString());
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::String &str, void *p)
{
   Storage::Structure::Text::StringBuffer ret(str);
   ret.add(Pointer(p).toString());
   return ret;
}
#endif


const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret(ascii);
   ret.add(str);
   return ret;
}

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::Character &c, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(c);
   ret.add(str);
   return ret;
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
const Storage::Structure::Text::StringBuffer operator +(_char ch, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Character(ch));
   ret.add(str);
   return ret;
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(char ascii, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Character(ascii));
   ret.add(str);
   return ret;
}
#endif

const Storage::Structure::Text::StringBuffer operator +(const Storage::Structure::Data::Object &o, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(o.toString());
   ret.add(str);
   return ret;
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_int num, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Integer(num).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(int num, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Integer(num).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_float num, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Float(num).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(double num, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Float(num).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_bool b, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Boolean(b).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(bool b, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Boolean(b).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
const Storage::Structure::Text::StringBuffer operator +(_pointer p, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Pointer(p).toString());
   ret.add(str);
   return ret;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
const Storage::Structure::Text::StringBuffer operator +(void *p, const Storage::Structure::Data::String &str)
{
   Storage::Structure::Text::StringBuffer ret;
   ret.add(Pointer(p).toString());
   ret.add(str);
   return ret;
}
#endif


const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Storage::Structure::Data::Character &c)
{
   Storage::Structure::Text::StringBuffer ret(ascii);
   ret.add(c);
   return ret;
}

const Storage::Structure::Text::StringBuffer operator +(const char *ascii, const Storage::Structure::Data::Object &o)
{
   Storage::Structure::Text::StringBuffer ret(ascii);
   ret.add(o.toString());
   return ret;
}

