/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Verbose reports generator
 * Generate detailed reports of the test runs.
 */
class VerboseReporter :
      public virtual TestReporter
{
public:
   /**
    * A set of test are about to be processed.
    */
   virtual void runStart(TestFramework *framework);

   /**
    * All the tests have been processed.
    */
   virtual void runEnd(_bool error);


   /**
    * A test case is about to be run.
    */
   virtual void testStart(TestCase *tc);

   /**
    * A test case has finished.
    * @param millis Time elapsed in milliseconds or 0 in case of error.
    */
   virtual void testEnd(TestCase *tc, _int millis);


protected:
   /**
    * Print an exception to the console.
    */
   virtual void printEx(Exception *ex);
};

