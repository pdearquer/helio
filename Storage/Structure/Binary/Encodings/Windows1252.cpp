/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

const _uint16 Windows1252::_table[0x20] =
{
   0x20AC, 0x0000, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
   0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x0000, 0x017D, 0x0000,
   
   0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
   0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x0000, 0x017E, 0x0178
};


Windows1252::Windows1252()
{
   setName("Windows-1252");
}
   
   
_bool Windows1252::canEncode(_char c)
{
   return (getCode((__char)c) >= 0);
}

_int Windows1252::getCode(__char c)
{
   if(c < 0x80 || (c >= 0xA0 && c <= 0xFF))
      return (_int) c;
      
   for(_int i = 0; i < 0x20; i++)
      if(_table[i] == c)
         return 0x80 + i;
      
   return -1;
} 
   
_int Windows1252::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{   
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (__char)in->get(i);
      if(c >= 0x80 && c < 0xA0)
      {
         c = _table[c - 0x80];
         if(c == 0)
         {
            Exception *ex = MAKE_ERROR("Storage.Structure.Binary.Encodings.InvalidByte");
            ex->add("encoding", _name);
            ex->addByte("byte", c);
            throw ex;
         }
      }
      
      out->add((_char)c);
   }
   return in->length();
}
   
_int Windows1252::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   for(_int i = 0; i < in->length(); i++)
   {
      _int c = getCode((__char)in->get(i));
      
      if(c >= 0)
         out->add((_byte) c);
      else
      {
         Exception *ex = MAKE_ERROR("Storage.Structure.Binary.Encodings.InvalidCharacter");
         ex->add("encoding", _name);
         ex->addUInt32("character", (__char)in->get(i));
         throw ex;
      }
   }
   return in->length();
}

} } } }
