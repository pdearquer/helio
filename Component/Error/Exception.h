/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Exception description container
 * Exception description container
 */
class Exception :
   public virtual Object
{
protected:
   /**
    * Cause identifier.
    */
   String _id;
   
public:   
   /**
    * Parameters table.
    */
   Table<String, String> params;


protected:
   /**
    * Subordinated exception or null if none.
    */
   Exception *_child;
   
   /**
    * Stack trace of the error.
    */
   Trace *_trace;

   
public:
   /**
    * Exception creation.
    */    
   Exception(String id, _int discard = 0);
   
   /**
    * Exception creation from an exinting trace.
    * @param trace Note that the exception take ownership of the trace
    */    
   Exception(String id, Trace *trace);

   /**
    * Exception creation with debug information.
    */
   Exception(String id, String source, _int line, String date);
   
   /**
    * Exception creation with child exception and debug information.
    */    
   Exception(String id, Exception *cause, String source, _int line, String date);
   
   /**
    * Destroy the trace and children exceptions.
    */
   ~Exception();
   
   
   /**
    * Returns the cause identifier.    
    */
   String id();
   
   /**
    * Get the translated message of the error.
    */
   String msg();
   
   
   /**
    * Add a parameter to the exception.
    */
   void add(String param, const String &value);
   void add(String param, const Object *value);   
   void addInt(String param, _int value);
   void addByte(String param, _byte value);
   void addUInt32(String param, _uint32 value);
   void addPointer(String param, const _pointer value);
   void addPointer(String param, const Object *value);
   
   /**
    * Subordinated exception or null if none.
    */
   Exception *child();
   
   
   /**
    * Get the stack trace of the error.
    */
   Trace *trace();

   /**
    * Dump the exception detail into a text string.
    */
   String dump();
};

