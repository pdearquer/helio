/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** ArraySet container tests
 * Tests the ArraySet implementation.
 */
class ArraySetTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   ArraySetTest(TestFramework *framework);
   
   
   /**
    * Container interface tests; ownership.
    */
   void container();

   /**
    * Basic operations.
    */
   void basic();
};

