/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

BufferWindow::BufferWindow(Buffer *buf)
{
   _buffer = buf;
   if(_buffer->length() == 0)
      THROW_ERROR(Exception::Format::EmptyBuffer);
      
   _position = 0;
}


void BufferWindow::setChar(const WindowPointer &p, _char c)
{
   _buffer->set(absolute(p), c);
}


Buffer *BufferWindow::get(const WindowPointer &from, const WindowPointer &to)
{
   return _buffer->sub(absolute(from), from.diff(to) + 1);
}


Buffer *BufferWindow::getBuffer()
{
   return _buffer;
}
  
_int BufferWindow::absolute(const WindowPointer &pos)
{
   return _position + getPointer(pos);
}

_bool BufferWindow::hasFinished()
{
   return (absolute(end()) >= _buffer->length() - 1);
}


_char BufferWindow::getChar(_int position)
{
   return _buffer->get(_position + position);
}

void BufferWindow::moveStart(_int chars)
{
   Window::moveStart(chars);
   
   // Move window position
   _int d = _pointers[POINTER_START];
   for(_int i = 0; i < _pointers.count(); i++)
      _pointers[i] -= d;
   _position += d;
}
   
void BufferWindow::moveEnd(_int chars)
{
   if(chars < 0)
   {
      MAKE_ERROR(ex, Error::Text::NoBackward);
      ex->add("pointer", "end");
      ex->addInt("move", chars);
      throw ex;
   }
      
   _int dst = _pointers[POINTER_END] + chars;
   if(_position + dst >= _buffer->length())
      _pointers[POINTER_END] = _buffer->length() - _position - 1;
   else
      _pointers[POINTER_END] = dst;
}

void BufferWindow::displace(const WindowPointer &p, _int chars)
{
   WritableWindow::displace(p, chars);
   
   _buffer->erase(absolute(p), -chars);
}

} } }

