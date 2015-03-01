/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

FIFO::FIFO()
{
}
   
   
_int FIFO::length()
{
   return buffer.length();
}
   
   
void FIFO::write(Buffer *buf, _int bytes, _int start)
{
   if(start < 0 || bytes < 0 || start + bytes > buf->length())
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("bytes", bytes);
      ex->addInt("length", buf->length());
      throw ex;
   }
   
   if(bytes == 0)
      bytes = buf->length();
   
   if(bytes == 0)
      return;
      
   buffer.add(buf, bytes, start);
}
   
_int FIFO::read(Buffer *buf, _int bytes, _int start)
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
      
   if(bytes > buffer.length())
      bytes = buffer.length();
      
   buf->length(start + bytes);   
   buf->add(start, &buffer, bytes);
   buffer.move(bytes);
   
   return bytes;
}

} } }

