/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

BufferWriter::BufferWriter(Buffer *buf)
{
   _buffer = buf;
}
   
   
void BufferWriter::write(Buffer *buf, _int chars, _int start)
{
   if(start < 0 || chars < 0 || start + chars > buf->length())
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("characters", chars);
      ex->addInt("length", buf->length());
      throw ex;
   }
   
   if(chars == 0)
      chars = buf->length();
   
   if(chars == 0)
      return;
      
   _buffer->add(buf, chars, start);
}


void BufferWriter::write(String str)
{
   _buffer->add(str);
}

} } }

