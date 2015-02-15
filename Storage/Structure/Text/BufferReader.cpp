/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

BufferReader::BufferReader(Buffer *buf)
{
   _buffer = buf;
   _position = 0;
}
   
   
_int BufferReader::read(Buffer *buf, _int chars, _int start)
{
   if(start < 0 || start > buf->length() || chars < 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("length", buf->length());
      throw ex;
   }
   
   if(chars == 0)
      chars = buf->capacity() - start;
   
   if(chars <= 0)
      return 0;
      
   if(_position + chars > _buffer->length())
      chars = _buffer->length() - _position;      
      
   buf->setLength(start + chars);
   if(chars == 0)
      return 0;
   
   buf->add(start, _buffer, chars, _position);
   _position += chars;
   
   return chars;
}
   
   
_int BufferReader::seek()
{
   return _position;
}
   
_int BufferReader::seek(_int pos)
{
   if(pos < 0 || pos >= _buffer->length())
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", pos);
      ex->addInt("length", _buffer->length());
      throw ex;
   }
   
   _position = pos;
   return _position;
}

} } }
