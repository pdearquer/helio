/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

using namespace Storage::Structure;

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

Ascii::Ascii()
{
   setName("ASCII");
}
   
   
_bool Ascii::canEncode(_char c)
{
   return isValid((__char)c);
}

_bool Ascii::isValid(__char c)
{
   if(c <= 0x9F)
      return true;
      
   return false;
} 
   
_int Ascii::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{   
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (__char) in->get(i);
      if(isValid(c))
      {
         out->add((_char)c);
      }
      else
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", _name);
         ex->addByte("byte", (_byte)c);
         throw ex;
      }
   }
   return in->length();
}
   
_int Ascii::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (__char)in->get(i);
      if(isValid(c))
         out->add((_byte) c);
      else
      {
         MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
         ex->add("encoding", _name);
         ex->addUInt32("character", (_uint32)c);
         throw ex;
      }
   }
   return in->length();
}

} } } }

