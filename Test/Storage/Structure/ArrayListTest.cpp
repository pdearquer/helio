/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

ArrayListTest::ArrayListTest(TestFramework *framework)
{
   init(framework, "ArrayListTest");

   ADD_TEST_CASE(ArrayListTest, container);
   ADD_TEST_CASE(ArrayListTest, basic);
   ADD_TEST_CASE(ArrayListTest, redim);
}


void ArrayListTest::container()
{
   ArrayList<Integer> *list = new ArrayList<Integer>();
   list->add(new Integer(1));
   list->add(new Integer(3));
   list->add(new Integer(5));
   list->add(new Integer(7));
   
   ASSERT_EQ(list->count(), 4);
   
   list->set(1, new Integer(2));

   ArrayList<Integer> *index = new ArrayList<Integer>(false);
   
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

   ASSERT_THROW(it.next(), Error::Structure::IterationEnded);

   delete list;
}

void ArrayListTest::basic()
{
   ArrayList<Float> *list = new ArrayList<Float>();
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

   list->remove(list->get(0));
   ASSERT(list->get(0) == null);
   ASSERT_EQ(list->count(), 4);

   for(_int i = 0; i < 300; i++)
      list->push(new Float((_float)i));
   ASSERT_EQ(list->count(), 304);

   ASSERT(list->peek()->getFloat() == 299.0);
   f = list->pop();
   ASSERT(f->getFloat() == 299.0);
   delete f;
   ASSERT_EQ(list->count(), 303);
   list->push(new Float(-12.0));
   ASSERT_EQ(list->count(), 304);
   ASSERT(list->peek()->getFloat() == -12.0);

   delete list;
}

void ArrayListTest::redim()
{
   ArrayList<Float> *list = new ArrayList<Float>();

   ASSERT_EQ(list->add(new Float(1.0)), 0);
   ASSERT_EQ(list->add(new Float(2.0)), 1);
   ASSERT_EQ(list->add(new Float(3.0)), 2);
   ASSERT_EQ(list->add(new Float(4.0)), 3);
   ASSERT_EQ(list->count(), 4);

   ASSERT_THROW(list->setCount(5), Error::Structure::InvalidLength);
   ASSERT_EQ(list->count(), 4);
   list->setCount(3);
   ASSERT_EQ(list->count(), 3);
   ASSERT_EQ(list->add(new Float(5.0)), 3);
   ASSERT_EQ(list->count(), 4);

   list->erase(0, 0);
   ASSERT_EQ(list->count(), 3);
   ASSERT(list->get(0)->getFloat() == 2.0);

   list->erase(1, 2);
   ASSERT_EQ(list->count(), 1);
   ASSERT(list->get(0)->getFloat() == 2.0);

   ASSERT_EQ(list->add(new Float(2.0)), 1);
   ASSERT_EQ(list->add(new Float(3.0)), 2);
   ASSERT_EQ(list->add(new Float(4.0)), 3);
   ASSERT_EQ(list->count(), 4);

   list->erase(1, 2);
   ASSERT_EQ(list->count(), 2);
   ASSERT(list->get(0)->getFloat() == 2.0);
   ASSERT(list->get(1)->getFloat() == 4.0);

   list->clear();
   ASSERT(list->isEmpty());
   delete list;
}

} } }

