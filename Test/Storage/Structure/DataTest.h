/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Data package tests
 * Tests all the Storage.Structure.Data package, except the String.
 */
class DataTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   DataTest(TestFramework *framework);


   /**
    * Tests the Object class.
    */
   void object();
   
   /**
    * Tests the Boolean class.
    */
   void boolean();
   
   /**
    * Tests the Integer class.
    */
   void integer();

   /**
    * Tests the Date class.
    */
   void date();

   /**
    * Tests the Float class.
    */
   void floatClass();

   /**
    * Tests the Character class.
    */
   void character();

   /**
    * Tests the Pointer class.
    */
   void pointer();

   /**
    * Tests the Function classes.
    */
   void function();

private:
   /**
    * Trivial static function for testing.
    */
   static _int sum(_int a, _int b);

   /**
    * Trivial member function for testing.
    */
   _int mult(_int a, _int b);
};

