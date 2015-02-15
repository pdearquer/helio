/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

void VerboseReporter::runStart(TestFramework *framework)
{
   PRINTLN("Starting run over " + framework->tests()->count() + " tests.");
}

void VerboseReporter::runEnd(_bool error)
{
   PRINTLN("Testing finished with result: " + (error ? "ERROR" : "OK"));
}


void VerboseReporter::testStart(TestCase *tc)
{
   PRINTLN(tc->fullName + ": Starting...");
}

void VerboseReporter::testEnd(TestCase *tc, _int millis)
{
   if(tc->error)
      PRINTLN(tc->fullName + ": finished in ERROR");
   else
      PRINTLN(tc->fullName + ": finished OK in " + millis + " millis");
}

void VerboseReporter::printEx(Exception *ex)
{
   PRINTLN(ex->dump());
}

}
