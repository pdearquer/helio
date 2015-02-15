/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */


/** Error handle helpers
 * Error reporting macros and especial handlers.
 *
 * TODO: Get rid of platform dependency.
 */
class Error : 
      public virtual Object
{
public:
   /**
    * Handle a critical error.
    * Note that a critical error occurs when something critical fails!
    * (memory, early console, corruption...), do NOT try to do "normal" things.
    */
   static void critical(const char *id, const char *file, int line, const char *date);
   
   /**
    * Warning inform.
    */
   static void warning(String id, String file, _int line, String date);
};

/* Error macros */

#ifndef __TIMESTAMP__
 #define __TIMESTAMP__ (__DATE__ " " __TIME__)
#endif

#define ERROR(id) \
      throw new ::Component::Error::Exception((String) (id), (String) __FILE__, __LINE__, (String) __TIMESTAMP__)

#define RE_ERROR(id, prev) \
      throw new ::Component::Error::Exception((String) (id), prev, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)    

#define MAKE_ERROR(id) \
      new ::Component::Error::Exception((String) (id), (String) __FILE__, __LINE__, (String) __TIMESTAMP__)
      
#define RE_MAKE_ERROR(id, prev) \
      new ::Component::Error::Exception((String) (id), prev, (String) __FILE__, __LINE__, (String) __TIMESTAMP__)
            
/*      
   Exception *ex = MAKE_ERROR("testing_error");
   ex->add("param1", "value");
   throw ex;
*/

#define WARN(id) \
      ::Component::Error::Error::warning((String) (id), (String) __FILE__, __LINE__, (String) __TIMESTAMP__)

#define CRITICAL_ERROR(id) \
      ::Component::Error::Error::critical(id, __FILE__, __LINE__, __TIMESTAMP__)


