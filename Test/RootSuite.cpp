/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

RootSuite::RootSuite(TestFramework *framework)
{
   init(framework, "ROOT");

#ifdef __HELIO_TEST_SELFTEST
   add(new SelfTest(framework));
#endif

#ifdef __HELIO_TEST_STORAGE_SUITE
   addSuite(new Storage::Suite(framework));
#endif
}

}

