/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

ISO_8859_1::ISO_8859_1()
{
   setName("ISO 8859-1");
}
   
   
_bool ISO_8859_1::canEncode(_char c)
{
   return ((__char)c <= 0xFF);
}
   
_int ISO_8859_1::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{   
   for(_int i = 0; i < in->length(); i++)
   {
      out->add((_char)(__char)in->get(i));
   }
   return in->length();
}
   
_int ISO_8859_1::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (_char)in->get(i);
      
      if(c <= 0xFF)
         out->add((_byte) c);
      else
      {
         Exception *ex = MAKE_ERROR(Exception::Format::InvalidCharacter);
         ex->add("encoding", _name);
         ex->addUInt32("character", c);
         throw ex;
      }
   }
   return in->length();
}

} } } }

