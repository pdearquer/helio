/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

TestSuite::TestSuite()
{
   _suites = new ArrayList<TestSuite>();
   _tests = new ArrayList<Test>();
}

void TestSuite::init(TestFramework *framework, const String &name)
{
   _framework = framework;
   _name = name;
}

TestSuite::~TestSuite()
{
   delete _suites;
   delete _tests;
}


void TestSuite::add(Test *test)
{
   // Check that name is not repeated
   for(_int i = 0; i < _tests->count(); i++)
   {
      Test *t = _tests->get(i);
      if(t->name() == test->name())
      {
         Error *ex = MAKE_ERROR(Error::Test::Duplicated);
         ex->add("name", test->name());
         throw ex;
      }
   }

   for(_int i = 0; i < _suites->count(); i++)
   {
      TestSuite *ts = _suites->get(i);
      if(ts->name() == test->name())
      {
         Error *ex = MAKE_ERROR(Error::Test::Duplicated);
         ex->add("name", test->name());
         throw ex;
      }
   }

   _tests->add(test);
}

void TestSuite::addSuite(TestSuite *suite)
{
   // Check that name is not repeated
   for(_int i = 0; i < _tests->count(); i++)
   {
      Test *t = _tests->get(i);
      if(t->name() == suite->name())
      {
         Error *ex = MAKE_ERROR(Error::Test::Duplicated);
         ex->add("name", suite->name());
         throw ex;
      }
   }

   for(_int i = 0; i < _suites->count(); i++)
   {
      TestSuite *ts = _suites->get(i);
      if(ts->name() == suite->name())
      {
         Error *ex = MAKE_ERROR(Error::Test::Duplicated);
         ex->add("name", suite->name());
         throw ex;
      }
   }

   _suites->add(suite);
}


String TestSuite::name()
{
   return _name;
}

ArrayList<TestSuite> *TestSuite::testSuites()
{
   return _suites;
}

ArrayList<Test> *TestSuite::tests()
{
   return _tests;
}


void TestSuite::appendTests(ArrayList<TestCase> *tests, const String &path, const String &filter)
{
   if(filter == "" || filter == "*")
   {
      appendAll(tests, path);
   }
   else
   {
      _int entity_len = filter.indexOf('.', 0);
      String entity;
      String next_filter;
      if(entity_len < 0)
      {
         entity = filter;
         next_filter = "";
      }
      else if(entity_len == 0)
      {
         Exception *ex = MAKE_ERROR(Exception::Test::IllegalFilter);
         ex->add("filter", filter);
         throw ex;
      }
      else
      {
         entity = filter.sub(entity_len);
         next_filter = filter.sub(entity_len + 1, 0);
      }

      for(_int i = 0; i < _tests->count(); i++)
      {
         Test *t = _tests->get(i);
         if(t->name() == entity)
         {
            appendTest(tests, path + t->name() + ".", t, next_filter);
            return;
         }
      }

      for(_int i = 0; i < _suites->count(); i++)
      {
         TestSuite *ts = _suites->get(i);
         if(ts->name() == entity)
         {
            ts->appendTests(tests, path + ts->name() + ".", next_filter);
            return;
         }
      }

      Exception *ex = MAKE_ERROR(Exception::Test::IllegalFilter);
      ex->add("filter", filter);
      throw ex;
   }
}

void TestSuite::appendAll(ArrayList<TestCase> *tests, const String &path)
{
   for(_int i = 0; i < _tests->count(); i++)
   {
      Test *t = _tests->get(i);
      appendAllTest(tests, path + t->name() + ".", t);
   }

   for(_int i = 0; i < _suites->count(); i++)
   {
      TestSuite *ts = _suites->get(i);
      String suite_path = path + ts->name() + ".";
      ts->appendAll(tests, suite_path);
   }
}

void TestSuite::appendTest(ArrayList<TestCase> *tests, const String &path, Test *test, const String &filter)
{
   if(filter == "" || filter == "*")
   {
      appendAllTest(tests, path, test);
   }
   else
   {
      if(filter.indexOf('.', 0) >= 0)
      {
         Exception *ex = MAKE_ERROR(Exception::Test::IllegalFilter);
         ex->add("filter", filter);
         throw ex;
      }

      ArrayList<TestCase> *cases = test->testCases();
      for(_int j = 0; j < cases->count(); j++)
      {
         TestCase *tc = cases->get(j);
         if(tc->name == filter)
         {
            tc->fullName = path + tc->name;
            tests->add(tc);
            return;
         }
      }

      Exception *ex = MAKE_ERROR(Exception::Test::IllegalFilter);
      ex->add("filter", filter);
      throw ex;
   }
}

void TestSuite::appendAllTest(ArrayList<TestCase> *tests, const String &path, Test *test)
{
   ArrayList<TestCase> *cases = test->testCases();
   for(_int j = 0; j < cases->count(); j++)
   {
      TestCase *tc = cases->get(j);
      tc->fullName = path + tc->name;
      tests->add(tc);
   }
}

}

