/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Framework tests
 * Tests that ensures that the framework works properly.
 */
class SelfTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   SelfTest(TestFramework *framework);

   /**
    * Prepare the fixture to run one test case.
    */
   virtual void setup();

   /**
    * Clean the fixture.
    * Make sure you clean it properly.
    */
   virtual void destroy();

   /**
    * Prepare the fixture for the whole test.
    */
   virtual void setupTest();

   /**
    * Clean the fixture of the whole test.
    * Make sure you clean it properly.
    */
   virtual void destroyTest();


   /**
    * Tests a simple assert.
    */
   void simpleAsserts();

   /**
    * Tests equal asserts.
    */
   void equalAsserts();

   /**
    * Tests exception asserts.
    */
   void excepAsserts();

   /**
    * Tests time measure and limits.
    */
   void timing();

   /**
    * Tests the memory protections.
    */
   void memory();
};

