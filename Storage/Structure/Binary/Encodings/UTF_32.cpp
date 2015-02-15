/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

UTF_32::UTF_32()
{
   setName("UTF-32");
#ifdef __HELIO_TARGET_BIG_ENDIAN
   _endian = true;
#else
   _endian = false;
#endif
   _bom = false;
}
  
UTF_32::UTF_32(_bool bigEndian)
{
   setName("UTF-32");
   _endian = bigEndian;
   _bom = false;
} 
   
   
_bool UTF_32::canEncode(_char c)
{
   return true;
}
   
_int UTF_32::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{  
   _int len = (in->length() / 4) * 4;
     
   for(_int i = 0; i < len; i += 4)
   {
      _char c;
      __char w;
      
      if(_endian)
         w = (__char)in->getUInt32BE(i);
      else
         w = (__char)in->getUInt32LE(i);
      
      if(w == 0xFEFF)
      {
         _bom = true;
         continue;
      }
      else if(w == 0xFFFE)
      {
         _bom = true;
         _endian = !_endian;
         continue;
      }
      
      try
      {
         c = w;
      }
      catch(Exception *e)
      {
         if(e->id() != "Storage.Structure.InvalidCharacter")
            throw e;
         delete e;

         Exception *ex = MAKE_ERROR("Storage.Structure.Binary.Encodings.InvalidByte");
         ex->add("encoding", _name);
         ex->addUInt32("code", w);
         throw ex;
      }
      
      out->add(c);
   }
   
   if(finish && len != in->length())
      ERROR("Storage.Structure.Binary.Encodings.UnexpectedEnd");
      
   return len;
}
   
_int UTF_32::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   if(_bom)
   {
      if(_endian)
         out->addUInt32BE(0xFEFF);
      else
         out->addUInt32LE(0xFEFF);
         
      _bom = false;
   } 
   
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (__char)in->get(i);
      if(!Character::isValid(c))
      {
         Exception *ex = MAKE_ERROR("Storage.Structure.Binary.Encodings.InvalidCharacter");
         ex->add("encoding", _name);
         ex->addUInt32("character", c);
         throw ex;
      }
         
      if(_endian)
         out->addUInt32BE(c);
      else
         out->addUInt32LE(c);
   }
   return in->length();
}


_bool UTF_32::bigEndian()
{
   return _endian;
}
   
_bool UTF_32::littleEndian()
{
   return !_endian;
}
   

_bool UTF_32::bom()
{
   return _bom;
}
   
void UTF_32::setBom(_bool bom)
{
   _bom = bom;
}

} } } }
