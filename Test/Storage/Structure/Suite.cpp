/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

Suite::Suite(TestFramework *framework)
{
   init(framework, "Structure");

#ifdef __HELIO_TEST_STORAGE_STRUCTURE_DATATEST
   add(new DataTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_STRINGTEST
   add(new StringTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_FORMATTEST
   add(new FormatTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_ARRAYLISTTEST
   add(new ArrayListTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_LINKEDQUEUETEST
   add(new LinkedQueueTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_ARRAYSETTEST
   add(new ArraySetTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_HASHSETTEST
   add(new HashSetTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_HASHMAPTEST
   add(new HashMapTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_ARRAYMAPTEST
   add(new ArrayMapTest(framework));
#endif
#ifdef __HELIO_TEST_STORAGE_STRUCTURE_LINKEDLISTTEST
   add(new LinkedListTest(framework));
#endif
}

} } }

