/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

WindowPointer::WindowPointer(Window *win, _int index)
{
   _win = win;
   _index = index;
   _win->addRef(_index);
}

WindowPointer::WindowPointer(const WindowPointer &other)
{
   _win = other._win;
   _index = other._index;
   
   _win->addRef(_index);
}

WindowPointer::~WindowPointer()
{
   _win->removeRef(_index);
}


void WindowPointer::move(const _int chars)
{
   _win->movePointer(_index, chars);
}
   
void WindowPointer::move(const WindowPointer &other)
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   _win->setPointer(_index, other._index);
}
   
void WindowPointer::start()
{
   _win->setPointer(_index, Window::POINTER_START);
}
   
void WindowPointer::end()
{
   _win->setPointer(_index, Window::POINTER_END);
}
   
   
_int WindowPointer::diff(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   _int from = _win->getPointer(_index);
   _int to = _win->getPointer(other._index);
   
   return (to - from);
}


WindowPointer &WindowPointer::operator =(const WindowPointer &other)
{
   move(other);
   return *this;
}
   
WindowPointer WindowPointer::operator +(const _int chars) const
{
   WindowPointer ret = dup();
   ret.move(chars);
   return ret;
}

WindowPointer WindowPointer::operator -(const _int chars) const
{
   WindowPointer ret = dup();
   ret.move(-chars);
   return ret;
}

WindowPointer &WindowPointer::operator ++()
{
   move(+1);
   return *this;
}

WindowPointer WindowPointer::operator ++(int)
{
   WindowPointer ret = dup();
   move(+1);
   return ret;
}

WindowPointer &WindowPointer::operator --()
{
   move(-1);
   return *this;
}

WindowPointer WindowPointer::operator --(int)
{
   WindowPointer ret = dup();
   move(-1);
   return ret;
}

WindowPointer &WindowPointer::operator +=(const _int chars)
{
   move(chars);
   return *this;
}

WindowPointer &WindowPointer::operator -=(const _int chars)
{
   move(-chars);
   return *this;
}


_bool WindowPointer::operator ==(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   return (_win->getPointer(_index) == _win->getPointer(other._index));
}

_bool WindowPointer::operator !=(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   return (_win->getPointer(_index) != _win->getPointer(other._index));
}

_bool WindowPointer::operator <(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   return (_win->getPointer(_index) < _win->getPointer(other._index));
}

_bool WindowPointer::operator >(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   return (_win->getPointer(_index) > _win->getPointer(other._index));
}

_bool WindowPointer::operator <=(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   return (_win->getPointer(_index) <= _win->getPointer(other._index));
}

_bool WindowPointer::operator >=(const WindowPointer &other) const
{
   if(_win != other._win)
      ERROR(Error::Text::IncompatiblePointers);
      
   return (_win->getPointer(_index) >= _win->getPointer(other._index));
}


WindowPointer WindowPointer::dup() const
{
   return WindowPointer(_win, _win->copyPointer(_index));
}

} } }

