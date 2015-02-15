/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Component {
namespace Error {

Exception::Exception(String id, _int discard)
{
   _id = id;
   _child = null;
   _trace = new Trace(1 + discard);
}

Exception::Exception(String id, Trace *trace)
{
   _id = id;
   _child = null;
   _trace = trace;
}

Exception::Exception(String id, String source, _int line, String date)
{
   _id = id;
   _child = null;
   _trace = new Trace(1);
   
   add("debug.file", source);
   addInt("debug.line", line);
   add("debug.date", date);
}

Exception::Exception(String id, Exception *cause, String source, _int line, String date)
{
   _id = id;
   _child = cause;
   _trace = new Trace(1);

   add("debug.file", source);
   addInt("debug.line", line);
   add("debug.date", date);
}

Exception::~Exception()
{
   if(_child != null)
      delete _child;

   delete _trace;
}


String Exception::id()
{
   return _id;
}

String Exception::msg()
{
   try
   {
      return Messages::get(_id);
   }
   catch(Exception *ex)
   {
      return id();
   }
}


void Exception::add(String param, const String &value)
{
   params.add(param, value);
}

void Exception::add(String param, const Object *value)
{
   params.add(param, value->toString());
}

void Exception::addInt(String param, _int value)
{
   params.add(param, Integer(value).toString());
}

void Exception::addByte(String param, _byte value)
{
   params.add(param, Integer(value).toString());
}

void Exception::addUInt32(String param, _uint32 value)
{
   params.add(param, Integer((_int)value).toString());
}

void Exception::addPointer(String param, const _pointer value)
{
   params.add(param, Pointer(value).toString());
}

void Exception::addPointer(String param, const Object *value)
{
   params.add(param, Pointer((const _pointer)value).toString());
}


Exception *Exception::child()
{
   return _child;
}

Trace *Exception::trace()
{
   return _trace;
}


String Exception::dump()
{
   Exception *ex = this;
   
   StringBuffer res = "Exception: ";

   _bool first = true;
   while(ex != null)
   {
      try
      {
         res.add(Messages::get(ex->_id));
      }
      catch(Exception *ex2)
      {
         res.add(ex->_id + "\n");
         res.add(" (" + ex2->msg() + ")");
      }
      res.add("\n");
      
      _int pars = 0;
      if(ex->params.containsKey("debug.file"))
      {
         res.add(" from " + ex->params.get("debug.file"));
         pars++;
         
         if(ex->params.containsKey("debug.line"))
         {
            res.add(':' + ex->params.get("debug.line"));
            pars++;
         }
         
         if(ex->params.containsKey("debug.date"))
         {
            res.add(" (" + ex->params.get("debug.date") + ")");
            pars++;
         }

         res.add("\n");
      }
      
      if(ex->params.count() > pars)
      {
         for(_int i = 0; i < ex->params.count(); i++)
         {
            String key = ex->params.getKey(i);
            if(key != "debug.file" && key != "debug.line" && key != "debug.date")
            {
               res.add("   " + key + ": " + ex->params.get(key) + "\n");
            }
         }
      }
   
      if(first)
      {
         res.add(_trace->toString());
         first = false;
      }
   
      ex = ex->_child;
      if(ex == null)
         break;
         
      res.add("Child exception: ");
   }
   
   return res;
}

} }

