/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

using namespace Storage::Structure::Binary::Encodings;

namespace Storage {
namespace Structure {
namespace Data {

String::String()
{
   _value = null;
   _length = 0;
   _bytes = 0;
}

String::String(const String &other)
{
   _length = other._length;
   _bytes = other._bytes;
   
   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}

String::String(const String *other)
{
   _length = other->_length;
   _bytes = other->_bytes;
   
   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other->_value, _bytes);
      _value[_bytes] = 0;
   }
}

String::String(const _uint8 *utf8, _int length)
{
   if(length < 0)
   {
      MAKE_ERROR(ex, Error::Structure::InvalidLength);
      ex->addInt("length", length);
      throw ex;
   }
      
   _length = length;
   _bytes = 0;
   
   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _bytes = Utf8::charbytes(utf8, _length);
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, utf8, _bytes);
      _value[_bytes] = 0;
   }
}

String::String(const Storage::Structure::Text::Buffer *buf)
{
   _length = buf->length();
   _bytes = 0;
   
   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      for(_int i = 0; i < _length; i++)
         _bytes += Utf8::charlen(buf->get(i));
      
      _value = new _uint8[_bytes + 1];
      
      _int p = 0;
      for(_int i = 0; i < _length; i++)
         p += Utf8::charenc(buf->get(i), &_value[p]);
      _value[_bytes] = 0;
   }
}

String::String(const Storage::Structure::Text::StringBuffer &buf)
{
   _length = buf.length();
   _bytes = 0;
   
   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      for(_int i = 0; i < _length; i++)
         _bytes += Utf8::charlen(buf.get(i));
      
      _value = new _uint8[_bytes + 1];
      
      _int p = 0;
      for(_int i = 0; i < _length; i++)
         p += Utf8::charenc(buf.get(i), &_value[p]);
      _value[_bytes] = 0;
   }
}

String::String(const char *ascii)
{
   _length = Binary::Buffer::strlen(ascii);   
   _bytes = _length;
   
   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      for(_int i = 0; i < _length; i++)
      {
         _uint32 utf32 = (_uint32)ascii[i];
         if(!Storage::Structure::Binary::Encodings::Ascii::isValid(utf32))
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("encoding", "ASCII");
            ex->addUInt32("character", utf32);
            throw ex;
         }
      }
      
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, ascii, _bytes);
      _value[_bytes] = 0;
   }
}

String::String(const Character &c)
{
   _length = 1;
   _bytes = Utf8::charlen(c);
   _value = new _uint8[_bytes + 1];
   Utf8::charenc(c, _value);
   _value[_bytes] = 0;
}  

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
String::String(_char ch)
{
   Character c = ch;
   _length = 1;
   _bytes = Utf8::charlen(c);
   _value = new _uint8[_bytes + 1];
   Utf8::charenc(c, _value);
   _value[_bytes] = 0;
}
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
String::String(char ascii)
{
   Character c = ascii;
   _length = 1;
   _bytes = Utf8::charlen(c);
   _value = new _uint8[_bytes + 1];
   Utf8::charenc(c, _value);
   _value[_bytes] = 0;
}
#endif

String::String(const Object &o)
{
   String other = o.toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
String::String(_int num)
{
   String other = Integer(num).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif
   
#ifndef __HELIO_TYPE_INT_IS_NATIVE
String::String(int num)
{
   String other = Integer(num).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
String::String(_float num)
{
   String other = Float(num).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif
   
#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
String::String(double num)
{
   String other = Float(num).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
String::String(_bool b)
{
   String other = Boolean(b).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif
   
#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
String::String(bool b)
{
   String other = Boolean(b).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
String::String(_pointer p)
{
   String other = Pointer(p).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif
   
#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
String::String(void *p)
{
   String other = Pointer(p).toString();

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}
#endif

String::~String()
{
   if(_value != null)
      delete[] _value;
}


_int String::length() const
{
   return _length;
}

_int String::count() const
{
   return _length;
}

_bool String::isEmpty() const
{
   return (_length == 0);
}


_char String::get(_int index) const
{
   if(index < 0 || index >= _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   _char c;
   _int p = Utf8::charbytes(_value, index);
   Utf8::chardec(&c, &_value[p]);
   return c;
}


_int String::compare(const String *other) const
{
   return compare(*other, false);
}

_int String::compare(const String &other, _bool igncase) const
{
   if(_value == null)
      return (other._value == null);
   if(other._value == null)
      return false;

   _int p1 = 0;
   _int p2 = 0;
   for(_int i = 0; i < _length; i++)
   {
      if(other._length == i)
         return +1;
         
      _char c1, c2;
      p1 += Utf8::chardec(&c1, &_value[p1]);
      p2 += Utf8::chardec(&c2, &other._value[p2]);
      
      if(!Character(c1).equals(c2, igncase))
      {
         return Character(c1).compare(c2, igncase);
      }
   }
   
   if(_length == other._length)
      return 0;
   return -1; 
}

_bool String::equals(const String *other) const
{
   return equals(*other, false);
}

_bool String::equals(const String &other, _bool igncase) const
{
   if(_length != other._length)
      return false;
   
   if(_value == null)
      return (other._value == null);
   if(other._value == null)
      return false;

   if(!igncase)
   {
      if(_bytes != other._bytes)
         return false;
         
      return (Binary::Buffer::memcmp(_value, other._value, _bytes) == 0);
   }
   else
   {
      _int p1 = 0;
      _int p2 = 0;
      for(_int i = 0; i < _length; i++)
      {
         _char c1, c2;
         p1 += Utf8::chardec(&c1, &_value[p1]);
         p2 += Utf8::chardec(&c2, &other._value[p2]);

         if(!Character(c1).equals(c2, true))
            return false;
      }
      return true;
   }
}

String *String::clone() const
{
   return new String(this);
}

_uint32 String::makeHash() const
{
   _uint32 hash = (_uint32)(_length + _bytes);
   for(_int i = 0; i < _bytes; i++)
      hash = (hash << 5) - hash + _value[i];
   return hash;
}


Text::Buffer *String::toBuffer() const
{
   return new Text::Buffer(*this);
}


String String::sub(_int length) const
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
      
   if(actual_len == 0)
      return String();
      
   return String(_value, actual_len);
}
   
String String::sub(_int start, _int length) const
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
      
   if(actual_len == 0)
      return String();
         
   _int p = Utf8::charbytes(_value, start);
   return String(&_value[p], actual_len);
}
   
   
String String::toLowerCase() const
{
   StringBuffer buf;
   _int p = 0;
   for(_int i = 0; i < _length; i++)
   {
      _char c;
      p += Utf8::chardec(&c, &_value[p]);
      buf.add(Character(c).toLowerCase());
   }
   
   return buf.toString();
}
   
String String::toUpperCase() const
{
   StringBuffer buf;
   _int p = 0;
   for(_int i = 0; i < _length; i++)
   {
      _char c;
      p += Utf8::chardec(&c, &_value[p]);
      buf.add(Character(c).toUpperCase());
   }
   
   return buf.toString();
}
   
   
_int String::indexOf(_char c, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   for(_int i = start2; i < _length; i++)
      if(get(i) == c)
         return i;
         
   return -1;
}

_int String::indexOf(const String &s, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(s._length == 0 || s._length + start2 > _length)
      return -1;
            
   for(_int i = start2; i <= _length - s._length; i++)
   {
      _bool found = true;
      for(_int j = 0; j < s._length; j++)
      {
         if(get(i + j) != s.get(j))      
         {
            found = false;
            break;
         }
      }
      
      if(found)
         return i;
   }
         
   return -1;
}

   
_int String::lastIndexOf(_char c, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   for(_int i = start2; i >= 0; i--)
      if(get(i) == c)
         return i;
         
   return -1;
}
   
_int String::lastIndexOf(const String &s, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
   
   start2++;
   if(s._length == 0 || start2 < s._length)
      return -1;
           
   for(_int i = start2 - s._length; i >= 0; i--)
   {
      _bool found = true;
      for(_int j = 0; j < s._length; j++)
      {
         if(get(i + j) != s.get(j))      
         {
            found = false;
            break;
         }
      }
      
      if(found)
         return i;
   }
         
   return -1;
}


_bool String::startsWith(_char c) const
{
   if(_length < 1)
      return false;
      
   return (get(0) == c);
}

_bool String::startsWith(const String &s) const
{
   if(_length < s._length)
      return false;
      
   for(_int i = 0; i < s._length; i++)
      if(get(i) != s.get(i))
         return false;
         
   return true;
}

_bool String::endsWith(_char c) const
{
   if(_length < 1)
      return false;
      
   return (get(_length - 1) == c);
}

_bool String::endsWith(const String &s) const
{
   if(_length < s._length)
      return false;
      
   for(_int i = 0; i < s._length; i++)
      if(get(_length - 1 - i) != s.get(s._length - 1 - i))
         return false;
      
   return true;
}


void String::operator =(const String &other)
{
   if(this == &other)
      return;

   if(_value != null)
      delete _value;

   _length = other._length;
   _bytes = other._bytes;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, other._value, _bytes);
      _value[_bytes] = 0;
   }
}

void String::operator =(const char *ascii)
{
   if(_value != null)
      delete _value;

   _length = Binary::Buffer::strlen(ascii);
   _bytes = _length;

   if(_length == 0)
   {
      _value = null;
   }
   else
   {
      for(_int i = 0; i < _length; i++)
      {
         _uint32 utf32 = (_uint32)ascii[i];
         if(!Storage::Structure::Binary::Encodings::Ascii::isValid(utf32))
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("encoding", "ASCII");
            ex->addUInt32("character", utf32);
            throw ex;
         }
      }

      _value = new _uint8[_bytes + 1];
      Binary::Buffer::memcpy(_value, ascii, _bytes);
      _value[_bytes] = 0;
   }
}


const Character String::operator [](const _int index) const
{
   return get(index);
}


_bool String::operator ==(const String &other) const
{
   return equals(other);
}

_bool String::operator !=(const String &other) const
{
   return !equals(other);
}

_bool String::operator <(const String &other) const
{
   return (compare(other) < 0);
}

_bool String::operator >(const String &other) const
{
   return (compare(other) > 0);
}

_bool String::operator <=(const String &other) const
{
   return (compare(other) <= 0);
}

_bool String::operator >=(const String &other) const
{
   return (compare(other) >= 0);
}



_bool String::operator ==(const char *ascii) const
{
   // No validation is done for comparisons
   return (Binary::Buffer::strcmp(getUTF8(), ascii) == 0);
}

_bool String::operator !=(const char *ascii) const
{
   // No validation is done for comparisons
   return (Binary::Buffer::strcmp(getUTF8(), ascii) != 0);
}

_bool String::operator <(const char *ascii) const
{
   // No validation is done for comparisons
   return (Binary::Buffer::strcmp(getUTF8(), ascii) < 0);
}

_bool String::operator >(const char *ascii) const
{
   // No validation is done for comparisons
   return (Binary::Buffer::strcmp(getUTF8(), ascii) > 0);
}

_bool String::operator <=(const char *ascii) const
{
   // No validation is done for comparisons
   return (Binary::Buffer::strcmp(getUTF8(), ascii) <= 0);
}

_bool String::operator >=(const char *ascii) const
{
   // No validation is done for comparisons
   return (Binary::Buffer::strcmp(getUTF8(), ascii) >= 0);
}


const _uint8 *String::getUTF8() const
{
   if(_value == null)
      return (const _uint8 *)"";
   return (const _uint8 *)_value;
}

} } }

