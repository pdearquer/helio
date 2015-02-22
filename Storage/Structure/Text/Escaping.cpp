/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

Escaping::Escaping()
{
}

void Escaping::setName(String name)
{
   _name = name;
}

String Escaping::name()
{
   return _name;
}


String Escaping::escString(String input)
{
   if(input.length() == 0)
      return "";

   Buffer *buf = input.toBuffer();
   BufferWindow *bw = new BufferWindow(buf);
   
   try
   {
      escape(bw);
   }
   catch(Exception *ex)
   {
      delete bw;
      delete buf;
      
      throw ex;
   }
   
   delete bw;
   String output = buf->toString();   
   delete buf;
   
   return output;
}

String Escaping::unescString(String input)
{
   if(input.length() == 0)
      return "";
      
   Buffer *buf = input.toBuffer();
   BufferWindow *bw = new BufferWindow(buf);
   
   try
   {
      unescape(bw);
   }
   catch(Exception *ex)
   {
      delete bw;
      delete buf;
      
      throw ex;
   }
   
   delete bw;
   String output = buf->toString();   
   delete buf;
   
   return output;
} 


Escaping *Escaping::get(String name)
{
#ifdef __HELIO_STORAGE_STRUCTURE_TEXT_ESCAPINGS_LINEFEED
   if(name.equals("LineFeed", true))
      return new Escapings::LineFeed();
#endif

#ifdef __HELIO_STORAGE_STRUCTURE_TEXT_ESCAPINGS_CSTYLE
   if(name.equals("CStyle", true))
      return new Escapings::CStyle();
#endif

#ifdef __HELIO_STORAGE_STRUCTURE_TEXT_ESCAPINGS_HTML
   if(name.equals("HTML", true))
      return new Escapings::HTML();
#endif

   Exception *ex = MAKE_ERROR(Exception::Structure::EscapingNotSupported);
   ex->add("escaping", name);
   throw ex;
}

} } }

