/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** LinkedList container tests.
 * Tests the LinkedList implementation.
 */
class LinkedListTest :
      public virtual Test
{
protected:
   /**
    * Linked node implementation for testing.
    * It stores an integer number.
    */
   class TestLinkedNode : public virtual LinkedNode<TestLinkedNode>
   {
   public:
      /**
       * Integer number to identify the node.
       */
      int number;

      /**
       * Fast constructor.
       */
      TestLinkedNode(int num)
      {
         number = num;
      }
   };


public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   LinkedListTest(TestFramework *framework);


   /**
    * Container interface tests; ownership.
    */
   void container();

   /**
    * Basic node operations.
    */
   void basic();
};

