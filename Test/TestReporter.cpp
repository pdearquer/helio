/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

void TestReporter::runStart(TestFramework *framework)
{
}

void TestReporter::runEnd(_bool error)
{
}

void TestReporter::fixtureError(TestCase *tc, Component::Error::Throwable *ex)
{
   PRINTLN("ERROR in fixture of: " + tc->fullName);
   printEx(ex);
}

void TestReporter::testStart(TestCase *tc)
{
}

void TestReporter::testError(TestCase *tc, Component::Error::Throwable *ex)
{
   PRINTLN("ERROR running test: " + tc->fullName);
   printEx(ex);
}

void TestReporter::testEnd(TestCase *tc, _int millis)
{
}


void TestReporter::printEx(Component::Error::Throwable *ex)
{
   PRINTLN(ex->getClass() + ": " + ex->msg());

   _int pars = 0;
   const Table<String, String> *params = ex->params();
   if(params->contains("debug.file"))
   {
      PRINT(" from " + params->get("debug.file"));
      pars++;
      
      if(params->contains("debug.line"))
      {
         PRINT(':' + params->get("debug.line"));
         pars++;
      }
      
      if(params->contains("debug.date"))
      {
         PRINT(" (" + params->get("debug.date") + ")");
         pars++;
      }

      PRINT("\n");
   }

   if(params->count() > pars)
   {
      for(_int i = 0; i < params->count(); i++)
      {
         String key = params->getKey(i);
         if(key != "debug.file" && key != "debug.line" && key != "debug.date")
         {
            PRINTLN("   " + key + ": " + params->get(key));
         }
      }
   }
}

}

