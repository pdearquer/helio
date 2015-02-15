/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {
namespace Escapings {

HTML::HTML()
{
   setName("HTML");
 
   //_entities.add(' ', "nbsp");
   _entities.add('\"', "quot");
   _entities.add('&', "amp");
   _entities.add('<', "lt");
   _entities.add('>', "gt");
   _entities.add((_uint32) 163, "pound");
   _entities.add((_uint32) 191, "iquest");   
   _entities.add((_uint32) 193, "Aacute");
   _entities.add((_uint32) 201, "Eacute");
   _entities.add((_uint32) 205, "Iacute");
   _entities.add((_uint32) 209, "Ntilde");
   _entities.add((_uint32) 211, "Oacute");
   _entities.add((_uint32) 218, "Uacute");
   _entities.add((_uint32) 225, "aacute");
   _entities.add((_uint32) 233, "eacute");
   _entities.add((_uint32) 237, "iacute");
   _entities.add((_uint32) 241, "ntilde");
   _entities.add((_uint32) 243, "oacute");
   _entities.add((_uint32) 250, "uacute");  
}


void HTML::addEntity(Character c, String name)
{
   _entities.add(c, name);
}


void HTML::escape(WritableWindow *w)
{
   WindowPointer start = w->start();

   while(true)
   {
      Character c = w->getChar(start);      
      try
      {
         String name = _entities.get(c);
         
         w->replace("&" + name + ";", start, start);
         
         start += name.length() + 1;
      }
      catch(Exception *ex)
      { }
      
      if(w->hasFinished(start))
         return;
         
      start++;
   }
}
   
void HTML::unescape(WritableWindow *w)
{
   WindowPointer start = w->start();
   WindowPointer result = w->result();

   while(w->find('&'))
   {
      start = result;
      
      if(!w->find(';'))
      {
         Exception *ex = MAKE_ERROR("Storage.Structure.Text.Escaping.BadSequence");
         ex->add("escaping", _name);
         ex->add("expected", ";");
         if(start.diff(result) < 64)
            ex->add("entity", w->getString());
         else
            ex->add("entity", w->getString(start, start + 64));
         throw ex;
      }
      
      String name = w->getString(start + 1, result - 1);
      try
      {
         Character c = _entities.keyOf(name);
         
         w->replace(c, start, result);
         start = result + 1;
      }
      catch(Exception *ex)
      {
         Exception *ex = MAKE_ERROR("Storage.Structure.Text.Escaping.BadSequence");
         ex->add("escaping", _name);
         ex->add("entity", name);
         throw ex;
      }
      
      if(w->hasFinished(start))
         return;
   }
}

} } } }
