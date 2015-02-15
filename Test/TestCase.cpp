/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

TestCase::TestCase(Test *test, const String &name, Function<> *method, _int time)
{
   this->test = test;
   this->name = name;
   this->method = method;
   timeSeconds = time;
   error = false;
}

TestCase::~TestCase()
{
   delete method;
}

}
