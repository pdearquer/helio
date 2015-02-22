/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

using namespace Storage::Structure;
using namespace Storage::Structure::Binary::Encodings;

namespace Storage {
namespace Structure {
namespace Text {

const_int Buffer::MIN_CAPACITY;


Buffer::Buffer()
{
   _length = 0;
   _capacity = MIN_CAPACITY;
   _data = new __char[_capacity];
   Binary::Buffer::memset(_data, 0, _capacity * sizeof(_data[0]));
}
   
Buffer::Buffer(_int cap)
{
   if(cap <= 0)
   {
      Error *ex = MAKE_ERROR(Error::Structure::IllegalCapacity);
      ex->addInt("capacity", cap);
      throw ex;
   }
      
   _length = 0;
   _capacity = cap;
   _data = new __char[_capacity];
   Binary::Buffer::memset(_data, 0, _capacity * sizeof(_data[0]));
}

Buffer::Buffer(const Buffer *other)
{
   _length = other->_length;
   _capacity = _length;
   if(_capacity < MIN_CAPACITY)
      _capacity = MIN_CAPACITY;

   _data = new __char[_capacity];
   Binary::Buffer::memset(_data, 0, _capacity * sizeof(_data[0]));
   Binary::Buffer::memcpy(_data, other->_data, _length * sizeof(_data[0]));
}

Buffer::Buffer(const __char *data, _int len)
{
   if(len < 0)
   {
      Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
      ex->addInt("length", len);
      throw ex;
   }
         
   _length = len;
   _capacity = len;
   if(_capacity < MIN_CAPACITY)
      _capacity = MIN_CAPACITY;
      
   _data = new __char[_capacity];
   Binary::Buffer::memset(_data, 0, _capacity * sizeof(_data[0]));
   Binary::Buffer::memcpy(_data, data, len * sizeof(_data[0]));
}
   
Buffer::Buffer(const __char *data, _int len, _int cap)
{
   if(cap <= 0)
   {
      Error *ex = MAKE_ERROR(Error::Structure::IllegalCapacity);
      ex->addInt("capacity", cap);
      throw ex;
   }
   
   if(len < 0 || len > cap)
   {
      Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
      ex->addInt("length", len);
      ex->addInt("capacity", cap);
      throw ex;
   }

   _length = len;
   _capacity = cap;
      
   _data = new __char[_capacity];
   Binary::Buffer::memset(_data, 0, _capacity * sizeof(_data[0]));
   Binary::Buffer::memcpy(_data, data, len * sizeof(_data[0]));
}
   
Buffer::Buffer(const String &str)
{
   _length = str.length();
   _capacity = _length;
   if(_capacity < MIN_CAPACITY)
      _capacity = MIN_CAPACITY;
   
   _data = new __char[_capacity];
   Binary::Buffer::memset(_data, 0, _capacity * sizeof(_data[0]));
   
   _int p = 0;
   for(_int i = 0; i < _length; i++)
   {
      _char c;
      p += UTF_8::chardec(&c, &str._value[p]);
      _data[i] = (__char)c;
   } 
}
   
Buffer::Buffer(_char ch)
{
   _length = 1;
   // A capacity of 1 is used to optimize the character handle
   _capacity = 1;

   _data = new __char[_capacity];
   _data[0] = (__char)ch;
}

Buffer::~Buffer()
{
   delete[] _data;
}


_int Buffer::length() const
{
   return _length;
}

_int Buffer::count() const
{
   return _length;
}
   
void Buffer::setLength(_int len)
{
   if(len < 0)
   {
      Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
      ex->addInt("length", len);
      throw ex;
   }

   if(len > _length)
   {
      ensureCap(len);
      Binary::Buffer::memset(&_data[_length], 0, (len - _length) * sizeof(_data[0]));
   }

   _length = len;
}

void Buffer::setCount(_int len)
{
   setLength(len);
}

_bool Buffer::empty() const
{
   return (_length == 0);
}   
   
void Buffer::clear()
{
   _length = 0;
}

_bool Buffer::hasNull()
{
   for(_int i = 0; i < _length; i++)
      if(_data[i] == 0)
         return true;
   return false;
}

_int Buffer::capacity() const
{
   return _capacity;
}
   
void Buffer::setCapacity(_int cap)
{
   if(cap <= 0)
   {
      Error *ex = MAKE_ERROR(Error::Structure::IllegalCapacity);
      ex->addInt("capacity", cap);
      throw ex;
   }

   if(cap == _capacity)
      return;
      
   if(_length > cap)
      _length = cap;       

   __char *data2 = new __char[cap];
   Binary::Buffer::memset(data2, 0, cap * sizeof(_data[0]));
   Binary::Buffer::memcpy(data2, _data, _length * sizeof(_data[0]));
   delete[] _data;
   _data = data2;
   _capacity = cap;
}


_char Buffer::get(_int index) const
{
   if(index < 0 || index >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
   
   return (_char) _data[index];
}
   
const _char Buffer::operator [](_int index) const
{
   if(index < 0 || index >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return (_char) _data[index];
}


void Buffer::set(_int index, _char c)
{
   if(index < 0 || index >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   _data[index] = (__char)c;
}
   
void Buffer::set(_int index, const String &s)
{
   if(index < 0 || s._length < 0 || index + s._length > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      ex->addInt("string.length", s._length);
      throw ex;
   }
   
   _int p = 0;
   for(_int i = 0; i < s._length; i++)
   {
      _char c;
      p += UTF_8::chardec(&c, &s._value[p]);
      _data[index + i] = (__char)c;
   } 
}
   
void Buffer::set(_int index, const Buffer *b)
{
   if(index < 0 || b->_length < 0 || index + b->_length > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }

   if(this == b)
      return;

   Binary::Buffer::memcpy(&_data[index], b->_data, b->_length * sizeof(_data[0]));
}
   
__char &Buffer::operator [](_int index)
{
   if(index < 0 || index >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return _data[index];
}
   

_int Buffer::indexOf(_char c, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   for(_int i = start2; i < _length; i++)
      if(_data[i] == (__char)c)
         return i;
         
   return -1;
}
   
_int Buffer::indexOf(const String &s, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(s.length() == 0 || s.length() + start2 > _length)
      return -1;
            
   for(_int i = start2; i <= _length - s.length(); i++)
   {
      _bool found = true;
      for(_int j = 0; j < s.length(); j++)
      {
         if(_data[i + j] != (__char)s.get(j))
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
   
_int Buffer::indexOf(const Buffer *b, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(b->_length == 0 || b->_length + start2 > _length)
      return -1;
            
   for(_int i = start2; i <= _length - b->_length; i++)
   {
      _bool found = true;
      for(_int j = 0; j < b->_length; j++)
      {
         if(_data[i + j] != b->_data[j])      
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
   
   
_int Buffer::lastIndexOf(_char c, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   for(_int i = start2; i >= 0; i--)
      if(_data[i] == (__char)c)
         return i;
         
   return -1;
}
   
_int Buffer::lastIndexOf(const String &s, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
   
   start2++;
   if(s.length() == 0 || start2 < s.length())
      return -1;
           
   for(_int i = start2 - s.length(); i >= 0; i--)
   {
      _bool found = true;
      for(_int j = 0; j < s.length(); j++)
      {
         if(_data[i + j] != (__char)s.get(j))
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
   
_int Buffer::lastIndexOf(const Buffer *b, _int start) const
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
   
   start2++;
   if(b->_length == 0 || start2 < b->_length)
      return -1;
           
   for(_int i = start2 - b->_length; i >= 0; i--)
   {
      _bool found = true;
      for(_int j = 0; j < b->_length; j++)
      {
         if(_data[i + j] != b->_data[j])      
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
 
   
_bool Buffer::startsWith(_char c) const
{
   if(_length < 1)
      return false;
      
   return (_data[0] == (__char)c);
}
   
_bool Buffer::startsWith(const String &s) const
{
   if(_length < s._length)
      return false;
      
   for(_int i = 0; i < s._length; i++)
      if(_data[i] != (__char)s.get(i))
         return false;
         
   return true;
}
   
_bool Buffer::startsWith(const Buffer *b) const
{
   if(_length < b->_length)
      return false;
      
   for(_int i = 0; i < b->_length; i++)
      if(_data[i] != b->_data[i])
         return false;
         
   return true;
}
 
_bool Buffer::endsWith(_char c) const
{
   if(_length < 1)
      return false;
      
   return (_data[_length - 1] == (__char)c);
}
   
_bool Buffer::endsWith(const String &s) const
{
   if(_length < s._length)
      return false;
      
   for(_int i = 0; i < s._length; i++)
      if(_data[_length - 1 - i] != (__char)s.get(s._length - 1 - i))
         return false;
      
   return true;
}
   
_bool Buffer::endsWith(const Buffer *b) const
{
   if(_length < b->_length)
      return false;
      
   for(_int i = 0; i < b->_length; i++)
      if(_data[_length - 1 - i] != b->_data[b->_length - 1 - i])
         return false;
      
   return true;
}


void Buffer::add(const __char *data, _int len)
{
   ensureCap(_length + len);
   
   Binary::Buffer::memcpy(&_data[_length], data, len * sizeof(_data[0]));
   _length += len;
}

void Buffer::add(const Buffer *b)
{
   // Note: Consider the case b == this
   
   ensureCap(_length + b->_length);
   
   Binary::Buffer::memcpy(&_data[_length], b->_data, b->_length * sizeof(_data[0]));
   _length += b->_length;
}

void Buffer::add(const Buffer *b, _int count, _int start)
{
   // Note: Consider the case b == this

   if(start < 0 || start > b->_length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
   
   if(count < 0 || count > b->_length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("count", count);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
        
   ensureCap(_length + count);
   Binary::Buffer::memcpy(&_data[_length], &(b->_data[start]), count * sizeof(_data[0]));
   _length += count;
}


void Buffer::add(const Character &c)
{
   ensureCap(_length + 1);

   _data[_length] = c.getUtf32();
   _length++;
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
void Buffer::add(_char c)
{
   ensureCap(_length + 1);

   _data[_length] = (__char)c;
   _length++;
}
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
void Buffer::add(char c)
{
   Character ch = c;
   add(ch);
}
#endif

void Buffer::add(const String &str)
{
   _int len = str._length;
   ensureCap(_length + len);
   
   _int p = 0;
   for(_int i = 0; i < len; i++)
   {
      _char c;
      p += UTF_8::chardec(&c, &str._value[p]);
      _data[_length + i] = (__char)c;
   }
   _length += len;  
}

void Buffer::add(const StringBuffer &str)
{
   add((Buffer *) &str);
}

void Buffer::add(const char *ascii)
{
   _int len = Binary::Buffer::strlen(ascii);
   if(len == 0)
      return;

   ensureCap(_length + len);
   
   for(_int i = 0; i < len; i++)
   {
      Character c = ascii[i];
      _data[_length + i] = c.getUtf32();
   }
   _length += len;
}

void Buffer::add(_int start, const Buffer *b)
{
   // Note: Consider the case b == this

   if(start < 0 || start > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   ensureCap(start + b->_length);
   
   Binary::Buffer::memcpy(&_data[start], b->_data, b->_length * sizeof(_data[0]));
   
   if(start + b->_length > _length)
      _length = start + b->_length;
}
   
void Buffer::add(_int start, const Buffer *b, _int count)
{
   // Note: Consider the case b == this

   if(start < 0 || start > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(count < 0 || count > b->_length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("count", count);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   ensureCap(start + count);
   
   Binary::Buffer::memcpy(&_data[start], b->_data, count * sizeof(_data[0]));
   
   if(start + count > _length)
      _length = start + count;
}  
   
void Buffer::add(_int start, const Buffer *b, _int count, _int start2)
{
   // Note: Consider the case b == this

   if(start < 0 || start > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(start2 < 0 || start2 > b->_length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("buffer.start", start2);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   if(count < 0 || start2 + count > b->_length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("count", count);
      ex->addInt("buffer.start", start2);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   ensureCap(start + count);
   
   Binary::Buffer::memcpy(&_data[start], &(b->_data[start2]), count * sizeof(_data[0]));
   
   if(start + count > _length)
      _length = start + count;
}


Buffer *Buffer::sub(_int length) const
{
   _int actual_len = length;
   if(length <= 0)
      actual_len = _length + length;

   if(actual_len < 0 || actual_len > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
      ex->addInt("sub.length", length);
      ex->addInt("sub.actual", actual_len);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return new Buffer(_data, actual_len);
}
   
Buffer *Buffer::sub(_int start, _int length) const
{
   _int actual_len = length;
   if(length <= 0)
      actual_len = _length - start + length;

   if(start < 0 || actual_len < 0 || start + actual_len > _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("sub.length", length);
      ex->addInt("sub.actual", actual_len);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return new Buffer(&_data[start], actual_len);
}


void Buffer::move(_int count)
{
   erase(0, -count);
}

void Buffer::erase(_int index, _int count)
{
   if(count == 0)
      return;
      
   if(index < 0 || index >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(count > 0)
   {
      if(index + count > _length)
      {
         Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
         ex->addInt("count", count);
         ex->addInt("index", index);
         ex->addInt("length", _length);
         throw ex;
      }
         
      Binary::Buffer::memcpy(&_data[index], &_data[index + count], (_length - count - index) * sizeof(_data[0]));
      _length -= count;
   }
   else
   {
      count = -count;
      ensureCap(_length + count);
      Binary::Buffer::memcpy(&_data[index + count], &_data[index], (_length - index) * sizeof(_data[0]));
      Binary::Buffer::memset(&_data[index], 0, count * sizeof(_data[0]));
      _length += count;
   }
}

void Buffer::insert(_int index, _char c, _int discard)
{
   erase(index, discard - 1);
   
   set(index, c);
}
   
void Buffer::insert(_int index, const String &s, _int discard)
{
   erase(index, discard - s.length());
   
   set(index, s);
}
   
void Buffer::insert(_int index, const Buffer *b, _int discard)
{
   // Note: Consider the case b == this
   if(b == this)
   {
      Buffer *copy = new Buffer(b);
      insert(index, copy, discard);
      delete copy;
      return;
   }

   erase(index, discard - b->length());
   
   set(index, b);
}


void Buffer::replace(_char find, _char other, _int start)
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }

   for(_int i = start2; i < _length; i++)
      if(_data[i] == (__char)find)
         _data[i] = (__char)other;
}
   
void Buffer::replace(const String &find, const String &other, _int start)
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(find.length() == 0 || find.length() + start2 > _length)
      return;
            
   for(_int i = start2; i < _length - find.length(); i++)
   {
      _bool found = true;
      for(_int j = 0; j < find.length(); j++)
      {
         if(_data[i + j] != (__char)find.get(j))
         {
            found = false;
            break;
         }
      }
      
      if(found)
      {
         insert(i, other, find.length());
         i += other.length() - 1;
      }
   }
}
   
void Buffer::replace(const Buffer *find, const Buffer *other, _int start)
{
   // Note: Consider the case find or other == this
   if(find == this)
   {
      Buffer *copy = new Buffer(find);
      replace(copy, other, start);
      delete copy;
      return;
   }
   if(other == this)
   {
      Buffer *copy = new Buffer(other);
      replace(find, copy, start);
      delete copy;
      return;
   }

   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(find->length() == 0 || find->length() + start2 > _length)
      return;
            
   for(_int i = start2; i < _length - find->length(); i++)
   {
      _bool found = true;
      for(_int j = 0; j < find->length(); j++)
      {
         if(_data[i + j] != find->_data[j])      
         {
            found = false;
            break;
         }
      }
      
      if(found)
      {
         insert(i, other, find->length());
         i += other->length() - 1;
      }
   }
}


void Buffer::padRight(_int length, _char c)
{
   if(_length >= length)
      return;
      
   ensureCap(length);
   
   for(_int i = _length; i < length; i++)
      _data[i] = (__char)c;
      
   _length = length;
}

void Buffer::padLeft(_int length, _char c)
{
   if(_length >= length)
      return;
   
   _int remaining = length - _length;
   move(remaining);
   
   for(_int i = 0; i < remaining; i++)
      _data[i] = (__char)c;
}

void Buffer::reverse()
{
   for(_int i = 0; i < _length / 2; i++)
   {
      _int back = _length - 1 - i;
      __char tmp = _data[i];
      _data[i] = _data[back];
      _data[back] = tmp;
   }
}


_int Buffer::compare(const Buffer *other) const
{
   for(_int i = 0; i < _length; i++)
   {
      if(other->_length == i)
         return +1;
          
      if(_data[i] != other->_data[i])
      {
         if(_data[i] < other->_data[i])
            return -1;
         else
            return +1;
      }
   }
   
   if(_length == other->_length)
      return 0;
   return -1; 
}

_bool Buffer::equals(const Buffer *other) const
{
   if(_length != other->_length)
      return false;
      
   return (Binary::Buffer::memcmp(_data, other->_data, _length * sizeof(_data[0])) == 0);
}
  
String Buffer::toString() const
{
   String ret(this);
   return ret;
}


__char *Buffer::data()
{
   return _data;
}

void Buffer::ensureCap(_int min)
{
   if(min <= _capacity)
      return;
   
   _int cap = _capacity;
        
   while(cap < min)
   {
      if(cap < 512)
         cap = cap * 2;
      else
         cap += 512;
   }
   
   __char *data2 = new __char[cap];
   Binary::Buffer::memset(data2, 0, cap * sizeof(_data[0]));
   Binary::Buffer::memcpy(data2, _data, _length * sizeof(_data[0]));
   delete[] _data;      
   _data = data2;
   
   _capacity = cap;
}

} } }

