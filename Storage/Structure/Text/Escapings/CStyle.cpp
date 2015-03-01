/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {
namespace Escapings {

const_String CStyle::SPECIAL;


CStyle::CStyle()
{
   setName("CStyle");

   fmt = new Format();
   fmt->base(16);
   fmt->minDigits(2);
}

CStyle::~CStyle()
{
   delete fmt;
}


void CStyle::escape(WritableWindow *w)
{
   WindowPointer start = w->start();

   while(true)
   {
      _uint32 c = Character(w->getChar(start)).getUtf32();
      
      if(w->isAny(SPECIAL))
      {
         switch(c)
         {
            case '\t':
               w->replace("\\t", start, start);               
               break;
            case '\n':
               w->replace("\\n", start, start);               
               break;
            case '\r':
               w->replace("\\r", start, start);               
               break;
            case '\"':
               w->replace("\\\"", start, start);               
               break;
            case '\'':
               w->replace("\\\'", start, start);               
               break;   
            case '\b':
               w->replace("\\b", start, start);               
               break;
            case '\a':
               w->replace("\\a", start, start);               
               break;
            case '\f':
               w->replace("\\f", start, start);               
               break;
            case '\\':
               w->replace("\\\\", start, start);               
               break;  
               
            default:
               THROW_ERROR(Error::Internal);
         }
         start++;
      }
      else if(c >= 0xA0)   // No valid ASCII
      {
         if(c > 0xFF)
         {
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("escaping", _name);
            ex->addUInt32("char", c);
            throw ex;
         }
         
         w->replace("\\x" + fmt->toString((_int) c), start, start);  
      }
      
      if(w->hasFinished(start))
         return;
         
      start++;
   }
}
   
void CStyle::unescape(WritableWindow *w)
{
   WindowPointer start = w->start();
   WindowPointer result = w->result();

   while(w->find('\\'))
   {
      start = result;
      if(w->hasFinished(start))
      {
         MAKE_ERROR(ex, Exception::Format::UnexpectedEnd);
         ex->add("escaping", _name);
         throw ex;
      }
      
      result++;
      _int c;
      switch(w->getChar(result))
      {
         case 't':
            w->replace('\t', start, result);
            break;
         case 'n':
            w->replace('\n', start, result);
            break;
         case 'r':
            w->replace('\r', start, result);
            break;
         case '\"':
            w->replace('\"', start, result);
            break;
         case '\'':
            w->replace('\'', start, result);
            break;
         case 'b':
            w->replace('\b', start, result);
            break;
         case 'a':
            w->replace('\a', start, result);
            break;
         case 'f':
            w->replace('\f', start, result);
            break;
         case '\\':
            w->replace('\\', start, result);
            break;
            
         case 'x':            
            result++;
            if(w->hasFinished(result))
            {
               MAKE_ERROR(ex, Exception::Format::UnexpectedEnd);
               ex->add("escaping", _name);
               throw ex;
            }
            c = fmt->toInt(w, result, result + 1);
            
            result++;
            w->replace((_char)(__char)c, start, result);
            
            break;
            
         default:
            MAKE_ERROR(ex, Exception::Format::InvalidCharacter);
            ex->add("escaping", _name);
            ex->addUInt32("char", Character(w->getChar(start)).getUtf32());
            throw ex;
      }            
      
      if(w->hasFinished(start))
         return;
         
      start++;
   }
}

} } } }

