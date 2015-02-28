/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Test report handler
 * Report all the events during a test run.
 *
 * This events sequence is:
 *
 *    runStart    (only once)
 *       fixtureError ?
 *       testStart
 *       testError ?
 *       testEnd
 *       fixtureError ?
 *    runEnd      (only once)
 *
 * Note that this class should not throw any exception, this is not
 * part of the tests but of the framework and any exception will be
 * understood as a failure in the framework (aborting the whole execution).
 *
 * The default implementation report only errors.
 */
class TestReporter :
      public virtual Object
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
    * Error found while preparing the fixture.
    */
   virtual void fixtureError(TestCase *tc, Component::Error::Throwable *ex);

   /**
    * A test case is about to be run.
    */
   virtual void testStart(TestCase *tc);
   
   /**
    * Error found while running a test case.
    */
   virtual void testError(TestCase *tc, Component::Error::Throwable *ex);

   /**
    * A test case has finished.
    * @param millis Time elapsed in milliseconds or 0 in case of error.
    */
   virtual void testEnd(TestCase *tc, _int millis);


protected:
   /**
    * Print an exception to the console.
    */
   virtual void printEx(Component::Error::Throwable *ex);
};

