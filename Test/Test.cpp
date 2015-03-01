/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

const_int Test::DEFAULT_TIMEOUT;

Test::Test()
{
   _cases = new ArrayList<TestCase>();
   _setupOk = false;
}

void Test::init(TestFramework *framework, const String &name)
{
   _framework = framework;
   _name = name;
}

Test::~Test()
{
   delete _cases;
}


void Test::add(const String &name, Function<> *method)
{
   add(name, method, DEFAULT_TIMEOUT);
}

void Test::add(const String &name, Function<> *method, _int seconds)
{
   // Check that name is not repeated
   for(_int i = 0; i < _cases->count(); i++)
   {
      TestCase *tc = _cases->get(i);
      if(tc->name == name)
      {
         MAKE_ERROR(ex, Error::Test::Duplicated);
         ex->add("name", name);
         throw ex;
      }
   }

   _cases->add(new TestCase(this, name, method, seconds));
}

_bool Test::verbose()
{
   return _framework->verbose();
}


void Test::setup()
{
   // Nothing is done by default.
}

void Test::destroy()
{
   // Nothing is done by default.
}

void Test::setupTest()
{
   // Nothing is done by default.
}

void Test::destroyTest()
{
   // Nothing is done by default.
}


String Test::name()
{
   return _name;
}

ArrayList<TestCase> *Test::testCases()
{
   return _cases;
}

void Test::setupTestOnce()
{
   if(!_setupOk)
   {
      setupTest();
      _setupOk = true;
   }
}

void Test::destroyTestOnce()
{
   if(_setupOk)
   {
      destroyTest();
      _setupOk = false;
   }
}

}

