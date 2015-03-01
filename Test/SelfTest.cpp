/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {

SelfTest::SelfTest(TestFramework *framework)
{
   init(framework, "SelfTest");

   ADD_TEST_CASE(SelfTest, simpleAsserts);
   ADD_TEST_CASE(SelfTest, equalAsserts);
   ADD_TEST_CASE(SelfTest, excepAsserts);
   ADD_TEST_CASE(SelfTest, timing);
   //ADD_TEST_CASE_TIME(SelfTest, timing, 0);
   ADD_TEST_CASE(SelfTest, memory);
}


void SelfTest::setup()
{
   //ASSERT_EX(false, "setup");
}

void SelfTest::destroy()
{
   //ASSERT_EX(false, "destroy");
}

void SelfTest::setupTest()
{
   //ASSERT_EX(false, "setupTest");
}

void SelfTest::destroyTest()
{
   //ASSERT_EX(false, "destroyTest");
}


void SelfTest::simpleAsserts()
{
   ASSERT(2 == 3 - 1);
   ASSERT_EX(2 == 3 - 1, "That's important");

   ASSERT_NO(2 != 3 - 1);
   ASSERT_NO_EX(2 != 3 - 1, "I get " + (3 - 1) + "!");
}

void SelfTest::equalAsserts()
{
   ASSERT_EQ(2 * 2, 3 + 1);
   ASSERT_EQ_EX(2 * 2, 3 + 1, "Not so good at maths?");

   ASSERT_NO_EQ(2 * 2, 3 - 1);
   ASSERT_NO_EQ_EX(2 * 2, 3 - 1, "Not so good at maths? try " + (3 - 1));
}

void SelfTest::excepAsserts()
{
   _int a = 1;
   ASSERT_THROW(a++; THROW_ERROR(Exception::Test::TestException), Exception::Test::TestException);
   ASSERT_THROW_EX(a++; THROW_ERROR(Exception::Test::TestException), Exception::Test::TestException,
         "Remember that a is " + a);

   //THROW_ERROR(Exception::Test::TestException);
   //THROW_ERROR(Error::Test::TestError);
   //throw std::bad_alloc();
   //throw "a stone";
}

void SelfTest::timing()
{
   _int var = 0;
   for(_int i = 0; i < Integer::MAX; i++)
      var++;

   //for(;;) { }
   //ASSERT_THROW(for(;;) { }, Exception);
}

void SelfTest::memory()
{
   Object *o = new Object();
   o->toString();
   delete o;
   //delete o;
   //delete (void *) 456;
}

}

