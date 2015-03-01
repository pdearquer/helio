/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

Utf8::Utf8()
{
   setName("UTF-8");
}
   
   
_bool Utf8::canEncode(_char c)
{
   return true;
}
   
_int Utf8::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{  
   const _byte *data = in->data();
   _int i = 0;
   
   while(i < in->length())
   {
      _int len = charlen(&data[i]);
      
      if(in->length() - i < len)
      {
         if(finish)
            THROW_ERROR(Exception::Format::UnexpectedEnd);
         return i;
      }
      
      _char ch;
      i += chardec(&ch, &data[i]);
      out->add(ch);
   }
   
   return i;
}
   
_int Utf8::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   _int pos = out->length();
   
   for(_int i = 0; i < in->length(); i++)
   {
      _char ch = in->get(i);
      
      out->length(pos + charlen(ch));
      
      _byte *data = out->data();
      pos += charenc(ch, &data[pos]);
      
      out->length(pos);
   }
   
   return in->length();
}


_int Utf8::charlen(const _uint8 *buf)
{
   _uint8 b = *buf;
   
   if(b <= 0x7F)
      return 1;
   else if((b & 0xE0) == 0xC0)
      return 2;
   else if((b & 0xF0) == 0xE0)
      return 3;
   else if((b & 0xF8) == 0xF0)
      return 4;
   else if((b & 0xFC) == 0xF8)
      return 5;
   else if((b & 0xFE) == 0xFC)
      return 6;
   else
   {
      MAKE_ERROR(ex, Exception::Format::InvalidByte);
      ex->add("encoding", "UTF-8");
      ex->addByte("byte", b);
      throw ex;
   }
}
   
_int Utf8::charlen(_char ch)
{
   __char c = ch;
   if(c <= 0x7F)
      return 1;
   else if(c <= 0x7FF)
      return 2;
   else if(c <= 0xFFFF)
      return 3;
   else if(c <= 0x1FFFFF)
      return 4;
   else if(c <= 0x3FFFFFF)
      return 5;
   else
      return 6;
}
   
_int Utf8::charenc(_char ch, _uint8 *buf)
{
   __char c = (__char)ch;
   if(!Character::isValid(c))
   {
      MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
      ex->add("encoding", "UTF-8");
      ex->addUInt32("character", c);
      throw ex;
   }
      
   if(c <= 0x7F)
   {
      buf[0] = (_byte) c;
      return 1;
   }
   else if(c <= 0x7FF)
   {
      buf[0] = 0xC0 | ((c >> 6) & 0x1F);
      buf[1] = 0x80 | (c & 0x3F);
      return 2;
   }
   else if(c <= 0xFFFF)
   {
      buf[0] = 0xE0 | ((c >> 12) & 0x0F);
      buf[1] = 0x80 | ((c >> 6) & 0x3F);
      buf[2] = 0x80 | (c & 0x3F);
      return 3;
   }
   else if(c <= 0x1FFFFF)
   {
      buf[0] = 0xF0 | ((c >> 18) & 0x07);
      buf[1] = 0x80 | ((c >> 12) & 0x3F);
      buf[2] = 0x80 | ((c >> 6) & 0x3F);
      buf[3] = 0x80 | (c & 0x3F);
      return 4;
   }
   else if(c <= 0x3FFFFFF)
   {
      buf[0] = 0xF8 | ((c >> 24) & 0x03);
      buf[1] = 0x80 | ((c >> 18) & 0x3F);
      buf[2] = 0x80 | ((c >> 12) & 0x3F);
      buf[3] = 0x80 | ((c >> 6) & 0x3F);
      buf[4] = 0x80 | (c & 0x3F);
      return 5;
   }
   else
   {
      buf[0] = 0xFC | ((c >> 30) & 0x01);
      buf[1] = 0x80 | ((c >> 24) & 0x3F);
      buf[2] = 0x80 | ((c >> 18) & 0x3F);
      buf[3] = 0x80 | ((c >> 12) & 0x3F);
      buf[4] = 0x80 | ((c >> 6) & 0x3F);
      buf[5] = 0x80 | (c & 0x3F);
      return 6;
   }
}
 
_int Utf8::chardec(_char *c, const _uint8 *buf)
{
   __char b = (__char) buf[0];
   __char b2;
   
   if(b <= 0x7F)
   {
      if(!Character::isValid(b))
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b);
         throw ex;
      }
      *c = b;
      return 1;
   }
   else if((b & 0xE0) == 0xC0)
   {     
      b = (b & 0x1F) << 6;
      
      b2 = (__char) buf[1];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      }
      b = b | (b2 & 0x3F);
      
      if(!Character::isValid(b) || b <= 0x7F)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b);
         throw ex;
      }
      *c = b;
      return 2;
   }
   else if((b & 0xF0) == 0xE0)
   {
      b = (b & 0x0F) << 12;
      
      b2 = (__char) buf[1];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 6;
      
      b2 = (__char) buf[2];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F);
      
      if(!Character::isValid(b) || b <= 0x7FF)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b);
         throw ex;
      }
      *c = b;
      return 3;
   }
   else if((b & 0xF8) == 0xF0)
   {    
      b = (b & 0x07) << 18;
      
      b2 = (__char) buf[1];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 12;
      
      b2 = (__char) buf[2];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 6;
      
      b2 = (__char) buf[3];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F);
      
      if(!Character::isValid(b) || b <= 0xFFFF)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b);
         throw ex;
      }
      *c = b;
      return 4;
   }
   else if((b & 0xFC) == 0xF8)
   {
      b = (b & 0x03) << 24;
      
      b2 = (__char) buf[1];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 18;
      
      b2 = (__char) buf[2];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 12;
      
      b2 = (__char) buf[3];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 6;
      
      b2 = (__char) buf[4];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F);
      
      if(!Character::isValid(b) || b <= 0x1FFFFF)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b);
         throw ex;
      }
      *c = b;
      return 5;
   }
   else if((b & 0xFE) == 0xFC)
   {
      b = (b & 0x01) << 30;
      
      b2 = (__char) buf[1];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 24;
      
      b2 = (__char) buf[2];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 18;
      
      b2 = (__char) buf[3];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 12;
      
      b2 = (__char) buf[4];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F) << 6;
      
      b2 = (__char) buf[5];
      if((b2 & 0xC0) != 0x80)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b2);
         throw ex;
      } 
      b = b | (b2 & 0x3F);

      if(!Character::isValid(b) || b <= 0x3FFFFFF)
      {
         MAKE_ERROR(ex, Exception::Format::InvalidByte);
         ex->add("encoding", "UTF-8");
         ex->addByte("byte", b);
         throw ex;
      }
      *c = b;
      return 6;
   }
   else
   {
      MAKE_ERROR(ex, Exception::Format::InvalidByte);
      ex->add("encoding", "UTF-8");
      ex->addByte("byte", b);
      throw ex;
   }        
}

_int Utf8::charcount(const _uint8 *buf, _int bytes)
{
   _int count = 0;
   _int i = 0;
   while(i < bytes)
   {
      i += Utf8::charlen(&buf[i]);
      count++;
   }
   
   if(i != bytes)
      THROW_ERROR(Exception::Format::UnexpectedEnd);
   
   return count;
}

_int Utf8::charbytes(const _uint8 *buf, _int len)
{
   _int b = 0;
   for(_int i = 0; i < len; i++)
      b += Utf8::charlen(&buf[b]);
      
   return b;
}

} } } }

