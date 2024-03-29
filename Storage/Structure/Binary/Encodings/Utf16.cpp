/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

Utf16::Utf16()
{
   setName("UTF-16");
#ifdef __HELIO_TARGET_BIG_ENDIAN
   _endian = true;
#else
   _endian = false;
#endif
   _bom = false;
}
  
Utf16::Utf16(_bool bigEndian)
{
   setName("UTF-16");
   _endian = bigEndian;
   _bom = false;
} 
   
   
_bool Utf16::canEncode(_char c)
{
   return true;
}
   
_int Utf16::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{   
   _int len = (in->length() / 2) * 2;
     
   for(_int i = 0; i < len; i += 2)
   {
      __char w;
      if(_endian)
         w = (__char)in->getUInt16BE(i);
      else
         w = (__char)in->getUInt16LE(i);
      __char w2;
      Character c;
      
      if(w >= 0xD800 && w <= 0xDFFF)
      {
         if(len - i < 4)
         {
            if(finish)
               THROW_ERROR(Exception::Format::UnexpectedEnd);
            return i;     
         }
         
         w = (w & 0x3FF) << 10;
         
         i += 2;
         if(_endian)
            w2 = (__char)in->getUInt16BE(i);
         else
            w2 = (__char)in->getUInt16LE(i);
         if((w2 & 0xDC00) != 0xDC00)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidByte);
            ex->add("encoding",_name);
            ex->addUInt32("word", w2);
            throw ex;
         }
         w = w | (w2 & 0x3FF);
         if(w < 0x10000)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidByte);
            ex->add("encoding",_name);
            ex->addUInt32("word", w2);
            throw ex;
         }
      }
      
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
      catch(Exception::Format::InvalidCharacter *e)
      {
         throw;
      }
      catch(Exception *e)
      {
         RE_MAKE_ERROR(ex, Exception::Format::InvalidByte, e);
         ex->add("encoding", _name);
         ex->addUInt32("code", w);
         throw ex;
      }
      
      out->add(c);
   }
   
   if(finish && len != in->length())
      THROW_ERROR(Exception::Format::UnexpectedEnd);
      
   return len;
}
   
_int Utf16::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   if(_bom)
   {
      if(_endian)
         out->addUInt16BE(0xFEFF);
      else
         out->addUInt16LE(0xFEFF);
         
      _bom = false;
   } 
   
   for(_int i = 0; i < in->length(); i++)
   {
      __char c = (__char) in->get(i);
      _uint16 w;
      
      if(!Character::isValid(c))
      {
         MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
         ex->add("encoding", _name);
         ex->addUInt32("character", c);
         throw ex;
      }
         
      if(c < 0x10000)
      {
         w = (_uint16) c;
         if(_endian)
            out->addUInt16BE(w);
         else
            out->addUInt16LE(w);
      }
      else
      {
         c = c - 0x10000;
         
         w = 0xD800 | ((c >> 10) & 0x3FF);
         if(_endian)
            out->addUInt16BE(w);
         else
            out->addUInt16LE(w);
         
         w = 0xDC00 | (c & 0x3FF);
         if(_endian)
            out->addUInt16BE(w);
         else
            out->addUInt16LE(w);
      }
   }
   return in->length();
}


_bool Utf16::bigEndian()
{
   return _endian;
}
   
_bool Utf16::littleEndian()
{
   return !_endian;
}
   

_bool Utf16::bom()
{
   return _bom;
}
   
void Utf16::setBom(_bool bom)
{
   _bom = bom;
}

} } } }

