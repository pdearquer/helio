/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Error reporter.
 * Report errors to the user/administrator in a safe way.
 *
 * The internal information should not be reported to the user,
 * it could give clues to attackers. Use the flag "silently" for that.
 *
 * Never report confidential information, not even silently. Personal
 * information or passwords should not appear in log files, they must
 * be stored encrypted.
 */
class Reporter : 
      public virtual Object
{
public:
   /**
    * Reports an error appropriately.
    * By now, prints it out through the console.
    * @param silently If true, it doesn't reports to the user, only to a log file.
    */
   static void report(Throwable *error, _bool silently);
};

