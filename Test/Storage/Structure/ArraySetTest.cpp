/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

ArraySetTest::ArraySetTest(TestFramework *framework)
{
   init(framework, "ArraySetTest");

   ADD_TEST_CASE(ArraySetTest, container);
   ADD_TEST_CASE(ArraySetTest, basic);
}


void ArraySetTest::container()
{
   ArraySet<Integer> *set = new ArraySet<Integer>();
   ASSERT_EQ(set->count(), 0);

   for(_int i = 0; i < 100; i++)
      ASSERT(set->add(new Integer(i)));
   ASSERT_EQ(set->count(), 100);

   _int count = 0;
   for(Integer *i : set)
   {
      (void) i;
      count++;
   }
   ASSERT_EQ_EX(count, 100, "Elements counted when iterating the set");

   List<Integer> *list = set->asList();
   ASSERT_EQ(list->count(), 100);

   ArraySet<Integer> *set2 = new ArraySet<Integer>(false);

   for(Integer *i : list)
      ASSERT(set2->add(i));
   ASSERT_EQ(set2->count(), 100);

   delete set2;
   delete list;

   Iterator<Integer> it = set->iterate();
   ASSERT_EQ(it.next()->getInt(), 0);

   set->add(new Integer(10));

   ASSERT_THROW(it.next(), Error::Structure::IterationEnded);

   delete set;
}

void ArraySetTest::basic()
{
   ArraySet<Integer> *set = new ArraySet<Integer>();
   ASSERT_EQ(set->count(), 0);
   ASSERT(set->isEmpty());

   ASSERT_THROW(set->add(null), Error::NullObject);

   ASSERT(set->add(new Integer(1)));
   ASSERT_EQ(set->count(), 1);
   ASSERT_NO(set->add(new Integer(1)));
   ASSERT_EQ(set->count(), 1);

   for(_int i = 2; i < 100; i++)
      ASSERT(set->add(new Integer(i)));
   ASSERT_EQ(set->count(), 99);

   Integer *i = new Integer(50);
   ASSERT(set->contains(i));
   set->remove(i);
   ASSERT_NO(set->contains(i));
   ASSERT_EQ(set->count(), 98);

   i->set(49);
   ASSERT(set->contains(i));
   i->set(51);
   ASSERT(set->contains(i));
   ASSERT_NO(set->add(i));

   set->clear();
   ASSERT_EQ(set->count(), 0);
   delete set;
}

} } }

