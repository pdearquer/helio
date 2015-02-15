/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Date and time retrieval in Unix.
 * Date and time retrieval using Unix standard functions.
 */
class UnixClock : 
      public virtual Clock
{
public:
   /**
    * Get current date and time from default clock.
    */
   virtual void get(Date *date);
   
   
   /**
    * Format the date to string.
    */
   static String format(const Date *date);

   /**
    * Gets the current number of milliseconds from 00:00:00 01/01/2000
    */
   static _uint64 getCurrentMillis();
};

