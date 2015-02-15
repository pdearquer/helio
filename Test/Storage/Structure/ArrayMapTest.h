/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** ArrayMap container tests.
 * Tests the ArrayMap implementation.
 */
class ArrayMapTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   ArrayMapTest(TestFramework *framework);
   
   
   /**
    * Container interface tests; ownership.
    */
   void container();

   /**
    * Basic operations.
    */
   void basic();
};

