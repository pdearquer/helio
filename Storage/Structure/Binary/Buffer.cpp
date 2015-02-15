/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

Buffer::Buffer()
{
   _length = 0;
   _capacity = 64;
   _data = new _byte[_capacity];
   memset(_data, 0, _capacity);
}
   
Buffer::Buffer(_int cap)
{
   if(cap <= 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.BadCapacity");
      ex->addInt("capacity", cap);
      throw ex;
   }
      
   _length = 0;
   _capacity = cap;
   _data = new _byte[_capacity];
   memset(_data, 0, _capacity);
}
   
Buffer::Buffer(const _byte *data, _int len)
{
   if(len < 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("length", len);
      throw ex;
   }
         
   _length = len;
   _capacity = len;
   if(_capacity < 64)
      _capacity = 64;
      
   _data = new _byte[_capacity];
   memset(_data, 0, _capacity);
   memcpy(_data, data, len);
}
   
Buffer::Buffer(const _byte *data, _int len, _int cap)
{
   if(len < 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("length", len);
      throw ex;
   }
      
   if(cap < len)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("length", len);
      ex->addInt("capacity", cap);
      throw ex;
   }
         
   _length = len;
   _capacity = cap;
      
   _data = new _byte[_capacity];
   memset(_data, 0, _capacity);
   memcpy(_data, data, len);
}
   
Buffer::Buffer(const Buffer *other)
{
   _length = other->_length;
   _capacity = other->_capacity;
   if(_capacity < 64)
      _capacity = 64;
      
   _data = new _byte[_capacity];
   memset(_data, 0, _capacity);
   memcpy(_data, other->_data, _length);
}
   
Buffer::~Buffer()
{
   delete[] _data;
}
   
   
_byte Buffer::get(_int index) const
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return _data[index];
}

_uint16 Buffer::getUInt16BE(_int index) const
{
   if(index < 0 || index + 1 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
#ifdef __HELIO_TARGET_BIG_ENDIAN  
   return *((_uint16 *) &_data[index]);
#else
   _uint16 v = _data[index];
   v = v << 8 | _data[index + 1];
   return v;
#endif
}

_uint16 Buffer::getUInt16LE(_int index) const
{
   if(index < 0 || index + 1 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
#ifdef __HELIO_TARGET_BIG_ENDIAN 
   _uint16 v = _data[index + 1];
   v = v << 8 | _data[index];
   return v;   
#else
   return *((_uint16 *) &_data[index]);
#endif
}

_uint16 Buffer::getUInt16(_int index) const
{
   if(index < 0 || index + 1 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return *((_uint16 *) &_data[index]);
}
   
_uint32 Buffer::getUInt32BE(_int index) const
{
   if(index < 0 || index + 3 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }

#ifdef __HELIO_TARGET_BIG_ENDIAN       
   return *((_uint32 *) &_data[index]);
#else
   _uint32 v = _data[index];
   v = v << 8 | _data[index + 1];
   v = v << 8 | _data[index + 2];
   v = v << 8 | _data[index + 3];
   return v;
#endif   
}

_uint32 Buffer::getUInt32LE(_int index) const
{
   if(index < 0 || index + 3 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
#ifdef __HELIO_TARGET_BIG_ENDIAN
   _uint32 v = _data[index + 3];
   v = v << 8 | _data[index + 2];
   v = v << 8 | _data[index + 1];
   v = v << 8 | _data[index];
   return v;    
#else    
   return *((_uint32 *) &_data[index]);
#endif    
}
   
_uint32 Buffer::getUInt32(_int index) const
{
   if(index < 0 || index + 3 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return *((_uint32 *) &_data[index]);
}
   
      
void Buffer::set(_int index, _byte value)
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   _data[index] = value;
}
   
void Buffer::set(_int index, _byte *b, _int count)
{
   if(index < 0 || count < 0 || index + count > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("count", count);
      ex->addInt("length", _length);
      throw ex;
   }
      
   memcpy(&_data[index], b, count);
}
   
void Buffer::set(_int index, Buffer *b)
{
   if(index < 0 || b->_length < 0 || index + b->_length > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   memcpy(&_data[index], b->_data, b->_length);
}
   
_byte &Buffer::operator [](const _int index)
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return _data[index];
}

   
void Buffer::add(_byte b)
{
   ensureCap(_length + 1);
   
   _data[_length] = b;
   _length++;
}
   
void Buffer::add(_byte *b, _int count)
{
   if(count < 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("count", count);
      throw ex;
   }
      
   ensureCap(_length + count);
   
   memcpy(&_data[_length], b, count);
   _length += count;
}
   
void Buffer::add(Buffer *b)
{
   ensureCap(_length + b->_length);
   
   memcpy(&_data[_length], b->_data, b->_length);
   _length += b->_length;
}
   
void Buffer::add(Buffer *b, _int count, _int start)
{
   if(count < 0 || count > b->_length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("count", count);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   if(start < 0 || start > b->_length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   ensureCap(_length + count);
   memcpy(&_data[_length], &(b->_data[start]), count);
   _length += count;
}
   
void Buffer::add(_int start, Buffer *b)
{
   if(start < 0 || start >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   ensureCap(start + b->_length);
   
   memcpy(&_data[start], b->_data, b->_length);
   
   if(start + b->_length > _length)
      _length = start + b->_length;
}

void Buffer::add(_int start, Buffer *b, _int count)
{
   if(start < 0 || start > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(count < 0 || count > b->_length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("count", count);
      ex->addInt("length", _length);
      throw ex;
   }
      
   ensureCap(start + count);
   
   memcpy(&_data[start], b->_data, count);
   
   if(start + count > _length)
      _length = start + count;
} 

void Buffer::add(_int start, Buffer *b, _int count, _int start2)
{
   if(start < 0 || start > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(start2 < 0 || start2 > b->_length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("buffer.start", start2);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   if(count < 0 || start2 + count > b->_length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("count", count);
      ex->addInt("buffer.start", start2);
      ex->addInt("buffer.length", b->_length);
      throw ex;
   }
      
   ensureCap(start + count);
   
   memcpy(&_data[start], &(b->_data[start2]), count);
   
   if(start + count > _length)
      _length = start + count;
}


void Buffer::addUInt16BE(_uint16 v)
{
   ensureCap(_length + 2);
   
#ifdef __HELIO_TARGET_BIG_ENDIAN    
   *((_uint16 *) &_data[_length]) = v;
#else
   _data[_length] = (_uint8) ((v >> 8) & 0xFF);
   _data[_length + 1] = (_uint8) (v & 0xFF);
#endif

   _length += 2;   
}
   
void Buffer::addUInt16LE(_uint16 v)
{
   ensureCap(_length + 2);
   
#ifdef __HELIO_TARGET_BIG_ENDIAN
   _data[_length] = (_uint8) (v & 0xFF);
   _data[_length + 1] = (_uint8) ((v >> 8) & 0xFF);
#else    
   *((_uint16 *) &_data[_length]) = v;
#endif

   _length += 2;   
}

void Buffer::addUInt16(_uint16 v)
{
   ensureCap(_length + 2);
   
   *((_uint16 *) &_data[_length]) = v;
   _length += 2;
}
 
void Buffer::addUInt32BE(_uint32 v)
{
   ensureCap(_length + 4);

#ifdef __HELIO_TARGET_BIG_ENDIAN   
   *((_uint32 *) &_data[_length]) = v;
#else
   _data[_length] = (_uint8) ((v >> 24) & 0xFF);
   _data[_length + 1] = (_uint8) ((v >> 16) & 0xFF);
   _data[_length + 2] = (_uint8) ((v >> 8) & 0xFF);
   _data[_length + 3] = (_uint8) (v & 0xFF);
#endif   
   _length += 4;
}
   
void Buffer::addUInt32LE(_uint32 v)
{
   ensureCap(_length + 4);

#ifdef __HELIO_TARGET_BIG_ENDIAN
   _data[_length] = (_uint8) (v & 0xFF);
   _data[_length + 1] = (_uint8) ((v >> 8) & 0xFF);
   _data[_length + 2] = (_uint8) ((v >> 16) & 0xFF);
   _data[_length + 3] = (_uint8) ((v >> 24) & 0xFF);   
#else
   *((_uint32 *) &_data[_length]) = v;
#endif   
   _length += 4;
}
     
void Buffer::addUInt32(_uint32 v)
{
   ensureCap(_length + 4);
   
   *((_uint32 *) &_data[_length]) = v;
   _length += 4;
}
   
      
_int Buffer::length() const
{
   return _length;
}

_int Buffer::count() const
{
   return _length;
}
   
_int Buffer::length(_int len)
{
   if(len > _length)
   {
      ensureCap(len);
      memset(&_data[_length], 0, len - _length);
   }

   _length = len;
   
   return _length;
}

_int Buffer::count(_int len)
{
   return length(len);
}
   
_int Buffer::capacity() const
{
   return _capacity;
}
   
_int Buffer::capacity(_int cap)
{
   if(cap <= 0 || _length > cap)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.BadCapacity");
      ex->addInt("capacity", cap);
      ex->addInt("length", _length);
      throw ex;
   }      
      
   _byte *data2 = new _byte[cap];
   memset(data2, 0, cap);
   memcpy(data2, _data, _length);
   delete _data;
   _data = data2;
   
   _capacity = cap;
   return _capacity;
}
   
   
Binary::Buffer *Buffer::sub(_int len) const
{
   if(len < 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("length", len);
      throw ex;
   }
      
   if(len > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("count", len);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return new Buffer(_data, len);
}
   
Binary::Buffer *Buffer::sub(_int start, _int len) const
{
   if(start < 0 || len < 0 || start + len > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("count", len);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return new Buffer(&_data[start], len);
}
   
   
_bool Buffer::empty() const
{
   return (_length == 0);
}   
   
void Buffer::clear()
{
   _length = 0;
}

void Buffer::move(_int count)
{
   erase(0, count);
}

void Buffer::erase(_int index, _int count)
{
   if(count == 0)
      return;
      
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   if(count > 0)
   {
      if(index + count > _length)
      {
         Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
         ex->addInt("count", count);
         ex->addInt("index", index);
         ex->addInt("length", _length);
         throw ex;
      }
         
      Binary::Buffer::memcpy(&_data[index], &_data[index + count], _length - count - index);
      _length -= count;
   }
   else
   {
      count = -count;
      ensureCap(_length + count);
      Binary::Buffer::memcpy(&_data[index + count], &_data[index], _length - index);
      Binary::Buffer::memset(&_data[index], 0, count);
      _length += count;
   }
}
   
   
void Buffer::insert(_int index, _byte b, _int discard)
{
   erase(index, discard - 1);
   
   set(index, b);
}
   
void Buffer::insert(_int index, Buffer *b, _int discard)
{
   erase(index, discard - b->length());
   
   set(index, b);
}
   
   
void Buffer::replace(_byte find, _byte other, _int start)
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }

   for(_int i = start2; i < _length; i++)
      if(_data[i] == find)
         _data[i] = other;
}
     
void Buffer::replace(Buffer *find, Buffer *other, _int start)
{
   _int start2 = start;
   
   if(start2 < 0)
      start2 = _length + start2;
      
   if(start2 < 0 || start2 >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
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
         if(_data[i + j] != find->get(j))      
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


_byte *Buffer::data()
{
   return _data;
}

const _byte *Buffer::data() const
{
   return _data;
}


_bool Buffer::equals(Buffer *other) const
{
   if(_length != other->_length)
      return false;
      
   return (memcmp(_data, other->_data, _length) == 0);
}
  
String Buffer::toString() const
{
   StringBuffer ret = Object::toString();

   ret += (StringBuffer) "[" + _length + "]:";
   
   for(_int i = 0; i < _length; i++)
   {
      ret += " " + (_int) _data[i];
   }
   
   return ret;
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
   
   _byte *data2 = new _byte[cap];
   memset(data2, 0, cap);
   Buffer::memcpy(data2, _data, _length);
   delete[] _data;
   _data = data2;
   
   _capacity = cap;
}


void *Buffer::memcpy(void *dst, const void *org, _int n)
{
   _byte *d = (_byte *) dst;
   _byte *o = (_byte *) org;
   
   if(d < o)
   {
      for(_int i = 0; i < n; i++)
         d[i] = o[i];
   }
   else
   {
      for(_int i = n - 1; i >= 0; i--)
         d[i] = o[i];
   }
   
   return dst;
}

void *Buffer::memset(void *buf, _byte val, _int n)
{
   _byte *p = (_byte *) buf;
   
   for(_int i = 0; i < n; i++)
      p[i] = val;
      
   return buf;
}

_int Buffer::memcmp(const void *buf1, const void *buf2, _int n)
{
   _byte *p1 = (_byte *) buf1;
   _byte *p2 = (_byte *) buf2;
   
   for(_int i = 0; i < n; i++)
   {
      if(p1[i] != p2[i])
      {
         if(p1[i] < p2[i])
            return -1;
         return +1;
      }
   }
   
   return 0;
}
 
_int Buffer::strlen(const void *buf)
{
   _byte *p = (_byte *) buf;
   _int len = 0;
   
   while(p[len] != 0)
      len++;
      
   return len;
}

_int Buffer::strcmp(const void *buf1, const void *buf2)
{
   _byte *p1 = (_byte *) buf1;
   _byte *p2 = (_byte *) buf2;
   
   _int i = 0;
   while(p1[i] != 0)
   {
      if(p2[i] == 0)
         return +1;
         
      if(p1[i] != p2[i])
      {
         if(p1[i] < p2[i])
            return -1;
         return +1;
      }
      
      i++;
   }
   
   if(p2[i] != 0)
      return -1;
      
   return 0;
}

} } }
