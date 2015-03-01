/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

ArrayMapTest::ArrayMapTest(TestFramework *framework)
{
   init(framework, "ArrayMapTest");

   ADD_TEST_CASE(ArrayMapTest, container);
   ADD_TEST_CASE(ArrayMapTest, basic);
}


void ArrayMapTest::container()
{
   ArrayMap<Integer, Float> *map = new ArrayMap<Integer, Float>();
   ASSERT_EQ(map->count(), 0);

   for(_int i = 0; i < 100; i++)
      ASSERT(map->add(new Integer(i), new Float(i)));
   ASSERT_EQ(map->count(), 100);

   _int count = 0;
   for(Integer *i : map)
   {
      (void) i;
      count++;
   }
   ASSERT_EQ_EX(count, 100, "Elements counted when iterating the map");

   List<Integer> *list = map->asList();
   ASSERT_EQ(list->count(), 100);

   ArrayMap<Integer, Float> *map2 = new ArrayMap<Integer, Float>(false);

   for(Integer *i : list)
      ASSERT(map2->add(i, map2->get(i)));
   ASSERT_EQ(map2->count(), 100);

   delete map2;
   delete list;

   Iterator<Integer> it = map->iterate();
   ASSERT_EQ(it.next()->getInt(), 0);

   map->add(new Integer(10), new Float(10));

   ASSERT_THROW(it.next(), Error::Structure::IteratorInvalidated);

   delete map;
}

void ArrayMapTest::basic()
{
   ArrayMap<String, Integer> *map = new ArrayMap<String, Integer>();
   ASSERT_EQ(map->count(), 0);
   ASSERT(map->isEmpty());

   ASSERT_THROW(map->add(null, null), Error::NullObject);

   ASSERT(map->add(new String("abc"), new Integer(1)));
   ASSERT_EQ(map->count(), 1);
   ASSERT_NO(map->add(new String("abc"), new Integer(2)));
   ASSERT_EQ(map->count(), 1);

   for(_int i = 2; i < 100; i++)
      ASSERT(map->add(new String((StringBuffer)"abc " + i), new Integer(i)));
   ASSERT_EQ(map->count(), 99);

   String *s = new String("abc 50");
   Integer *i = new Integer(50);
   ASSERT(map->contains(s));
   ASSERT(map->get(s) != null);
   ASSERT(map->get(s)->equals(i));
   map->remove(s);
   ASSERT_NO(map->contains(s));
   ASSERT_EQ(map->count(), 98);

   *s = "abc 49";
   i->set(49);
   ASSERT(map->contains(s));
   ASSERT(map->get(s) != null);
   ASSERT(map->get(s)->equals(i));
   *s = "abc 51";
   ASSERT(map->contains(s));
   ASSERT_NO(map->add(s, i));

   map->clear();
   ASSERT_EQ(map->count(), 0);
   delete map;
}

} } }

