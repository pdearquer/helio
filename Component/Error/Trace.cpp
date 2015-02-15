/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#include <execinfo.h>
#include <stdlib.h>

namespace Component {
namespace Error {

Trace::Trace(_int discard)
{
   discard++;  // Remove this call
   
   _pointers = backtrace(_trace, 32);
   
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


String Trace::toString() const
{
   char **syms;
   syms = backtrace_symbols(_trace, _pointers);
   
   StringBuffer res;
   
   for(_int i = 0; i < _pointers; i++)
   {
      res.add((StringBuffer)" " + syms[i] + "\n");
   }
   
   free(syms);
   
   return res;
}

} }

