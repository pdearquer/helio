/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

BufferWriter::BufferWriter(Binary::Buffer *buf)
{
   buffer = buf;
}
   
   
void BufferWriter::write(Binary::Buffer *buf, _int bytes, _int start)
{
   if(start < 0 || bytes < 0 || start + bytes > buf->length())
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("bytes", bytes);
      ex->addInt("length", buf->length());
      throw ex;
   }
   
   if(bytes == 0)
      bytes = buf->length();
   
   if(bytes == 0)
      return;
      
   buffer->add(buf, bytes, start);
}

} } }

