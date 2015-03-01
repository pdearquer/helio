/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

const_int Window::POINTER_START;
const_int Window::POINTER_END;
const_int Window::POINTER_RESULT;

const_String Window::NUMBER;
const_String Window::ALPHA;
const_String Window::ALPHANUMERIC;
const_String Window::UPPER_ALPHA;
const_String Window::LOWER_ALPHA;
   

Window::Window()
{
   // Start
   _pointers.add(0);
   _refs.add(1);
   
   // End
   _pointers.add(0);
   _refs.add(1);
   
   // Result
   _pointers.add(0);
   _refs.add(1);
}


WindowPointer Window::start()
{
   return WindowPointer(this, POINTER_START);
}

WindowPointer Window::end()
{
   return WindowPointer(this, POINTER_END);
}

WindowPointer Window::result()
{
   return WindowPointer(this, POINTER_RESULT);
}

WindowPointer Window::pointer(_int index)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
      
   return WindowPointer(this, index);
}
   
_int Window::pointersCount()
{
   return _pointers.count();
}


_int Window::length()
{
   return _pointers[POINTER_END] - _pointers[POINTER_START];
}

_char Window::getChar(const WindowPointer &p)
{
   return getChar(getPointer(p));
}

Buffer *Window::get()
{
   return get(start(), end());
}
   
Buffer *Window::get(const WindowPointer &to)
{
   return get(start(), to);
}
   
Buffer *Window::get(const WindowPointer &from, const WindowPointer &to)
{
   if(this != from._win || this != to._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("from.pointer", from._index);
      ex->addInt("to.pointer", to._index);
      throw ex;
   }
   
   if(to < from)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("from.pointer", from._index);
      ex->addInt("to.pointer", to._index);
      throw ex;
   }
   
   Buffer *buf = new Buffer();
   WindowPointer p = from.dup();
   while(p < to)
   {
      buf->add(getChar(p));
      p++;
   }
   buf->add(getChar(to));
   
   return buf;
}

String Window::getString()
{
   return getString(start(), end());
}
   
String Window::getString(const WindowPointer &to)
{
   return getString(start(), to);
}

String Window::getString(const WindowPointer &from, const WindowPointer &to)
{
   Buffer *b = get(from, to);
   String ret(b);
   delete b;
   return ret;
}


_bool Window::is(_char c, _bool igncase)
{
   return is(c, start(), igncase);
}
   
_bool Window::is(_char c, const WindowPointer &p, _bool igncase)
{
   return Character(getChar(p)).equals(c, igncase);
}

_bool Window::is(const StringBuffer &s, _bool igncase)
{
   return is(s, start(), igncase);
}
   
_bool Window::is(const StringBuffer &s, const WindowPointer &p, _bool igncase)
{
   _int len = s.count();
   if(len == 0)
      return true;
      
   WindowPointer p2 = p.dup();
   _int i;    
   for(i = 0; i < len - 1; i++)
   {         
      if(!Character(getChar(p2)).equals(s.get(i), igncase))
         return false;
    
      if(hasFinished(p2))
         return false;
              
      p2++;
   }
   
   if(getChar(p2) != s.get(i))
      return false;
   return true;
}
   

_bool Window::isAny(const StringBuffer &valid, _bool igncase)
{
   return isAny(valid, start(), igncase);
}
   
_bool Window::isAny(const StringBuffer &valid, const WindowPointer &p, _bool igncase)
{
   Character c = getChar(p);

   for(_int i = 0; i < valid.length(); i++)
      if(Character(valid.get(i)).equals(c, igncase))
         return true;
         
   return false;
}


_bool Window::isNone(const StringBuffer &invalid, _bool igncase)
{
   return isNone(invalid, start(), igncase);
}
   
_bool Window::isNone(const StringBuffer &invalid, const WindowPointer &p, _bool igncase)
{
   Character c = getChar(p);

   for(_int i = 0; i < invalid.length(); i++)
      if(Character(invalid.get(i)).equals(c, igncase))
         return false;
         
   return true;
}
   

_bool Window::find(_char c)
{
   return find(c, start());
}

_bool Window::find(_char c, const WindowPointer &from)
{
   if(this != from._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("pointer", from._index);
      throw ex;
   }

   WindowPointer p = from.dup();
   while(true)
   {      
      if(c == getChar(p))
      {
         result().move(p);
         return true;
      }
      
      if(hasFinished(p))
         return false;
      
      p++;
   }   
}


_bool Window::find(_char c, const WindowPointer &from, const WindowPointer &to)
{
   if(this != from._win || this != to._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("from.pointer", from._index);
      ex->addInt("to.pointer", to._index);
      throw ex;
   }
      
   WindowPointer p = from.dup();
   while(p <= to)
   {
      if(getChar(p) == c)
      {
         result().move(p);
         return true;
      }
      p++;
   }
   return false;
}

   
_bool Window::find(const StringBuffer &s)
{
   return find(s, start());
}
   
_bool Window::find(const StringBuffer &s, const WindowPointer &from)
{
   if(this != from._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("pointer", from._index);
      throw ex;
   }
      
   WindowPointer p = from.dup();
   _bool found;
   _int last = s.count() - 1;
   while(true)
   {
      found = true;
      for(_int i = 0; i <= last; i++)
      {
         if(getChar(p + i) != s.get(i))
         {
            found = false;
            break;            
         }
      }
      
      if(found)
      {
         result().move(p);
         return true;
      }
      
      if(hasFinished(p + last))
         return false;
         
      p++;
   }
}

_bool Window::find(const StringBuffer &s, const WindowPointer &from, const WindowPointer &to)
{
   if(this != from._win || this != to._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("from.pointer", from._index);
      ex->addInt("to.pointer", to._index);
      throw ex;
   }
      
   WindowPointer p = from.dup();
   WindowPointer e = to - s.count();
   _bool found;
   while(p <= e)
   {
      found = true;
      for(_int i = 0; i < s.count(); i++)
      {
         if(getChar(p + i) != s.get(i))
         {
            found = false;
            break;            
         }
      }
      
      if(found)
      {
         result().move(p);
         return true;
      }
      
      p++;
   }
   return false;   
}
   
 
_bool Window::findAny(const StringBuffer &valid)
{
   return findAny(valid, start());
}
   
_bool Window::findAny(const StringBuffer &valid, const WindowPointer &from)
{
   if(this != from._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("pointer", from._index);
      throw ex;
   }

   WindowPointer p = from.dup();      
   while(true)
   {      
      if(valid.indexOf(getChar(p)) != -1)
      {
         result().move(p);
         return true;
      }
      
      if(hasFinished(p))
         return false;
         
      p++;
   }
      
   return false;
}

/*
_bool Window::findAny(const Vector<String> &valid);
   
*/

_bool Window::findNone(const StringBuffer &invalid)
{
   return findNone(invalid, start());
}
     
_bool Window::findNone(const StringBuffer &invalid, const WindowPointer &from)
{
   if(this != from._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("pointer", from._index);
      throw ex;
   }

   WindowPointer p = from.dup();      
   while(!hasFinished(p))
   {      
      if(invalid.indexOf(getChar(p)) == -1)
      {
         result().move(p);
         return true;
      }
      p++;
   }
      
   return false;
}

//_bool Window::findNone(const Vector<String> &invalid);


void Window::finish()
{
   while(!hasFinished())
      end()++;
}

_bool Window::hasFinished(const WindowPointer &p)
{
   if(p < end())
      return false;
   
   return hasFinished();
}


WindowStatus *Window::getStatus(const WindowPointer &at)
{
   if(this != at._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("pointer", at._index);
      throw ex;
   }
   
   WindowStatus *s = new WindowStatus(&status);
   
   WindowPointer p = start().dup();
   while(p < at)
   {
      p++;
      s->update(getChar(p));
   }
   
   return s;
}
   
void Window::addStatus(Exception *ex, const WindowPointer &at)
{
   WindowStatus *s = getStatus(at);
   ex->addInt("line", s->line());
   ex->addInt("column", s->column());
   delete s;
      
   ex->add("text", getString(at - 10, at + 10));
}
   
void Window::addStatus(Exception *ex, const WindowPointer &from, const WindowPointer &to)
{
   if(to < from)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("from.pointer", from._index);
      ex->addInt("to.pointer", to._index);
      throw ex;
   }
   
   WindowStatus *s = getStatus(from);
   ex->addInt("from.line", s->line());
   ex->addInt("from.column", s->column());
   delete s;
   
   s = getStatus(to);
   ex->addInt("to.line", s->line());
   ex->addInt("to.column", s->column());
   delete s;
      
   ex->add("text", getString(from - 10, to + 10));
}
   

void Window::moveStart(_int chars)
{
   if(chars < 0)
   {
      MAKE_ERROR(ex, Error::Text::NoBackward);
      ex->add("pointer", "start");
      ex->addInt("move", chars);
      throw ex;
   }
   
   for(_int i = 0; i < chars; i++)
      status.update(getChar(_pointers[POINTER_START] + i));
   
   _pointers[POINTER_START] += chars;
   
   for(_int i = POINTER_RESULT; i < _pointers.count(); i++)
      if(_pointers[i] < _pointers[POINTER_START])
         _pointers[i] = _pointers[POINTER_START];
}

void Window::movePointer(_int index, _int chars)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
   
   if(chars == 0)
      return;
         
   if(index == POINTER_START)
   {
      if(chars < 0)
      {
         MAKE_ERROR(ex, Error::Text::NoBackward);
         ex->add("pointer", "start");
         ex->addInt("move", chars);
         throw ex;
      }
         
      if(_pointers[POINTER_START] + chars > _pointers[POINTER_END])
      {
         moveEnd(_pointers[POINTER_START] + chars - _pointers[POINTER_END]);
         
         if(_pointers[POINTER_START] + chars > _pointers[POINTER_END])
            chars = _pointers[POINTER_END] - _pointers[POINTER_START];
      }
      
      if(chars == 0)
         return;
      moveStart(chars);
   }
   else if(index == POINTER_END)
   {
      if(chars < 0)
      {
         MAKE_ERROR(ex, Error::Text::NoBackward);
         ex->add("pointer", "end");
         ex->addInt("move", chars);
         throw ex;
      }
      
      moveEnd(chars);
   }
   else
   {
      _int dst = _pointers[index] + chars;
      if(dst < _pointers[POINTER_START])
      {
         _pointers[index] = _pointers[POINTER_START];
      }
      else if(dst > _pointers[POINTER_END])
      {
         moveEnd(dst - _pointers[POINTER_END]);
         _pointers[index] = _pointers[POINTER_END];
      }
      else
      {
         _pointers[index] = dst;
      }
   }
}
   
void Window::setPointer(_int index, _int other)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
   
   if(other < 0 || other >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", other);
      throw ex;
   }
      
   if(index == other)
      return;
      
   if(index == POINTER_START)
   {
      /* Since the start pointer should always be 0, this should be enough:
       *  moveStart(_pointers[other]);
       * Unfortunately, we don't trust these "should"s. */
       
      _int chars = _pointers[other] - _pointers[index];
      
      if(chars < 0)
      {
         MAKE_ERROR(ex, Error::Text::NoBackward);
         ex->add("pointer", "start");
         ex->addInt("move", chars);
         throw ex;
      }
         
      moveStart(chars); 
   }
   else if(index == POINTER_END)
   {
      if(_pointers[index] != _pointers[other])
      {
         MAKE_ERROR(ex, Error::Text::NoBackward);
         ex->add("pointer", "end");
         ex->addInt("other", other);
         throw ex;
      }
   }
   else
   {
      _pointers[index] = _pointers[other];
   }
}
   
_int Window::getPointer(_int index)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
      
   return _pointers[index];
}
   
_int Window::getPointer(const WindowPointer &p)
{
   if(this != p._win)
   {
      MAKE_ERROR(ex, Error::Text::IncompatiblePointers);
      ex->addInt("pointer", p._index);
      throw ex;
   }
   
   return getPointer(p._index);
}
   
   
_int Window::copyPointer(_int index)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
   
   for(_int i = POINTER_RESULT + 1; i < _refs.count(); i++)
      if(_refs[i] == 0)
      {
         // Reuse position
         _pointers[i] = _pointers[index];
         return i;
      }
   
   _refs.add(0);
   return _pointers.add(_pointers[index]);
}


void Window::addRef(_int index)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
      
   _refs[index]++;
}
   
void Window::removeRef(_int index)
{
   if(index < 0 || index >= _pointers.count())
   {
      MAKE_ERROR(ex, Error::Text::InvalidPointer);
      ex->addInt("index", index);
      throw ex;
   }
      
   if(_refs[index] > 0)
      _refs[index]--;
      
   // clean up
   _int pos = _pointers.count() - 1;
   for(; pos > POINTER_RESULT; pos--)
      if(_refs[pos] != 0)
         break;
         
   pos++;
   _pointers.setCount(pos);
   _refs.setCount(pos);
}

} } }

