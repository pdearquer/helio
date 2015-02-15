/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** HashMap container tests.
 * Tests the HashMap implementation.
 */
class HashMapTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   HashMapTest(TestFramework *framework);
   
   
   /**
    * Container interface tests; ownership.
    */
   void container();

   /**
    * Basic operations.
    */
   void basic();
};

