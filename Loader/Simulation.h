/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Runtime environment within other operative systems
 * Uses an static object to run initial tasks required before any
 * other piece of code.
 * Do NOT use static objects in any other part of the system.
 *
 * TODO: Implement main() and collect components included in compilation.
 */
class Simulation : 
      public virtual Object
{
private:
   /**
    * Static object to ensure initial tasks are done
    */
   static Simulation _init;
   
   
public:
   /**
    * Set or cancel an execution time out.
    * @param seconds Time in seconds or 0 to cancel previous set.
    */
   static void setTimeOut(int seconds);
   
private:
   /**
    * Preps the runtime environment.
    */
   Simulation();
   
   /**
    * Install the fault handlers.
    */
   void installFaults();
};

