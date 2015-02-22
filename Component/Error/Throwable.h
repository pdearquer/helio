/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Generic error descriptor.
 * Base of any class that can be thrown or, more generally, that
 * describes an error.
 *
 * Do not use this class directly, intead use any of its three
 * children; Exception, Error or Fault. Each of them have a different
 * porpuse:
 *  Exception: Normal error handling user data. Recoverable.
 *  Error: Error in the applciation itself. Unrecoverable.
 *  Fault: Critical error. Do not try to catch them unless you know
 *     what you are doing. Created with the Safe Allocator.
 *
 * The Exceptions, Errors and Faults to be used are defined in Throwables.xml.
 */
class Throwable :
   public virtual Object
{
protected:
   /**
    * Explansion of the error.
    */
   String _msg;
 
   /**
    * Parameters table with especific details.
    */
   Table<String, String> _params;

   /**
    * Next throwable of the chain (reason of this exception) or null if none.
    */
   Throwable *_child;
   
   /**
    * Stack trace of the error or null if none.
    */
   Trace *_trace;

   
   /**
    * Protected constructor; init() must be called.
    */    
   Throwable();
   
   /**
    * Initilaze the class.
    * Must be called once and only once in the constructor.
    */    
   void init(String msg, Throwable *child, String source, _int line, String date);
   
public:
   /**
    * Destroy the trace and children exceptions.
    */
   ~Throwable();
   
   
   /**
    * Returns the message of the error.
    */
   String msg();
   
   /**
    * Returns the error parameters.
    */
   const Table<String, String> *params();
   
   /**
    * Returns the exception that caused this or null if none.
    */
   Throwable *child();
   
   /**
    * Returns the stack trace of the error or null if none.
    */
   Trace *trace();
   
   
   /**
    * Reports the error to the user.
    */
   void report();
   
   /**
    * Reports the error silently (e.g. to a log file).
    */
   void reportSilenty();
   
   
   /**
    * Adds a string parameter to the exception.
    */
   void add(String param, const String &value);
   
   /**
    * Adds a generic object to the exception.
    */
   void add(String param, const Object *value);
   
   /**
    * Adds an integer parameter to the exception.
    */
   void addInt(String param, _int value);
   
   /**
    * Adds a byte parameter to the exception.
    */
   void addByte(String param, _byte value);
   
   /**
    * Adds an unsigned integer to the exception.
    */
   void addUInt32(String param, _uint32 value);
   
   /**
    * Adds a pointer to the exception.
    */
   void addPointer(String param, const _pointer value);
   
   /**
    * Adds a pointer to an object to the exception.
    */
   void addPointer(String param, const Object *value);
};


#ifndef __TIMESTAMP__
 #define __TIMESTAMP__ (__DATE__ " " __TIME__)
#endif

#define MAKE_ERROR(type) \
      new type (null, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)
      
#define RE_MAKE_ERROR(type, prev) \
      new type (prev, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)

#define ERROR(type) \
      throw MAKE_ERROR(type)

#define RE_ERROR(type, prev) \
      throw RE_MAKE_ERROR(type, prev)  
            
/*      
   Exception *ex = MAKE_ERROR(Exception::Format);
   ex->add("param1", "value");
   throw ex;
*/

