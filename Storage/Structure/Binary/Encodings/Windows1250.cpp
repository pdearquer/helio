/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

const _uint16 Windows1250::_table[0x80] =
{
   0x20AC, 0x0000, 0x201A, 0x0000, 0x201E, 0x2026, 0x2020, 0x2021,
   0x0000, 0x2030, 0x0160, 0x2039, 0x015A, 0x0164, 0x017D, 0x0179,
   
   0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
   0x0000, 0x2122, 0x0161, 0x203A, 0x015B, 0x0165, 0x017E, 0x017A,
   
   0x00A0, 0x02C7, 0x02D8, 0x0141, 0x00A4, 0x0104, 0x00A6, 0x00A7,
   0x00A8, 0x00A9, 0x015E, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x017B,
   
   0x00B0, 0x00B1, 0x02DB, 0x0142, 0x00B4, 0x00B5, 0x00B6, 0x00B7,
   0x00B8, 0x0105, 0x015F, 0x0105, 0x013D, 0x02DD, 0x013E, 0x017C,
   
   0x0154, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0139, 0x0106, 0x00C7,
   0x010C, 0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E,
   
   0x0110, 0x0142, 0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7,
   0x0158, 0x016E, 0x00DA, 0x0170, 0x00DC, 0x00DD, 0x0162, 0x00DF,
   
   0x0155, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x013A, 0x0107, 0x00E7,
   0x010D, 0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F,
   
   0x0111, 0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7,
   0x0159, 0x016F, 0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9
};


Windows1250::Windows1250()
{
   setName("Windows-1250");
}
   
   
_bool Windows1250::canEncode(_char c)
{
   return (getCode((__char)c) >= 0);
}

_int Windows1250::getCode(__char c)
{
   if(c < 0x80)
      return (_int) c;
      
   for(_int i = 0; i < 0x80; i++)
      if(_table[i] == c)
         return 0x80 + i;
      
   return -1;
} 
   
_int Windows1250::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{   
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (__char) in->get(i);
      if(c >= 0x80)
      {
         c = _table[c - 0x80];
         if(c == 0)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidByte);
            ex->add("encoding", _name);
            ex->addByte("byte", c);
            throw ex;
         }
      }
      
      out->add((_char)c);
   }
   return in->length();
}
   
_int Windows1250::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   for(_int i = 0; i < in->length(); i++)
   {
      _int c = getCode((__char)in->get(i));
      
      if(c >= 0)
      {
         out->add((_byte) c);
      }
      else
      {
         MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
         ex->add("encoding", _name);
         ex->addUInt32("character", (__char)in->get(i));
         throw ex;
      }
   }
   return in->length();
}

} } } }

