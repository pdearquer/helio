/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

InputWindow::InputWindow(Input *in, _int step)
{
   _in = in;
   _finish = false;
   if(step < 1)
   {
      Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
      ex->addInt("step", step);
      throw ex;
   }
   _step = step;
   
   if(_in->read(&_buffer, _step) < _step)
      _finish = true;
}


Buffer *InputWindow::get(const WindowPointer &from, const WindowPointer &to)
{
   return _buffer.sub(getPointer(from), from.diff(to) + 1);
}

_bool InputWindow::hasFinished()
{
   if(!_finish)
      return false;
      
   return (getPointer(end()) >= _buffer.length() - 1);
}

_int InputWindow::step()
{
   return _step;
}
   
_int InputWindow::step(_int step)
{
   if(step < 1)
   {
      Error *ex = MAKE_ERROR(Error::Structure::InvalidLength);
      ex->addInt("step", step);
      throw ex;
   }
      
   _step = step;
   return _step;
}


_char InputWindow::getChar(_int position)
{
   return _buffer.get(position);
}

void InputWindow::moveStart(_int chars)
{
   Window::moveStart(chars);
   
   // Move window ahead
   _int d = _pointers[POINTER_START];
   for(_int i = 0; i < _pointers.count(); i++)
      _pointers[i] -= d;
   _buffer.move(d);
}
   
void InputWindow::moveEnd(_int chars)
{
   if(chars < 0)
   {
      Error *ex = MAKE_ERROR(Error::Text::NoBackward);
      ex->add("pointer", "end");
      ex->addInt("move", chars);
      throw ex;
   }
      
   _int dst = _pointers[POINTER_END] + chars;
   if(dst >= _buffer.length() - 1 && !_finish)
   {      
      // Always one more to ensure we recognize the last byte.
      _int req = dst - _buffer.length() + 1;
      if(req < _step)
         req = _step;
      
      try
      {
         if(_in->read(&_buffer, req, _buffer.length()) < req)
            _finish = true;
      }
      catch(Exception *ex)
      {
         addStatus(ex, end());
         throw ex;
      }
   }
   
   if(dst >= _buffer.length())
      _pointers[POINTER_END] = _buffer.length() - 1;
   else
      _pointers[POINTER_END] = dst;
}

} } }

