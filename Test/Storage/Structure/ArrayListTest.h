/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** ArrayList container tests
 * Tests the ArrayList implementation.
 */
class ArrayListTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   ArrayListTest(TestFramework *framework);


   /**
    * Container interface tests; ownership.
    */
   void container();

   /**
    * Basic operations.
    */
   void basic();

   /**
    * Redimension operations.
    */
   void redim();
};

