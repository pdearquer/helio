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
 * TODO: Unmangle symbols.
 * TODO: Make the linker to load the symbols in memory and read them.
 */
class Trace :
   public virtual Object
{
protected:
   /**
    * Pointers trace.
    */
   void *_trace[32];
   
   /**
    * Number of pointers.
    */
   _int _pointers;
   
   
public:
   /**
    * Extract the trace from the stack discarding some last calls.
    */
   Trace(_int discard = 0);
   
   /**
    * Make a copy of another trace.
    */
   Trace(Trace *other);

   
   /**
    * Dump the trace to a String.
    */
   virtual String toString() const; 
};

