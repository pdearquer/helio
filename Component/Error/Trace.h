/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Trace the stack of an error.
 * Extract the trace of the stack where the error occur.
 * Must be created at the point that want to be traced.
 *
 * FIXME: Only works in Linux with libc.
 *    Recommended compilation with "-g3 -rdynamic" flags.
 * TODO: Make the linker to load the symbols in memory and read them.
 */
class Trace :
   public virtual Object
{
protected:
   /**
    * Maximum number of pointers stored (depth of the stack trace).
    */
   static_const_int MAX_POINTERS = 32;
   

   /**
    * Pointers trace.
    */
   void *_trace[MAX_POINTERS];
   
   /**
    * Number of pointers.
    */
   _int _pointers;
   
   
public:
   /**
    * Demangles the symbol internal name to produce the human readable name.
    */
   static String demangleSymbol(const char *mangled);

   /**
    * Returns an string with information about the pointer's closer symbol.
    */
   static String pointerInfo(_pointer p);
   

   /**
    * Extract the trace from the stack discarding some last calls.
    */
   Trace(_int discard = 0);
   
   /**
    * Make a copy of another trace.
    */
   Trace(Trace *other);


   /**
    * Returns the number of pointers stored.
    */
   virtual _int pointers();
   
   /**
    * Returns a pointer by index.
    */
   virtual _pointer getPointer(_int index);
};

