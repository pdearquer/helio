/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Error reporter.
 * Report errors to the user/administrator in a safe way.
 */
class Reporter : 
      public virtual Object
{
public:
   /**
    * Reports an error appropriately.
    * By now, prints it out through the console.
    * @param silently If true reports to the user, if false to a log file.
    */
   static void report(Throwable *error, _bool silently);
};

