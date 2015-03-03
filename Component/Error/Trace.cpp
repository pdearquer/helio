/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#include <execinfo.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cxxabi.h>

namespace Component {
namespace Error {

const_int Trace::MAX_POINTERS;


String Trace::demangleSymbol(const char *mangled)
{
   int status;
   char *demangled = abi::__cxa_demangle(mangled, 0, 0, &status);
   if(demangled == null)
      return (String)mangled;
   String ret = demangled;
   free(demangled);
   if(status == 0)
      return ret;
   return (String)mangled;
}

String Trace::pointerInfo(_pointer p)
{
   Dl_info info;
   if(dladdr((void *)p, &info) == 0)
      return Pointer(p).toString();

   return (StringBuffer)demangleSymbol(info.dli_sname) + " [+" + -Pointer::diff(p, info.dli_saddr) + "]";
}


Trace::Trace(_int discard)
{
   discard++;  // Remove this call
   
   _pointers = backtrace(_trace, MAX_POINTERS);
   if(_pointers > 1)
      _pointers--;   // Last one makes dladdr to crash
   
   if(discard < 0 || discard >= _pointers)
      return;
   
   for(_int i = 0; i < _pointers - discard; i++)
      _trace[i] = _trace[i + discard];
   _pointers -= discard;   
}

Trace::Trace(Trace *other)
{
   _pointers = other->_pointers;
   
   for(_int i = 0; i < _pointers; i++)
      _trace[i] = other->_trace[i];
}


_int Trace::pointers()
{
   return _pointers;
}
   
_pointer Trace::getPointer(_int index)
{
   if(index < 0 || index >= _pointers)
   {
      MAKE_ERROR(ex, ::Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("pointers", _pointers);
      throw ex;
   }
   
   return (_pointer)_trace[index];
}

} }

