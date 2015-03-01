/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

BufferReader::BufferReader(Binary::Buffer *buf)
{
   buffer = buf;
   position = 0;
}
   
   
_int BufferReader::read(Binary::Buffer *buf, _int bytes, _int start)
{
   if(start < 0 || start > buf->length() || bytes < 0)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("bytes", bytes);
      ex->addInt("length", buf->length());
      throw ex;
   }
   
   if(bytes == 0)
      bytes = buf->capacity() - start;
   
   if(bytes <= 0)
      return 0;
      
   if(position + bytes > buffer->length())
      bytes = buffer->length() - position;      
      
   buf->length(start + bytes);
   if(bytes == 0)
      return 0;
   
   buf->add(start, buffer, bytes, position);
   position += bytes;
   
   return bytes;
}
   
   
_int BufferReader::seek()
{
   return position;
}
   
_int BufferReader::seek(_int pos)
{
   if(pos < 0 || pos >= buffer->length())
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("position", pos);
      ex->addInt("length", buffer->length());
      throw ex;
   }
   
   position = pos;
   return position;
}

} } }

