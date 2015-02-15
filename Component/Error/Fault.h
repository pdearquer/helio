/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Fault detection support
 * Handle fault detections translating them to exceptions.
 *
 * TODO: Get rid of platform dependency.
 */
class Fault :
   public virtual Object
{
public:
   /**
    * Install the handlers in the system.
    */
   static void install();
   
   /**
    * Set or cancel an execution time out.
    * @param seconds Time in seconds or 0 to cancel previous set.
    */
   static void setTimeOut(int seconds);
};

