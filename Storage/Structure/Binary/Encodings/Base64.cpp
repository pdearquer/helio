/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {
namespace Encodings {

const_String Base64::_table;


Base64::Base64()
{
   setName("Base64");
   _padding = true;
   _line = 76;
   _linePos = 0;
   _char62 = '+';
   _char63 = '/';
   _end = false;
}
   
   
_bool Base64::canEncode(_char c)
{
   return (getValue((__char)c) >= 0);
}

_int Base64::getValue(__char c)
{
   if(c >= 0x7F)
      return -1;
      
   for(_int i = 0; i < 0x3E; i++)
      if((__char) _table[i] == c)
         return i;
      
   if(c == (__char)_char62)
      return 62;
   if(c == (__char)_char63)
      return 63;
            
   return -1;
}

_char Base64::getChar(_int val)
{
   if(val == 62)
      return _char62;
   if(val == 63)
      return _char63;
 
   if(val > 61)
   {
      MAKE_ERROR(ex, Error::Internal);
      ex->add("encoding", _name);
      throw ex;
   }
      
   return _table[val];
}
   
_int Base64::decode(const Buffer *in, Text::Buffer *out, _bool finish)
{   
   _int len = (in->length() / 3) * 3;
   __char c;
   
   for(_int i = 0; i < len; i += 3)
   {
      c = (__char)in->get(i);
      c = c << 8 | (__char)in->get(i + 1);
      c = c << 8 | (__char)in->get(i + 2);

      out->add(getChar((c >> 18) & 0x3F));
      out->add(getChar((c >> 12) & 0x3F));
      out->add(getChar((c >> 6) & 0x3F));
      out->add(getChar(c & 0x3F));
      
      if(_line > 0)
      {
         _linePos += 4;
         if(_linePos >= _line)
         {
            out->add("\r\n");
            _linePos = 0;
         }
      }
   }
   
   if(!finish)
      return len;
      
   switch(in->length() - len)
   {
      case 0:
         break;
         
      case 1:
         c = (__char)in->get(len);
         
         out->add(getChar((c >> 2) & 0x3F));
         out->add(getChar((c << 4) & 0x3F));
         if(_padding)
            out->add("==");
         break;
         
      case 2:
         c = (__char)in->get(len);
         c = c << 8 | (__char)in->get(len + 1);
         
         out->add(getChar((c >> 10) & 0x3F));
         out->add(getChar((c >> 4) & 0x3F));
         out->add(getChar((c << 2) & 0x3F));
         if(_padding)
            out->add('='); 
         break;
         
      default:
         MAKE_ERROR(ex, Error::Internal);
         ex->add("encoding", _name);
         throw ex;
   }
    
   return in->length();
}
   
_int Base64::encode(const Text::Buffer *in, Buffer *out, _bool finish)
{
   _char ch;
   _int c;
   _uint32 v;
   _int i = 0;
   
   if(!_end)
   {
      for(; i < in->length(); i++)
      {
         ch = in->get(i);
         if(ch == '\r' || ch == 'n')
            continue;
         
         if(in->length() - i < 4)
         {
            if(!finish)
               return i;
               
            if(!_padding || in->length() - i < 2)
               THROW_ERROR(Exception::Format::UnexpectedEnd);
         }
         
         c = getValue((__char)ch);
         if(c < 0)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("encoding", _name);
            ex->addUInt32("character", (__char)ch);
            throw ex;
         }
         v = c;
         
         i++;
         c = getValue(in->get(i));      
         if(c < 0)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("encoding", _name);
            ex->addUInt32("character", (__char)ch);
            throw ex;
         }
         v = (v << 6) | c;
         
         if(!_padding && in->length() - i == 0)
         {
            out->add((_byte) (v >> 4) & 0xFF);
            return i;
         }
         
         i++;
         ch = in->get(i);
         if(_padding && ch == '=')
         {
            i++;
            ch = in->get(i);
            if(ch != '=')
            {
               MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
               ex->add("encoding", _name);
               ex->addUInt32("character", (__char)ch);
               ex->add("expected", "padding");
               throw ex;
            }
            
            out->add((_byte) (v >> 4) & 0xFF);
            
            _end = true;
            i++;
            break;         
         }      
         c = getValue(ch);      
         if(c < 0)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("encoding", _name);
            ex->addUInt32("character", (__char)ch);
            throw ex;
         }
         v = (v << 6) | c;
         
         if(!_padding && in->length() - i == 0)
         {
            out->add((_byte) (v >> 10) & 0xFF);
            out->add((_byte) (v >> 2) & 0xFF);
            return i;
         }
         
         i++;
         ch = in->get(i);
         if(_padding && ch == '=')
         {         
            out->add((_byte) (v >> 10) & 0xFF);
            out->add((_byte) (v >> 2) & 0xFF);
            
            _end = true;
            i++;
            break;         
         }
         c = getValue(ch);      
         if(c < 0)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("encoding", _name);
            ex->addUInt32("character", (__char)ch);
            throw ex;
         }
         v = (v << 6) | c;
         
         out->add((_byte) (v >> 16) & 0xFF);
         out->add((_byte) (v >> 8) & 0xFF);
         out->add((_byte) v & 0xFF);
      }
   }
      
   for(; i < in->length(); i++)
   {
      ch = in->get(i);
      if(ch != '\r' && ch != '\n')
      {
         MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
         ex->add("encoding", _name);
         ex->addUInt32("character", (__char)ch);
         ex->add("expected", "end");
         throw ex;
      }
   }
   
   if(finish)
      _end = false;
      
   return i;
}


_bool Base64::padding()
{
   return _padding;
}
   
_bool Base64::padding(_bool pad)
{
   _padding = pad;
   return _padding;
}

_int Base64::line()
{
   return _line;
}
   
_int Base64::line(_int lin)
{
   if(lin < 0)
      _line = -1;
   else
      _line = (lin / 4) * 4;
      
   return _line;
}

_char Base64::char62()
{
   return _char62;
}

void Base64::setChar62(_char c)
{
   _char62 = c;
}

_char Base64::char63()
{
   return _char63;
}

void Base64::setChar63(_char c)
{
   _char63 = c;
}
   
void Base64::modeNormal()
{
   _char62 = '+';
   _char63 = '/';
}

void Base64::modeUrl()
{
   _char62 = '-';
   _char63 = '_';
}
   
void Base64::modeXml()
{
   _char62 = '.';
   _char63 = '-';
}
   
} } } }

