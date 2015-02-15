/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** LinkedQueue container tests.
 * Tests the LinkedQueue implementation.
 */
class LinkedQueueTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   LinkedQueueTest(TestFramework *framework);


   /**
    * Container interface tests; ownership.
    */
   void container();

   /**
    * Basic operations.
    */
   void basic();

   /**
    * Queue operations.
    */
   void queue();

   /**
    * Redimension operations.
    */
   void redim();
};

