/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

void WritableWindow::set(const WindowPointer &p, String s)
{
   WindowPointer p2 = p.dup();
   setChar(p2, s.get(0));
   for(_int i = 1; i < s.length(); i++)
   {
      if(hasFinished(p2))
      {
         Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
         ex->addInt("pointer", p._index);
         ex->addInt("position", getPointer(p));
         ex->add("string", s);
         throw ex;
      }
      p2++;
      
      setChar(p2, s.get(i));            
   }
}

void WritableWindow::insert(_char c, const WindowPointer &p)
{
   displace(p, 1);
   setChar(p, c);
}
   
void WritableWindow::insert(const StringBuffer &s, const WindowPointer &p)
{
   displace(p, s.length());
   
   WindowPointer p2 = p.dup();
   setChar(p2, s.get(0));
   for(_int i = 1; i < s.length(); i++)
   {
      p2++;
      setChar(p2, s.get(i));      
   }
}
   
void WritableWindow::erase(const WindowPointer &from, const WindowPointer &to)
{
   _int diff = from.diff(to);   
   diff++;
      
   if(diff <= 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("difference", diff);
      throw ex;
   }
   
   displace(from, -diff);
}

void WritableWindow::replace(_char c, const WindowPointer &from, const WindowPointer &to)
{
   _int diff = from.diff(to);
   diff++;
   
   if(diff <= 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("difference", diff);
      throw ex;
   }
   
   displace(from, 1 - diff);
   setChar(from, c);
}

void WritableWindow::replace(const StringBuffer &s, const WindowPointer &from, const WindowPointer &to)
{
   _int diff = from.diff(to);
   diff++;
   
   if(diff <= 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("difference", diff);
      throw ex;
   }
   
   displace(from, s.length() - diff);
   
   WindowPointer p = from.dup();
   setChar(p, s.get(0));
   for(_int i = 1; i < s.length(); i++)
   {
      p++;
      setChar(p, s.get(i));      
   }
}


void WritableWindow::displace(const WindowPointer &p, _int chars)
{
   if(chars == 0)
      return;
      
   _int pos = getPointer(p);
   
   if(_pointers[POINTER_END] + chars < pos)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("pointer", p._index);
      ex->addInt("end", _pointers[POINTER_END]);
      ex->addInt("position", pos);
      ex->addInt("move", chars);
      throw ex;
   }
   _pointers[POINTER_END] += chars;
      
   for(_int i = POINTER_RESULT; i < _pointers.count(); i++)
   {
      if(_pointers[i] > pos)
      {
         _pointers[i] += chars;
         if(_pointers[i] < pos)
            _pointers[i] = pos;
      }
   }
}

} } }
