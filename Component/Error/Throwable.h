/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Generic error descriptor.
 * Base of any class that can be thrown or, more generally, that
 * describes an error.
 *
 * Do not use this class directly, instead use any of its three
 * children; Exception, Error or Fault. Each of them have a different
 * purpose:
 *  Exception: Normal error handling user data. Recoverable.
 *  Error: Error in the application itself. Unrecoverable.
 *  Fault: Critical error. Do not try to catch them unless you know
 *     what you are doing. Created with the Safe Allocator.
 *
 * The Exceptions, Errors and Faults to be used are defined in Throwables.xml.
 * Use the error macros to create or throw exceptions:
 *  MAKE_ERROR(name, type)
 *  RE_MAKE_ERROR(name, type, prev)
 *  THROW_ERROR(type)
 *  RE_THROW_ERROR(type, prev)
 *
 * For example:
 *  MAKE_ERROR(ex, Exception::Format);  // Defines a variable called "ex" and creates it
 *  ex->add("param1", "value");
 *  throw ex;
 * Or:
 *  catch(Exception::NotSupported *ex)
 *  {
 *     RE_THROW_ERROR(Exception::Device::NoDefault, ex);
 *  }
 *
 * The MAKE macros are not very intuitive, but they prevent a worse problem.
 * Consider this old example:
 *  try
 *  {
 *     Exception *ex = MAKE_ERROR(Exception::Format);
 *     throw ex;
 *  }
 *  catch(Exception::Format *ex)
 *  {
 *     // This code NEVER runs because the exception was declared and thrown
 *     // as "Exception" not "Exception::Format"!
 *     delete ex; 
 *  }
 * The new macros, as ugly as they are, avoid this.
 */
class Throwable :
   public virtual Object
{
protected:
   /**
    * Explanation of the error.
    */
   String _msg;
 
   /**
    * Parameters table with specific details.
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
   
public:
   /**
    * Destroy the trace and children exceptions.
    */
   ~Throwable();

protected:   
   /**
    * Initialize the class.
    * Must be called once and only once in the constructor.
    */    
   void init(String msg, Throwable *child, const String &source, _int line, const String &date);   


public:
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
    * Do NOT report confidential information.
    */
   void report();
   
   /**
    * Reports the error silently (e.g. to a log file).
    * Do NOT report confidential information.
    */
   void reportSilenty();
   
   
   /**
    * Adds (or overwrites) a string parameter to the exception.
    */
   void add(String param, const String &value);
   
   /**
    * Adds (or overwrites) a generic object to the exception.
    */
   void add(String param, const Object *value);
   
   /**
    * Adds (or overwrites) an integer parameter to the exception.
    */
   void addInt(String param, _int value);
   
   /**
    * Adds (or overwrites) a byte parameter to the exception.
    */
   void addByte(String param, _byte value);
   
   /**
    * Adds (or overwrites) an unsigned integer to the exception.
    */
   void addUInt32(String param, _uint32 value);
   
   /**
    * Adds (or overwrites) a pointer to the exception.
    */
   void addPointer(String param, const _pointer value);
   
   /**
    * Adds (or overwrites) a pointer to an object to the exception.
    */
   void addPointer(String param, const Object *value);
};


#ifndef __TIMESTAMP__
 #define __TIMESTAMP__ (__DATE__ " " __TIME__)
#endif

/**
 * Defines and creates a new error descriptor.
 * You must add your parameters and throw it. e.g:
 *  MAKE_ERROR(ex, Exception::Format);
 *  ex->add("param1", "value");
 *  throw ex;
 */
#define MAKE_ERROR(name, type) \
      type *name = new type (null, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)

/**
 * Defines and creates a new error descriptor containing another.
 * You must add your parameters and throw it. e.g:
 *  RE_MAKE_ERROR(ex, Exception::Format, ex2);
 *  ex->add("param1", "value");
 *  throw ex;
 */
#define RE_MAKE_ERROR(name, type, prev) \
      type *name = new type (prev, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)

/**
 * Creates and throws a new error descriptor. e.g:
 *  THROW_ERROR(ex, Exception::Format);
 */
#define THROW_ERROR(type) \
      throw new type (null, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)

/**
 * Creates and throws a new error descriptor containing another. e.g:
 *  RE_THROW_ERROR(ex, Exception::Format, ex2);
 */
#define RE_THROW_ERROR(type, prev) \
      throw new type (prev, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)


