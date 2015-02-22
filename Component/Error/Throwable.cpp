/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Component {
namespace Error {

Throwable::Throwable()
{
   _child = null;
   _trace = new Trace(1);
}

void Throwable::init(String msg, Throwable *child, const String &source, _int line, const String &date)
{
   _msg = msg;
   _child = child;
   
   add("debug.file", source);
   addInt("debug.line", line);
   add("debug.date", date);
}

Throwable::~Throwable()
{
   if(_child != null)
      delete _child;

   delete _trace;
}


String Throwable::msg()
{
   return _msg;
}
   
const Table<String, String> *Throwable::params()
{
   return &_params;
}
   
Throwable *Throwable::child()
{
   return _child;
}
   
Trace *Throwable::trace()
{
   return _trace;
}


void Throwable::report()
{
   Reporter::report(this, false);
}
   
void Throwable::reportSilenty()
{
   Reporter::report(this, true);
}
   

void Throwable::add(String param, const String &value)
{
   _params.add(param, value);
}

void Throwable::add(String param, const Object *value)
{
   _params.add(param, value->toString());
}

void Throwable::addInt(String param, _int value)
{
   _params.add(param, Integer(value).toString());
}

void Throwable::addByte(String param, _byte value)
{
   _params.add(param, Integer(value).toString());
}

void Throwable::addUInt32(String param, _uint32 value)
{
   _params.add(param, Integer((_int)value).toString());
}

void Throwable::addPointer(String param, const _pointer value)
{
   _params.add(param, Pointer(value).toString());
}

void Throwable::addPointer(String param, const Object *value)
{
   _params.add(param, Pointer((const _pointer)value).toString());
}

} }

