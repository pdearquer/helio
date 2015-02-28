/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

DataTest::DataTest(TestFramework *framework)
{
   init(framework, "DataTest");

   ADD_TEST_CASE(DataTest, object);
   ADD_TEST_CASE(DataTest, boolean);
   ADD_TEST_CASE(DataTest, integer);
   ADD_TEST_CASE(DataTest, date);
   ADD_TEST_CASE(DataTest, floatClass);
   ADD_TEST_CASE(DataTest, character);
   ADD_TEST_CASE(DataTest, pointer);
   ADD_TEST_CASE(DataTest, function);
}


void DataTest::object()
{
   Object *obj = new Object();

   ASSERT(obj->equals(obj));

   ASSERT(obj->getClass() != "");

   ASSERT(obj->tryAs<Object>() == obj);
   ASSERT(obj->tryAs<Integer>() == null);

   ASSERT(obj->as<Object>() == obj);
   ASSERT_THROW(obj->as<Integer>(), Exception::InvalidClass);

   ASSERT(obj->is<Object>());
   ASSERT_NO(obj->is<Integer>());

   String str = obj->toString();
   ASSERT(str != "");
   TEST_PRINTLN("Object to string: " + str);

   delete obj;
}

void DataTest::boolean()
{
   Boolean b;
   ASSERT_NO(b.get());
   ASSERT_NO(b);

   b = true;
   ASSERT(b);
   ASSERT(b.toString() == "true");

   b = false;
   ASSERT_NO(b);
   ASSERT(b.toString() == "false");
   ASSERT(!b);

   ASSERT(b || true);
   ASSERT_NO(b && true);

   ASSERT(true || b);
   ASSERT_NO(true && b);

   Boolean b2 = true;
   ASSERT(b || b2);
   ASSERT_NO(b && b2);

   ASSERT_NO(b.equals(&b2));
}

void DataTest::integer()
{
   Integer i;   
   ASSERT_EQ(i.get(), 0);
   ASSERT_EQ(i, 0);

   i = 1234;
   ASSERT_EQ(i, 1234);
   ASSERT(i == 1234);
   ASSERT(1234 == i);
   ASSERT(i != 4321);
   ASSERT(4321 != i);
   ASSERT(i < 4321);
   ASSERT_NO(4321 < i);
   ASSERT_NO(i > 4321);
   ASSERT(4321 > i);
   ASSERT(i >= 1234);
   ASSERT(1234 >= i);
   ASSERT_NO(i <= 1233);
   ASSERT(1233 <= i);

   Integer i2 = i;
   ASSERT(i.equals(&i2));
   ASSERT_EQ(i.compare(&i2), 0);
   i2 = -1234;
   ASSERT_EQ(i.compare(&i2), +1);
   ASSERT_EQ(i2.compare(&i), -1);

   ASSERT_NO(i == i2);
   ASSERT(i != i2);
   ASSERT_NO(i < i2);
   ASSERT(i > i2);
   ASSERT(i >= i2);
   ASSERT_NO(i <= i2);
 
   ASSERT_NO(i == sizeof(_uint8));
   ASSERT(i != sizeof(_uint8));
   ASSERT_NO(i < sizeof(_uint8));
   ASSERT(i > sizeof(_uint8));
   ASSERT(i >= sizeof(_uint8));
   ASSERT_NO(i <= sizeof(_uint8));
 
   i = 2;
   i2 = sizeof(_uint32);
   
   ASSERT_EQ(i + i, 4);
   ASSERT_EQ(i + 2, 4);
   ASSERT_EQ(-2 + i, 0);
   ASSERT_EQ(i + sizeof(_uint16), 4);
   ASSERT_EQ(sizeof(_uint16) + i, 4);
   
   ASSERT_EQ(i2 - i, 2);
   ASSERT_EQ(i2 - 2, 2);
   ASSERT_EQ(4 - i, 2);
   ASSERT_EQ(i2 - sizeof(_uint16), 2);
   ASSERT_EQ(sizeof(_uint32) - i, 2);
   
   ASSERT_EQ(i2 * i, 8);
   ASSERT_EQ(i2 * 2, 8);
   ASSERT_EQ(4 * i, 8);
   ASSERT_EQ(i2 * sizeof(_uint16), 8);
   ASSERT_EQ(sizeof(_uint32) * i, 8);
   
   ASSERT_EQ(i2 / i, 2);
   ASSERT_EQ(i2 / 2, 2);
   ASSERT_EQ(4 / i, 2);
   ASSERT_EQ(i2 / sizeof(_uint16), 2);
   ASSERT_EQ(sizeof(_uint32) / i, 2);
   
   ASSERT_EQ(i2 % i, 0);
   ASSERT_EQ(i2 % 3, 1);
   ASSERT_EQ(5 % i, 1);
   ASSERT_EQ(i2 % sizeof(_uint16), 0);
   ASSERT_EQ(sizeof(_uint32) % i, 0);

#ifdef __HELIO_TYPE_INT_IS_STATIC
   i = Integer::MAX;
   ASSERT_THROW(i + 1, Error::Arithmetic::Overflow);
   ASSERT_THROW(1 + i, Error::Arithmetic::Overflow);
   ASSERT_THROW(i * 2, Error::Arithmetic::Overflow);
   ASSERT_THROW(2 * i, Error::Arithmetic::Overflow);
   
   i = Integer::MIN;
   ASSERT_THROW(i - 1, Error::Arithmetic::Overflow);
   ASSERT_THROW(-1 + i, Error::Arithmetic::Overflow);
   ASSERT_THROW(i * 2, Error::Arithmetic::Overflow);
   ASSERT_THROW(2 * i, Error::Arithmetic::Overflow);
   ASSERT_THROW(-i, Error::Arithmetic::Overflow);
   ASSERT_THROW(i / -1, Error::Arithmetic::Overflow);
   ASSERT_THROW(i % -1, Error::Arithmetic::Overflow);
   
   i = 10;
   ASSERT_THROW(i / 0, Error::Arithmetic::DivisionByCero);
   ASSERT_THROW(i % 0, Error::Arithmetic::ModuloByCero);
   i = 0;
   ASSERT_THROW(15 / i, Error::Arithmetic::DivisionByCero);
   ASSERT_THROW(15 % i, Error::Arithmetic::ModuloByCero);
#endif

   i = 1234;
   ASSERT(i.toString() == "1234");
   i = -4321;
   ASSERT(i.toString() == "-4321");
}

void DataTest::date()
{
   Date now;
   Date later(now.secs() + 60);

   ASSERT_NO(now == later);
   ASSERT(now == now);
   ASSERT(now != later);
   ASSERT(now < later);
   ASSERT(later > now);
   ASSERT(now <= later);
   ASSERT(later <= later);
   ASSERT(later >= now);
   ASSERT(later >= later);

   String str = now.toString();
   ASSERT(str != "");
   TEST_PRINTLN("Current date: " + str);
}

void DataTest::floatClass()
{
   Float f;
   ASSERT(f.get() == 0.0);

   Float f2 = 12.3;
   ASSERT_NO(f == f2);
   ASSERT(f == f);
   ASSERT(f2 == 12.3);
   ASSERT(12.3 == f2);
   ASSERT(f != f2);
   ASSERT(f2 != 12.4);
   ASSERT(12.4 != f2);
   ASSERT(f < f2);
   ASSERT(f2 < 12.4);
   ASSERT(-15.0 < f2);
   ASSERT_NO(f > f2);
   ASSERT(f2 > 0.5);
   ASSERT_NO(0.5 > f2);
   ASSERT_NO(f >= f2);
   ASSERT(f2 >= 12.3);
   ASSERT(12.3 >= f2);
   ASSERT(f <= f2);
   ASSERT(f <= 0.5);
   ASSERT_NO(0.5 <= f);

   ASSERT_NO(f.equals(&f2));
   ASSERT_NO_EQ(f.compare(&f2), 0);
   ASSERT_EQ(f.compare(&f2), -1);
   ASSERT_EQ(f2.compare(&f), +1);

   f = 5.2;    // f2 = 12.3;
   // Grap your calculator now...
   ASSERT(f + f2 == 17.5);
   ASSERT(f + 4.9 == 10.1);
   ASSERT(4.9 + f == 10.1);

   ASSERT(f - f2 == -7.1);
   ASSERT(f - 4.9 == 0.3);
   ASSERT(4.9 - f == -0.3);
   
   ASSERT(f * f2 == 63.96);
   ASSERT(f * 4.9 == 25.48);
   ASSERT(4.9 * f == 25.48);
   
   f = 3.0;
   ASSERT(f2 / f == 4.1);
   ASSERT(f / 1.5 == 2.0);
   ASSERT(4.5 / f == 1.5);
   
#ifdef __HELIO_TYPE_FLOAT_IS_STATIC
   ASSERT(f2 % f == 0.3);
   ASSERT(f % 1.2 == 0.6);
   ASSERT(4.3 % f == 1.3);
   
   f = Float::MAX;
   ASSERT_THROW(f + __HELIO_TYPE_FLOAT_MAX, Error::Arithmetic::Overflow);
   ASSERT_THROW(__HELIO_TYPE_FLOAT_MAX + f, Error::Arithmetic::Overflow);
   ASSERT_THROW(f * 2, Error::Arithmetic::Overflow);
   ASSERT_THROW(2 * f, Error::Arithmetic::Overflow);
   
   f = -Float::MAX;
   ASSERT_THROW(f - __HELIO_TYPE_FLOAT_MAX, Error::Arithmetic::Overflow);
   ASSERT_THROW(-__HELIO_TYPE_FLOAT_MAX + f, Error::Arithmetic::Overflow);
   ASSERT_THROW(f * 2, Error::Arithmetic::Overflow);
   ASSERT_THROW(2 * f, Error::Arithmetic::Overflow);
   
   f = 10.2;
   ASSERT_THROW(f / 0, Error::Arithmetic::Overflow);
   ASSERT_THROW(f % 0, Error::Arithmetic::Overflow);
   f = 0;
   ASSERT_THROW(15.2 / f, Error::Arithmetic::Overflow);
   ASSERT_THROW(15.2 % f, Error::Arithmetic::Overflow);
#endif

   ASSERT(f2.toString() != "12.3");
}

void DataTest::character()
{
   Character c;
   ASSERT(c.getUtf32() == 0);
   ASSERT((_uint32)c == 0);

   c = 'y';
   ASSERT(c == 'y');
   ASSERT(c != 'Y');
   ASSERT(c < 'z');
   ASSERT(c <= 'z');
   ASSERT(c > 'x');
   ASSERT(c >= 'x');

   ASSERT(c.isLowerCase());
   ASSERT_NO(c.isUpperCase());

   c = c.toUpperCase();
   ASSERT(c == 'Y');
   c = c.toLowerCase();
   ASSERT(c == 'y');

   ASSERT(c.toString() == "y");
}

void DataTest::pointer()
{
   Pointer p;
   ASSERT(p.isNull());
   ASSERT(p == null);

   Pointer p2 = p;
   ASSERT(p.equals(&p2));
   ASSERT(p.equals(&p));

   p2.move(10);
   ASSERT_EQ(p.diff(p2), 10);
   ASSERT_EQ(p2.diff(p), -10);
   p2.move(-20);
   ASSERT_EQ(p.diff(p2), -10);

   ASSERT(p < p2);
   ASSERT(p <= p2);
   ASSERT_NO(p > p2);
   ASSERT(p2 >= p2);
   ASSERT_NO(p == p2);
   ASSERT(p != p2);

   p2 = this;
   String str = p2.toString();
   ASSERT(str != "");
   TEST_PRINTLN("Pointer: " + str);
}

void DataTest::function()
{
   Function<_int, _int, _int> *fun = new StaticFunction<_int, _int, _int>(&DataTest::sum);

   ASSERT_EQ(fun->invoke(12, 8), 20);

   delete fun;

   fun = new MemberFunction<DataTest, _int, _int, _int>(this, &DataTest::mult);

   ASSERT_EQ(fun->invoke(5, -4), -20);

   delete fun;

}

_int DataTest::sum(_int a, _int b)
{
   return a + b;
}

_int DataTest::mult(_int a, _int b)
{
   return a * b;
}

} } }

