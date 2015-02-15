/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {

Suite::Suite(TestFramework *framework)
{  
   init(framework, "Storage");

#ifdef __HELIO_TEST_STORAGE_STRUCTURE_SUITE
   addSuite(new Structure::Suite(framework));
#endif
}

} }

