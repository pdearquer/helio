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

void TestReporter::fixtureError(TestCase *tc, Exception *ex)
{
   PRINTLN("ERROR in fixture of: " + tc->fullName);
   printEx(ex);
}

void TestReporter::testStart(TestCase *tc)
{
}

void TestReporter::testError(TestCase *tc, Exception *ex)
{
   PRINTLN("ERROR running test: " + tc->fullName);
   printEx(ex);
}

void TestReporter::testEnd(TestCase *tc, _int millis)
{
}


void TestReporter::printEx(Exception *ex)
{
   PRINTLN("   " + ex->msg() + " (" + ex->id() + ")");

   if(ex->params.containsKey("debug.file"))
   {
      StringBuffer res;
      res.add("      " + ex->params.get("debug.file"));

      if(ex->params.containsKey("debug.line"))
         res.add(':' + ex->params.get("debug.line"));

      if(ex->params.containsKey("debug.date"))
         res.add(" (" + ex->params.get("debug.date") + ")");

      PRINTLN(res);
   }

   for(_int i = 0; i < ex->params.count(); i++)
   {
      String key = ex->params.getKey(i);
      if(key != "debug.file" && key != "debug.line" && key != "debug.date")
      {
         PRINTLN("      " + key + ": " + ex->params.get(key));
      }
   }
}

}
