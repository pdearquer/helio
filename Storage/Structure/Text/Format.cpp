/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

Format *Format::_default = null;


Format::Format()
{
   _base = 10;
   _digits = "0123456789ABCDEF";
   _igncase = true;
   _minDigits = 0;
   _sign = false;
   _precision = 3;
}
   
Format::Format(Format *fmt)
{
   _base = fmt->_base;
   _digits = fmt->_digits;
   _igncase = fmt->_igncase;
   _minDigits = fmt->_minDigits;
   _sign = fmt->_sign;
   _precision = fmt->_precision;
}
  

Format *Format::def()
{
   if(_default == null)
      _default = new Format();
   
   return _default;
}
   

_bool Format::toBool(const String &str)
{
   if(str.equals("true", _igncase) || str.equals("1"))
      return true;
      
   if(str.equals("false", _igncase) || str.equals("0"))
      return false;
      
   Exception *ex = MAKE_ERROR(Exception::Format);
   ex->add("convertion", "toBool");
   ex->add("string", str);
   throw ex;
}
   
_bool Format::toBool(Window *win, WindowPointer &p)
{
   if(win->is("true", p, _igncase))
   {
      p += 4;
      return true;
   }
   
   if(win->is("1", p))
   {
      p++;
      return true;
   }
      
   if(win->is("false", p, _igncase))
   {
      p += 5;
      return false;
   }
   
   if(win->is("0", p))
   {
      p++;
      return false;
   }
      
   Exception *ex = MAKE_ERROR(Exception::Format);
   ex->add("convertion", "toBool");
   ex->add("string", win->getString(p, win->end()));
   throw ex;
}
   
_bool Format::toBool(Window *win, const WindowPointer &from, const WindowPointer &to)
{
   switch(from.diff(to))
   {
      case 1:
         if(win->is("1", from))
            return true;
         if(win->is("0", from))
            return false;
         break;
         
      case 4:
         if(win->is("true", from, _igncase))
            return true;
         break;
         
      case 5:
         if(win->is("false", from, _igncase))
            return true;
         break;
   }
   
   Exception *ex = MAKE_ERROR(Exception::Format);
   ex->add("convertion", "toBool");
   ex->add("string", win->getString(from, to));
   throw ex;
}


_int Format::toInt(const String &str)
{
   StringWindow *sw = new StringWindow(str);
   _int ret;
   try
   {
      sw->finish();  // Ensure take into account the whole string
      ret = toInt(sw, sw->start(), sw->end());
   }
   catch(Exception *ex)
   {
      delete sw;
      throw ex;
   }
   return ret;
}
   
_int Format::toInt(Window *win, WindowPointer &p)
{
   WindowPointer p2 = p.dup();

   __sint64 num;
   try
   {
      num = toSInt64(win, p2);
   }
   catch(Exception *ex2)
   {
      Exception *ex = RE_MAKE_ERROR(Exception::Format, ex2);
      ex->add("convertion", "toInt");
      ex->add("string", win->getString(p, p + 20));
      throw ex;
   }
   
   if(num < (__sint64)__HELIO_TYPE_INT_MIN || num > (__sint64)__HELIO_TYPE_INT_MAX)
   {
      Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
      ex->add("convertion", "toInt");
      ex->add("string", win->getString(p, p2));
      throw ex;
   }

   p = p2;
   return (_int)num;
}
   
_int Format::toInt(Window *win, const WindowPointer &from, const WindowPointer &to)
{
   __sint64 num;
   try
   {
      num = toSInt64(win, from, to);
   }
   catch(Exception *ex2)
   {
      Exception *ex = RE_MAKE_ERROR(Exception::Format, ex2);
      ex->add("convertion", "toInt");
      ex->add("string", win->getString(from, to));
      throw ex;
   }
   
   if(num < (__sint64)__HELIO_TYPE_INT_MIN || num > (__sint64)__HELIO_TYPE_INT_MAX)
   {
      Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
      ex->add("convertion", "toInt");
      ex->add("string", win->getString(from, to));
      throw ex;
   }

   return (_int)num;
}


__uint64 Format::toUInt64(const String &str)
{
   StringWindow *sw = new StringWindow(str);
   __uint64 ret;
   try
   {
      sw->finish();
      ret = toUInt64(sw, sw->start(), sw->end());
   }
   catch(Exception *ex)
   {
      delete sw;
      throw ex;
   }
   return ret;
}

__uint64 Format::toUInt64(Window *win, WindowPointer &p)
{
   WindowPointer p2 = p.dup();
 
   if(win->is('+', p2))
   {      
      if(win->hasFinished(p2))
      {
         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toUInt64");
         ex->add("reason", "No digit");
         ex->add("string", win->getString(p, p + 10));
         throw ex;
      }
      
      p2++;
   }
   
   __uint64 num = 0;
   _bool found = false;
   __uint64 ubase = (__uint64)_base;
   __uint64 mult_limit = __HELIO_TYPE_UINT64_MAX / ubase;
   while(true)
   {
      Character c = win->getChar(p2);
      
      _int dig = 0;
      while(true)
      {
         if(c.equals(_digits.get(dig), _igncase))
         {
            found = true;          
            break;
         }
         
         dig++;
         if(dig >= _base)
         {
            if(!found)
            {
               Exception *ex = MAKE_ERROR(Exception::Format);
               ex->add("convertion", "toUInt64");
               ex->add("string", win->getString(p, p2));
               throw ex;
            }
            else
            {
               found = false;
               break;
            }
         }
      }
      if(!found)
         break;
      
      if(num > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toUInt64");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      num *= ubase;
      
      __uint64 udig = (__uint64)dig;
      if(num > __HELIO_TYPE_UINT64_MAX - udig)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toUInt64");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      num += udig;

      if(win->hasFinished(p2))
         break;
      p2++;
   } 
   
   p = p2;
   return num;
}
   
__uint64 Format::toUInt64(Window *win, const WindowPointer &from, const WindowPointer &to)
{
   WindowPointer p = from.dup();
   
   if(win->is("+", p))
   {
      if(p == to)
      {
         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toUInt64");
         ex->add("reason", "No digit");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      
      p++;
   }
   
   __uint64 num = 0;
   __uint64 ubase = (__uint64)_base;
   __uint64 mult_limit = __HELIO_TYPE_UINT64_MAX / ubase;
   while(true)
   {
      Character c = win->getChar(p);
      
      _int dig = 0;
      while(true)
      {
         if(c.equals(_digits.get(dig), _igncase))
            break;
         
         dig++;
         if(dig >= _base)
         {
            Exception *ex = MAKE_ERROR(Exception::Format);
            ex->add("convertion", "toUInt64");
            ex->add("string", win->getString(from, to));
            throw ex;
         }
      }
      
      if(num > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toUInt64");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      num *= ubase;
      
      __uint64 udig = (__uint64)dig;
      if(num > __HELIO_TYPE_UINT64_MAX - udig)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toUInt64");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      num += udig;

      if(p == to)
         break;
      p++;
   } 
   
   return num;
}


__sint64 Format::toSInt64(const String &str)
{
   StringWindow *sw = new StringWindow(str);
   __sint64 ret;
   try
   {
      sw->finish();
      ret = toSInt64(sw, sw->start(), sw->end());
   }
   catch(Exception *ex)
   {
      delete sw;
      throw ex;
   }
   return ret;
}

__sint64 Format::toSInt64(Window *win, WindowPointer &p)
{
   WindowPointer p2 = p.dup();

   _bool neg = false;   
   if(win->isAny("-+", p2))
   {
      if(win->is('-', p2))
         neg = true;
      
      if(win->hasFinished(p2))
      {
         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toSInt64");
         ex->add("reason", "No digit");
         ex->add("string", win->getString(p, p + 10));
         throw ex;
      }
      
      p2++;
   }
   
   if(win->is('+', p2))
   {
      Exception *ex = MAKE_ERROR(Exception::Format);
      ex->add("convertion", "toSInt64");
      ex->add("reason", "Sign duplicated");
      ex->add("string", win->getString(p, p + 10));
      throw ex;
   }
   
   __uint64 unum;
   try
   {
      unum = toUInt64(win, p2);
   }
   catch(Exception *ex2)
   {
      Exception *ex = RE_MAKE_ERROR(Exception::Format, ex2);
      ex->add("convertion", "toSInt64");
      ex->add("string", win->getString(p, p + 20));
      throw ex;
   }
   
   __sint64 num;
   if(neg)
   {
      if(unum > (__uint64)__HELIO_TYPE_SINT64_MIN)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toSInt64");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      
      num = (__sint64)unum;
      if(num > 0)
         num = -num;
   }
   else
   {
      if(unum > (__uint64)__HELIO_TYPE_SINT64_MAX)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toSInt64");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      
      num = (__sint64)unum;
   }
   
   p = p2;
   return num;
}
   
__sint64 Format::toSInt64(Window *win, const WindowPointer &from, const WindowPointer &to)
{
   WindowPointer p = from.dup();

   _bool neg = false;   
   if(win->isAny("-+", p))
   {
      if(win->is('-', p))
         neg = true;
      
      if(p == to)
      {
         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toSInt64");
         ex->add("reason", "No digit");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      
      p++;
   }
   
   if(win->is('+', p))
   {
      Exception *ex = MAKE_ERROR(Exception::Format);
      ex->add("convertion", "toSInt64");
      ex->add("reason", "Sign duplicated");
      ex->add("string", win->getString(from, to));
      throw ex;
   }
   
   __uint64 unum;
   try
   {
      unum = toUInt64(win, p, to);
   }
   catch(Exception *ex2)
   {
      Exception *ex = RE_MAKE_ERROR(Exception::Format, ex2);
      ex->add("convertion", "toSInt64");
      ex->add("string", win->getString(from, to));
      throw ex;
   }
   
   __sint64 num;
   if(neg)
   {
      if(unum > (__uint64)__HELIO_TYPE_SINT64_MIN)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toSInt64");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      
      num = (__sint64)unum;
      if(num > 0)
         num = -num;
   }
   else
   {
      if(unum > (__uint64)__HELIO_TYPE_SINT64_MAX)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toSInt64");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      
      num = (__sint64)unum;
   }

   return num;
}

  
_float Format::toFloat(const String &str)
{
   StringWindow *sw = new StringWindow(str);
   _float ret;
   try
   {
      sw->finish();  // Ensure take into account the whole string
      ret = toFloat(sw, sw->start(), sw->end());
   }
   catch(Exception *ex)
   {
      delete sw;
      throw ex;
   }
   return ret;
}
   
_float Format::toFloat(Window *win, WindowPointer &p)
{
   // TODO: Use Precision utilities instead

   WindowPointer p2 = p.dup();

   _bool neg = false;   
   if(win->isAny("-+", p2))
   {
      if(win->is('-', p2))
         neg = true;
      
      if(win->hasFinished(p2))
      {
         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toFloat");
         ex->add("reason", "No digit");
         ex->add("string", win->getString(p, p + 10));
         throw ex;
      }
      
      p2++;
   }
   
   _uint64 num = 0;
   _bool found = false;
   _uint64 ubase = (_uint64)_base;
   _uint64 mult_limit = __HELIO_TYPE_UINT64_MAX / ubase;
   Float ret;
   while(true)
   {
      Character c = win->getChar(p2);
      
      if(c == '.')
      {
         if(found)
            break;

         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(p, p + 10));
         throw ex;
      }
      
      _int dig = 0;
      while(true)
      {
         if(c.equals(_digits.get(dig), _igncase))
         {
            found = true;          
            break;
         }
         
         dig++;
         if(dig >= _base)
         {
            if(!found)
            {
               Exception *ex = MAKE_ERROR(Exception::Format);
               ex->add("convertion", "toFloat");
               ex->add("string", win->getString(p, p + 10));
               throw ex;
            }
            else
            {
               // No decimal part 
               ret.setRaw((__float)num);
               if(neg)
                  ret = -ret;

               p = p2;
               return ret;
            }
         }
      }
    
      if(num > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      num *= ubase;
      
      _uint64 udig = (_uint64)dig;
      if(num > __HELIO_TYPE_UINT64_MAX - udig)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      num += udig;

      if(win->hasFinished(p2))
         break;
      p2++;
   }  
   
   if(win->hasFinished(p2))
   {
      // No decimal part
      ret.setRaw((__float)num);
      if(neg)
         ret = -ret;

      p = p2;
      return ret;
   }
   p2++;
   
   _uint64 dec = 0;
   _uint64 pre = 1;
   found = true;
   while(true)
   {
      Character c = win->getChar(p2);
      
      _int dig = 0;
      while(true)
      {
         if(c.equals(_digits.get(dig), _igncase))        
            break;
         
         dig++;
         if(dig >= _base)
         {
            found = false;
            break;
         }
      }
      if(!found)
         break;      
    
      if(pre > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      pre *= ubase;
      
      if(dec > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      dec *= ubase;
      
      _uint64 udig = (_uint64)dig;
      if(dec > __HELIO_TYPE_UINT64_MAX - udig)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(p, p2));
         throw ex;
      }
      dec += udig;

      if(win->hasFinished(p2))
         break;
      p2++;
   }
   
   ret.setRaw((__float)num + (__float)dec / (__float)pre);
   
   if(neg)
      ret = -ret;
   
   p = p2;
   return ret;
}
   
_float Format::toFloat(Window *win, const WindowPointer &from, const WindowPointer &to)
{
   // TODO: Use Precision utilities instead

   WindowPointer p = from.dup();

   _bool neg = false;   
   if(win->isAny("-+", p))
   {
      if(win->is('-', p))
         neg = true;
      
      if(p == to)
      {
         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toFloat");
         ex->add("reason", "No digit");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      
      p++;
   }
   
   _uint64 num = 0;
   _bool found = false;
   _uint64 ubase = (_uint64)_base;
   _uint64 mult_limit = __HELIO_TYPE_UINT64_MAX / ubase;
   Float ret;
   while(true)
   {
      Character c = win->getChar(p);
      
      if(c == '.')
      {
         if(found)
            break;

         Exception *ex = MAKE_ERROR(Exception::Format);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      
      _int dig = 0;
      while(true)
      {
         if(c.equals(_digits.get(dig), _igncase))
         {
            found = true;          
            break;
         }
         
         dig++;
         if(dig >= _base)
         {
            Exception *ex = MAKE_ERROR(Exception::Format);
            ex->add("convertion", "toFloat");
            ex->add("string", win->getString(from, to));
            throw ex;
         }
      }
      
      if(num > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      num *= ubase;
      
      _uint64 udig = (_uint64)dig;
      if(num > __HELIO_TYPE_UINT64_MAX - udig)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      num += udig;

      if(p == to)
         break;
      p++;
   }
          
   if(p == to)
   {
      // No decimal part
      ret.setRaw((__float)num);
      if(neg)
         return -ret;
      return ret;
   }
   p++;
   
   _uint64 dec = 0;
   _uint64 pre = 1;
   while(true)
   {
      Character c = win->getChar(p);
      
      _int dig = 0;
      while(true)
      {
         if(c.equals(_digits.get(dig), _igncase))        
            break;
         
         dig++;
         if(dig >= _base)
         {
            Exception *ex = MAKE_ERROR(Exception::Format);
            ex->add("convertion", "toFloat");
            ex->add("string", win->getString(from, to));
            throw ex;
         }
      }    
    
      if(pre > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      pre *= ubase;
      
      if(dec > mult_limit)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      dec *= ubase;
      
      _uint64 udig = (_uint64)dig;
      if(dec > __HELIO_TYPE_UINT64_MAX - udig)
      {
         Exception *ex = MAKE_ERROR(Exception::Format::Overflow);
         ex->add("convertion", "toFloat");
         ex->add("string", win->getString(from, to));
         throw ex;
      }
      dec += udig;

      if(p == to)
         break;
      p++;
   }

   ret.setRaw((__float)num + (__float)dec / (__float)pre);
   
   if(neg)
      ret = -ret;
      
   return ret;
}
   
   
Character Format::toChar(const String &str)
{
   if(str.length() != 1)
   {
      Exception *ex = MAKE_ERROR(Exception::Format);
      ex->add("convertion", "toChar");
      ex->add("string", str);
      throw ex;
   }
   
   return str.get(0);
}


_pointer Format::toPointer(const String &str)
{
   StringWindow *sw = new StringWindow(str);
   _pointer ret;
   try
   {
      sw->finish();  // Ensure take into account the whole string
      ret = toPointer(sw, sw->start(), sw->end());
   }
   catch(Exception *ex)
   {
      delete sw;
      throw ex;
   }
   return ret;
}
   
_pointer Format::toPointer(Window *win, WindowPointer &p)
{
   WindowPointer p2 = p.dup();
   
   if(!win->is("0x", p2))
   {
      Exception *ex = MAKE_ERROR(Exception::Format);
      ex->add("convertion", "toPointer");
      ex->add("string", win->getString(p2, p2 + 10));
      throw ex;
   }
   p2 += 2;
   
   __uint64 num;
   Format *f = new Format();
   f->base(16);
   try
   {
      num = f->toUInt64(win, p2);
   }
   catch(Exception *ex2)
   {
      delete f;
      Exception *ex = RE_MAKE_ERROR(Exception::Format, ex2);
      ex->add("convertion", "toPointer");
      ex->add("string", win->getString(p2, p2 + 20));
      throw ex;
   }
   delete f;
   
   Pointer ret;
   ret.setRaw((__pointer)num);
   
   p = p2;
   return ret;
}
   
_pointer Format::toPointer(Window *win, const WindowPointer &from, const WindowPointer &to)
{
   WindowPointer p = from.dup();
   
   if(!win->is("0x", p))
   {
      Exception *ex = MAKE_ERROR(Exception::Format);
      ex->add("convertion", "toPointer");
      ex->add("string", win->getString(p, p + 10));
      throw ex;
   }
   p += 2;
   
   __uint64 num;
   Format *f = new Format();
   f->base(16);
   try
   {
      num = f->toUInt64(win, p, to);
   }
   catch(Exception *ex2)
   {
      delete f;
      Exception *ex = RE_MAKE_ERROR(Exception::Format, ex2);
      ex->add("convertion", "toPointer");
      ex->add("string", win->getString(from, to));
      throw ex;
   }
   delete f;
   
   Pointer ret;
   ret.setRaw((__pointer)num);
   
   return ret;
}


#if 0
Date Format::toDate(const String &str);
#endif

   
String Format::toString(_bool b)
{
   if(b)
      return "true";
   else
      return "false";
}
   
Buffer *Format::toBuffer(_bool b)
{
   Buffer *buf = new Buffer();   
   if(b)
      buf->add("true");
   else
      buf->add("false");
   return buf;
}


String Format::toString(_int num)
{
   return toString(num, _base);
}
   
String Format::toString(_int num, _int base)
{
   Buffer *b = toBuffer(num, base);
   String ret = b->toString();
   delete b;
   return ret;
}
   
Buffer *Format::toBuffer(_int num)
{
   return toBuffer(num, _base);
}
   
Buffer *Format::toBuffer(_int num, _int base)
{
   if(base < 2 || base > _digits.length())
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidBase);
      ex->addInt("base", base);
      ex->add("digits", _digits);
      throw ex;
   }
   
   if(num == __HELIO_TYPE_INT_MIN)
   {
      return toBuffer((__sint64)num, base);
   }
   
   _bool neg = false;   
   if(num < 0)
   {
      neg = true;
      num = -num;
   }
   
   Buffer *buf = new Buffer(); 
   do
   {
      buf->add(_digits.get(num % base));
      
      num = num / base;
   }
   while(num != 0);
   
   if(_minDigits > 0)
      buf->padRight(_minDigits, _digits.get(0));
   
   if(neg)
   {
      buf->add('-');
   }
   else if(_sign)
   {
      buf->add('+');
   } 

   buf->reverse();   
      
   return buf;
}


String Format::toString(__uint64 num)
{
   return toString(num, _base);
}
   
String Format::toString(__uint64 num, _int base)
{
   Buffer *b = toBuffer(num, base);
   String ret = b->toString();
   delete b;
   return ret;
}
   
Buffer *Format::toBuffer(__uint64 num)
{
   return toBuffer(num, _base);
}
   
Buffer *Format::toBuffer(__uint64 num, _int base)
{
   if(base < 2 || base > _digits.length())
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidBase);
      ex->addInt("base", base);
      ex->add("digits", _digits);
      throw ex;
   }
   
   Buffer *buf = new Buffer();
   if(base == 16)
   {
      do
      {
         buf->add(_digits.get((_int)(num & 0x0F)));
         
         num = num >> 4;
      }
      while(num != 0);
   }
   else
   {
      __uint64 ubase = (__uint64)base;
      do
      {
         buf->add(_digits.get((_int)(num % ubase)));
         
         num = num / ubase;
      }
      while(num != 0);
   }
   
   if(_minDigits > 0)
      buf->padRight(_minDigits, _digits.get(0));

   buf->reverse();   
      
   return buf;
}
   
   
String Format::toString(__sint64 num)
{
   return toString(num, _base);
}
   
String Format::toString(__sint64 num, _int base)
{
   Buffer *b = toBuffer(num, base);
   String ret = b->toString();
   delete b;
   return ret;
}
   
Buffer *Format::toBuffer(__sint64 num)
{
   return toBuffer(num, _base);
}
   
Buffer *Format::toBuffer(__sint64 num, _int base)
{
   if(base < 2 || base > _digits.length())
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidBase);
      ex->addInt("base", base);
      ex->add("digits", _digits);
      throw ex;
   }
   
   Buffer *buf;
   if(num == __HELIO_TYPE_SINT64_MIN)
   {
      buf = toBuffer((__uint64)num, base);
      buf->insert(0, "-");
      return buf;
   }

   _bool neg = false;
   if(num < 0)
   {
      neg = true;
      num = -num;
   }
   
   buf = new Buffer();
   __sint64 sbase = (__sint64)base;
   do
   {
      buf->add(_digits.get(num % sbase));
      
      num = num / sbase;
   }
   while(num != 0);
   
   if(_minDigits > 0)
      buf->padRight(_minDigits, _digits.get(0));
   
   if(neg)
   {
      buf->add('-');
   }
   else if(_sign)
   {
      buf->add('+');
   } 

   buf->reverse();   
      
   return buf;
}
   
   
String Format::toString(_float num)
{
   Buffer *b = toBuffer(num);
   String ret = b->toString();
   delete b;
   return ret;
}
   
Buffer *Format::toBuffer(_float num)
{
   // TODO: Use Precision package instead
   
   _int digits = 9;
   __float multiplier = 1000000000.0;
   __float raw = Float(num).raw();
   
   __sint64 integer = (__sint64)raw;         
   __sint64 decimal = (__sint64)((raw - (__float)integer) * multiplier);

   Buffer *buf;
   if(integer != 0)
   {
      buf = toBuffer(integer);
   }
   else
   {
      if(decimal < 0)
         buf = new Buffer("-0");
      else
         buf = new Buffer("0");
   }

   if(decimal < 0)
      decimal = -decimal;
   
   if(_precision <= 0 && decimal == 0)
      return buf;
   
   buf->add('.');
   
   Format *fmt = new Format();   
   fmt->minDigits(digits);
   Buffer *tmp = fmt->toBuffer(decimal);
   delete fmt;
   
   if(_precision <= 0)
   {
      for(_int i = tmp->length() - 1; i > 0; i--)
      {
         if(tmp->get(i) == '0')
            tmp->setLength(i);
         else
            break;
      }
   }
   else if(_precision < tmp->length())
   {
      tmp->setLength(_precision);
   }
   
   buf->add(tmp);
   delete tmp;
   
   return buf;
}


String Format::toString(_char c)
{
   return (String)c;
}

Buffer *Format::toBuffer(_char c)
{
   return new Buffer(c);
}


String Format::toString(_pointer p)
{
   Buffer *b = toBuffer(p);
   String ret = b->toString();
   delete b;
   return ret;
}

Buffer *Format::toBuffer(_pointer p)
{
   Buffer *buf;
   Format *f = new Format();
   f->base(16);
   f->minDigits(sizeof(__pointer) * 2);
   try
   {
      buf = f->toBuffer((_uint64)Pointer(p).raw());
   }
   catch(Exception *ex)
   {
      delete f;
      throw ex;
   }
   delete f;
   
   buf->insert(0, "0x");
   
   return buf;
}


String Format::toString(const Date &date)
{
   // TODO: Make a proper Calendar class
   
#ifdef __HELIO_DEVICE_TIME_UNIXCLOCK
   return Device::Time::UnixClock::format(&date);
#else
   ERROR(Error::NotImplemented);
#endif
}

  
String Format::printf(String fmt, ...)
{
   va_list args;

   StringBuffer res;
   StringBuffer fmt2 = fmt;   
   va_start(args, fmt);
   _int i = 0;
   
   while(i < fmt2.length())
   {
      _char c = fmt2.get(i);
      if(c != '%')
      {
         res.add(c);
      }
      else
      {
         Format *f = new Format();
         _bool zeros = false;
         
         try
         {
            _bool end = false;
            _int pad = 0;
            while(!end)
            {
               i++;
               c = fmt2.get(i);
               
               switch((char)c)
               {
                  case '%':
                     res.add('%');
                     end = true;
                     break;
                     
                  case 'd':
                  case 'i':
                     if(zeros)
                        f->minDigits(pad);                  
                     if(pad > 0 && !zeros)
                     {
                        StringBuffer buf = f->toString((_int) va_arg(args, int));
                        buf.padLeft(pad, ' ');
                        res.add(buf);
                     }
                     else
                     {
                        res.add(f->toString((_int) va_arg(args, int)));
                     }
                     end = true;
                     break;
                     
                  case 'x':
                     if(zeros)
                        f->minDigits(pad);
                     f->base(16);
                     f->digits("0123456789abcdef");
                     if(pad > 0 && !zeros)
                     {
                        StringBuffer buf = f->toString((_int) va_arg(args, int));
                        buf.padLeft(pad, ' ');
                        res.add(buf);
                     }
                     else
                     {
                        res.add(f->toString((_int) va_arg(args, int)));
                     }
                     end = true;
                     break;

                  case 'X':
                     if(zeros)
                        f->minDigits(pad);
                     f->base(16);
                     if(pad > 0 && !zeros)
                     {
                        StringBuffer buf = f->toString((_int) va_arg(args, int));
                        buf.padLeft(pad, ' ');
                        res.add(buf);
                     }
                     else
                     {
                        res.add(f->toString((_int) va_arg(args, int)));
                     }
                     end = true;
                     break;
                     
                  case 'o':
                     if(zeros)
                        f->minDigits(pad);
                     f->base(8);
                     if(pad > 0 && !zeros)
                     {
                        StringBuffer buf = f->toString((_int) va_arg(args, int));
                        buf.padLeft(pad, ' ');
                        res.add(buf);
                     }
                     else
                     {
                        res.add(f->toString((_int) va_arg(args, int)));
                     }
                     end = true;
                     break;
                  
                  case 'f':
                  case 'F':
                  case 'e':
                  case 'E':
                  case 'g':
                  case 'G':
                     if(zeros)
                        f->minDigits(pad);
                     if(pad > 0 && !zeros)
                     {
                        StringBuffer buf = f->toString((_float) va_arg(args, double));
                        buf.padLeft(pad, ' ');
                        res.add(buf);
                     }
                     else
                     {
                        res.add(f->toString((_float) va_arg(args, double)));
                     }
                     end = true;
                     break;
                  
                  case 'c':
                     res.add((_char)(__char)va_arg(args, int));
                     end = true;
                     break;
                     
                  case 's':
                     res.add(va_arg(args, char *));
                     end = true;
                     break;
                     
                  case 'p':
                     res.add(f->toString((_pointer) va_arg(args, void *)));
                     end = true;
                     break;
                  
                  case '+':
                     f->sign(true);
                     break;
                     
                  case '0':
                     if(pad == 0)
                     {
                        zeros = true;
                        break;
                     }
                  case '1':
                  case '2':
                  case '3':
                  case '4':
                  case '5':
                  case '6':
                  case '7':
                  case '8':
                  case '9':
                     pad = pad * 10 + (c - '0');
                     break;
                  
                  default:
                     end = true;
                     res.add("%ERROR%");
                     break;
               }
               
            }
         }
         catch(Exception *ex)
         {
            res.add("%ERROR%");
         }
         delete f;
      }
      
      i++;
   }
   
   va_end(args);   
   
   return res;   
}


_int Format::base()
{
   return _base;
}
   
_int Format::base(_int b)
{
   if(b < 2 || b > _digits.length())
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidBase);
      ex->addInt("base", b);
      ex->add("digits", _digits);
      throw ex;
   }
   
   _base = b;
   return _base;
}
   
String Format::digits()
{
   return _digits;
}

String Format::digits(String dig)
{
   if(dig.length() < 2 || dig.length() < _base)
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidDigits);
      ex->add("digits", dig);
      ex->addInt("base", _base);
      throw ex;
   }
   
   _digits = dig;
   return _digits;
}

_bool Format::igncase()
{
   return _igncase;
}

_bool Format::igncase(_bool ignore)
{
   _igncase = ignore;
   return _igncase;
}

_int Format::minDigits()
{
   return _minDigits;
}

_int Format::minDigits(_int min)
{
   _minDigits = min;
   return _minDigits;
}

_bool Format::sign()
{
   return _sign;
}

_bool Format::sign(_bool plus)
{
   _sign = plus;
   return _sign;
}

_int Format::precision()
{
   return _precision;
}

_int Format::precision(_int pre)
{
   _precision = pre;
   return _precision;
}

} } }

