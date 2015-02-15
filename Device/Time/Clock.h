/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Date and time retrieval interface.
 * Interface of any device able to retrieve the date and time from a
 * hardware clock.
 */
class Clock :
      public virtual Object
{
protected:
   /**
    * Default clock devide.
    */
   static Clock *_default;
   
   
public:
   /**
    * Get current date and time from default clock.
    */
   virtual void get(Date *date) = 0;


   /**
    * Get current date and time from default clock.
    */
   static void getDefault(Date *date);

   /**
    * Gets the current number of milliseconds from 00:00:00 01/01/2000
    */
   static _uint64 getCurrentMillis();
};

