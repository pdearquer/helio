/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

StringWindow::StringWindow(const StringBuffer &str)
{
   _str = str;
   if(_str.count() == 0)
      ERROR(Exception::Format::EmptyBuffer);
   _position = 0;
}

StringWindow::StringWindow(const StringBuffer &str, _int start, _int length)
{
   _str = str.sub(start, length);
   if(_str.count() == 0)
      ERROR(Exception::Format::EmptyBuffer);
   _position = 0;
}


Buffer *StringWindow::get(const WindowPointer &from, const WindowPointer &to)
{
   return ((Buffer *) &_str)->sub(absolute(from), from.diff(to) + 1);
}


String StringWindow::getStringCopy()
{
   return _str;
}
   
_int StringWindow::absolute(const WindowPointer &pos)
{
   return _position + getPointer(pos);
}

_bool StringWindow::hasFinished()
{
   return (absolute(end()) >= _str.count() - 1);
}


_char StringWindow::getChar(_int position)
{
   return _str.get(_position + position);
}

void StringWindow::moveStart(_int chars)
{
   if(chars < 0)
   {
      Error *ex = MAKE_ERROR(Error::Text::NoBackward);
      ex->add("pointer", "start");
      ex->addInt("move", chars);
      throw ex;
   }
      
   Window::moveStart(chars);
   
   // Move window position
   _int d = _pointers[POINTER_START];
   for(_int i = 0; i < _pointers.count(); i++)
      _pointers[i] -= d;
   _position += d;
}
   
void StringWindow::moveEnd(_int chars)
{
   if(chars < 0)
   {
      Error *ex = MAKE_ERROR(Error::Text::NoBackward);
      ex->add("pointer", "end");
      ex->addInt("move", chars);
      throw ex;
   }
      
   _int dst = _pointers[POINTER_END] + chars;
   if(_position + dst >= _str.count())
      _pointers[POINTER_END] = _str.count() - _position - 1;
   else
      _pointers[POINTER_END] = dst;
}

} } }

