/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

LinkedQueueTest::LinkedQueueTest(TestFramework *framework)
{
   init(framework, "LinkedQueueTest");

   ADD_TEST_CASE(LinkedQueueTest, container);
   ADD_TEST_CASE(LinkedQueueTest, basic);
   ADD_TEST_CASE(LinkedQueueTest, queue);
   ADD_TEST_CASE(LinkedQueueTest, redim);
}


void LinkedQueueTest::container()
{
   LinkedQueue<Integer> *list = new LinkedQueue<Integer>();
   list->add(new Integer(1));
   list->add(new Integer(3));
   list->add(new Integer(5));
   list->add(new Integer(7));

   ASSERT_EQ(list->count(), 4);

   list->set(1, new Integer(2));

   LinkedQueue<Integer> *index = new LinkedQueue<Integer>(false);

   for(Integer *i : list)
      index->add(i);

   ASSERT_EQ(index->count(), 4);

   Integer *i = new Integer(5);
   ASSERT(list->contains(i));
   ASSERT(index->contains(i));
   delete index;

   Iterator<Integer> it = list->iterate();
   ASSERT_EQ(it.next()->getInt(), 1);

   list->remove(i);
   ASSERT_NO(list->contains(i));
   delete i;

   ASSERT_THROW(it.next(), Error::Structure::IteratorInvalidated);

   delete list;
}

void LinkedQueueTest::basic()
{
   LinkedQueue<Float> *list = new LinkedQueue<Float>();
   ASSERT_EQ(list->count(), 0);
   ASSERT(list->isEmpty());

   ASSERT_EQ(list->add(new Float(1.0)), 0);
   ASSERT_EQ(list->add(new Float(-2.0)), 1);
   ASSERT_EQ(list->add(new Float(3.0)), 2);
   ASSERT_EQ(list->add(new Float(4.0)), 3);
   ASSERT_EQ(list->count(), 4);

   ASSERT_THROW(list->get(-1), Error::Structure::OutOfBounds);
   ASSERT_THROW(list->get(4), Error::Structure::OutOfBounds);
   ASSERT_THROW(list->set(-1, null), Error::Structure::OutOfBounds);
   ASSERT_THROW(list->set(4, null), Error::Structure::OutOfBounds);

   ASSERT(list->get(1)->getFloat() == -2.0);
   list->set(1, new Float(2.0));
   ASSERT(list->get(1)->getFloat() == 2.0);
   ASSERT_EQ(list->count(), 4);

   Float *f = new Float(3.0);
   ASSERT(list->contains(f));
   ASSERT_EQ(list->indexOf(f), 2);
   ASSERT_EQ(list->indexOf(f, 2), 2);
   ASSERT_EQ(list->indexOf(f, 3), -1);
   ASSERT_THROW(list->indexOf(f, 4), Error::Structure::OutOfBounds);

   list->remove(f);
   ASSERT_NO(list->contains(f));
   ASSERT_EQ(list->indexOf(f), -1);
   ASSERT(list->get(2) == null);
   ASSERT(list->get(3)->getFloat() == 4.0);
   ASSERT_EQ(list->count(), 4);
   delete f;

   list->remove(list->get(3));
   ASSERT(list->get(3) == null);
   ASSERT_EQ(list->count(), 4);

   delete list;
}

void LinkedQueueTest::queue()
{
   LinkedQueue<Integer> *list = new LinkedQueue<Integer>();

   list->enqueue(new Integer(0));
   ASSERT_EQ(list->count(), 1);
   ASSERT_EQ(list->front()->getInt(), 0);
   ASSERT_EQ(list->back()->getInt(), 0);

   list->enqueue(new Integer(1));
   ASSERT_EQ(list->count(), 2);
   ASSERT_EQ(list->front()->getInt(), 0);
   ASSERT_EQ(list->back()->getInt(), 1);

   for(_int i = 2; i < 200; i++)
      list->enqueue(new Integer(i));

   ASSERT_EQ(list->count(), 200);
   ASSERT_EQ(list->front()->getInt(), 0);
   ASSERT_EQ(list->back()->getInt(), 199);

   Integer *el = list->dequeue();
   ASSERT_EQ(el->getInt(), 0);
   ASSERT_EQ(list->front()->getInt(), 1);
   ASSERT_EQ(list->back()->getInt(), 199);
   ASSERT_EQ(list->count(), 199);
   delete el;

   el = list->dequeueBack();
   ASSERT_EQ(el->getInt(), 199);
   ASSERT_EQ(list->front()->getInt(), 1);
   ASSERT_EQ(list->back()->getInt(), 198);
   ASSERT_EQ(list->count(), 198);
   delete el;

   for(_int i = 0; i < 198; i++)
   {
      el = list->dequeue();
      ASSERT_EQ(el->getInt(), i + 1);
      delete el;
   }

   ASSERT(list->isEmpty());
   delete list;
}

void LinkedQueueTest::redim()
{
   LinkedQueue<Integer> *list = new LinkedQueue<Integer>();

   ASSERT_EQ(list->add(new Integer(1)), 0);
   ASSERT_EQ(list->add(new Integer(2)), 1);
   ASSERT_EQ(list->add(new Integer(3)), 2);
   ASSERT_EQ(list->add(new Integer(4)), 3);
   ASSERT_EQ(list->count(), 4);

   for(_int i = 5; i <= 200; i++)
      list->enqueue(new Integer(i));

   ASSERT_EQ(list->count(), 200);

   ASSERT_THROW(list->setCount(201), Error::Structure::InvalidLength);
   ASSERT_EQ(list->count(), 200);
   list->setCount(160);
   ASSERT_EQ(list->count(), 160);
   ASSERT_EQ(list->add(new Integer(-1)), 160);
   ASSERT_EQ(list->count(), 161);

   list->erase(0, 0);
   ASSERT_EQ(list->count(), 160);
   ASSERT_EQ(list->get(0)->getInt(), 2);

   list->erase(1, 2);
   ASSERT_EQ(list->count(), 158);
   ASSERT_EQ(list->get(0)->getInt(), 2);
   ASSERT_EQ(list->get(1)->getInt(), 5);

   list->erase(101, 150);
   ASSERT_EQ(list->count(), 108);
   ASSERT_EQ(list->get(0)->getInt(), 2);
   ASSERT_EQ(list->get(100)->getInt(), 104);
   ASSERT_EQ(list->get(101)->getInt(), 155);
   ASSERT_EQ(list->get(106)->getInt(), 160);
   ASSERT_EQ(list->get(107)->getInt(), -1);

   list->clear();
   ASSERT(list->isEmpty());
   delete list;
}

} } }

