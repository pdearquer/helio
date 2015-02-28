/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

LinkedListTest::LinkedListTest(TestFramework *framework)
{
   init(framework, "LinkedListTest");

   ADD_TEST_CASE(LinkedListTest, container);
   ADD_TEST_CASE(LinkedListTest, basic);
}


void LinkedListTest::container()
{
   LinkedList<TestLinkedNode> *list = new LinkedList<TestLinkedNode>();

   ASSERT(list->isEmpty());
   ASSERT_EQ(list->count(), 0);

   list->enqueue(new TestLinkedNode(1));
   list->enqueue(new TestLinkedNode(2));
   list->enqueue(new TestLinkedNode(3));
   list->enqueue(new TestLinkedNode(4));

   ASSERT_NO(list->isEmpty());
   ASSERT_EQ(list->count(), 4);
   ASSERT_EQ(list->countReverse(), 4);
   ASSERT_EQ(list->front()->number, 1);
   ASSERT_EQ(list->back()->number, 4);

   list->enqueue_front(new TestLinkedNode(0));
   ASSERT_EQ(list->count(), 5);
   ASSERT_EQ(list->countReverse(), 5);
   ASSERT_EQ(list->front()->number, 0);

   _int count = 0;
   for(TestLinkedNode *node : list)
   {
      ASSERT_EQ(node->number, count);
      count++;
   }

   TestLinkedNode *node = list->dequeue();
   ASSERT_EQ(node->number, 0);
   ASSERT_EQ(list->count(), 4);
   ASSERT_EQ(list->countReverse(), 4);
   delete node;

   Iterator<TestLinkedNode> it = list->iterate();
   ASSERT_EQ(it.next()->number, 1);

   node = list->dequeue_back();
   ASSERT_EQ(node->number, 4);
   ASSERT_EQ(list->count(), 3);
   ASSERT_EQ(list->countReverse(), 3);
   delete node;

   ASSERT_THROW(it.next(), Error::Structure::IterationEnded);

   delete list;
}

void LinkedListTest::basic()
{
   LinkedList<TestLinkedNode> *list = new LinkedList<TestLinkedNode>();

   for(_int count = 0; count < 10; count++)
      list->enqueue(new TestLinkedNode(count));

   ASSERT_EQ(list->count(), 10);
   ASSERT_EQ(list->countReverse(), 10);

   TestLinkedNode *node = list->first();
   _int count = 0;
   while(node != null)
   {
      ASSERT_EQ(node->number, count);
      if(count == 4)
         node->removePrev();

      count++;
      node = node->next();
   }

   ASSERT_EQ(list->count(), 9);
   ASSERT_EQ(list->countReverse(), 9);

   ASSERT_EQ(list->front()->number, 0);

   list->front()->swap(list->back());

   ASSERT_EQ(list->front()->number, 9);
   ASSERT_EQ(list->back()->number, 0);
   ASSERT_EQ(list->count(), 9);
   ASSERT_EQ(list->countReverse(), 9);

   node = list->first();
   ASSERT(node != null);
   while(node->number != 2)
   {
      node = node->next();
      ASSERT(node != null);
   }

   node->insertAfter(new TestLinkedNode(3));

   ASSERT_EQ(node->next()->number, 3);
   ASSERT_EQ(node->next()->next()->number, 4);
   ASSERT_EQ(list->count(), 10);
   ASSERT_EQ(list->countReverse(), 10);

   TestLinkedNode *node2 = node->next()->next();
   node->removeNext();

   ASSERT_EQ(node2->number, 4);
   ASSERT(node->next() == node2);
   ASSERT_EQ(list->count(), 9);
   ASSERT_EQ(list->countReverse(), 9);

   node2->insertBefore(new TestLinkedNode(3));

   ASSERT_EQ(node->next()->number, 3);
   ASSERT_EQ(node->next()->next()->number, 4);
   ASSERT(node->next() == node2->prev());
   ASSERT_EQ(list->count(), 10);
   ASSERT_EQ(list->countReverse(), 10);

   node = node2->prev();
   node2->swapWithNext();

   ASSERT_EQ(node->next()->number, 5);
   ASSERT_EQ(node2->prev()->number, 5);
   ASSERT(node->next() == node2->prev());
   ASSERT_EQ(list->count(), 10);
   ASSERT_EQ(list->countReverse(), 10);

   node2->swapWithPrev();

   ASSERT(node->next() == node2);
   ASSERT_EQ(node2->next()->number, 5);
   ASSERT_EQ(list->count(), 10);
   ASSERT_EQ(list->countReverse(), 10);

   delete list;
}

} } }

