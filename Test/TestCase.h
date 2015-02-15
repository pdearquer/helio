/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Test case descriptor
 * Keep all the information about one single test case.
 */
class TestCase :
      public virtual Object
{
public:
   /**
    * Test unit.
    */
   Test *test;

   /**
    * Test case name.
    */
   String name;
   
   /**
    * Full path name if in the selected list.
    */
   String fullName;

   /**
    * Test case function invoker.
    */
   Function<> *method;

   /**
    * Time limit in seconds or 0 for none.
    */
   _int timeSeconds;

   /**
    * This test has report any error.
    */
   _bool error;


   /**
    * Construct the test case information
    * @param name Test case name
    * @param method
    */
   TestCase(Test *test, const String &name, Function<> *method, _int time);

   /**
    * Delete the method handler.
    */
   virtual ~TestCase();
};
