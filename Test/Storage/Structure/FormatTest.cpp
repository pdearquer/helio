/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

FormatTest::FormatTest(TestFramework *framework)
{
   init(framework, "FormatTest");

   ADD_TEST_CASE(FormatTest, boolean);
   ADD_TEST_CASE(FormatTest, binary);
   ADD_TEST_CASE(FormatTest, integer);
   ADD_TEST_CASE(FormatTest, floatClass);
   ADD_TEST_CASE(FormatTest, character);
   ADD_TEST_CASE(FormatTest, pointer);
}


void FormatTest::boolean()
{
   Format *fmt = Format::def();

   _bool b = true;
   ASSERT(fmt->toString(b) == "true");
   b = false;
   ASSERT(fmt->toString(b) == "false");
   
   ASSERT(fmt->toBool("true"));
   ASSERT(fmt->toBool("1"));
   ASSERT_NO(fmt->toBool("false"));
   ASSERT_NO(fmt->toBool("0"));
   
   ASSERT_THROW(fmt->toBool(""));
   ASSERT_THROW(fmt->toBool("2"));
   ASSERT_THROW(fmt->toBool("bla"));
}

void FormatTest::binary()
{
   Format *fmt = Format::def();
   
   __uint64 u = 123456789ULL;
   ASSERT(fmt->toString(u) == "123456789");
   ASSERT(fmt->toUInt64("123456789") == u);
   ASSERT(fmt->toUInt64("+123456789") == u);
   ASSERT_THROW(fmt->toUInt64(""));
   ASSERT_THROW(fmt->toUInt64("-123456789"));
   ASSERT_THROW(fmt->toUInt64("1234.56789"));
   ASSERT_THROW(fmt->toUInt64("1234567890000000000000"));
   u = 0xFEDCBA987654321ULL;
   ASSERT(fmt->toString(u, 16) == "FEDCBA987654321");
   u = __HELIO_TYPE_UINT64_MAX;
   String str = fmt->toString(u);
   TEST_PRINTLN("UINT64_MAX: " + str);
   ASSERT(fmt->toUInt64(str) == u);
   
   __sint64 s = -123456789ULL;
   ASSERT(fmt->toString(s) == "-123456789");
   ASSERT(fmt->toSInt64("-123456789") == s);
   ASSERT(fmt->toSInt64("+123456789") == -s);
   ASSERT_THROW(fmt->toSInt64(""));
   ASSERT_THROW(fmt->toSInt64("-+123456789"));
   ASSERT_THROW(fmt->toSInt64("1234.56789"));
   ASSERT_THROW(fmt->toSInt64("-1234567890000000000000"));
   ASSERT_THROW(fmt->toSInt64("-" + str));
   s = __HELIO_TYPE_SINT64_MIN;
   str = fmt->toString(s);
   TEST_PRINTLN("SINT64_MIN: " + str);
   ASSERT(fmt->toSInt64(str) == s);

   u = __HELIO_TYPE_UINT32_MAX;
   str = fmt->toString(u);
   TEST_PRINTLN("UINT32_MAX: " + str);   
   s = __HELIO_TYPE_SINT32_MIN;
   str = fmt->toString(s);
   TEST_PRINTLN("SINT32_MIN: " + str);
}

void FormatTest::integer()
{
   Format *fmt = Format::def();
   
   _int i = 654;
   ASSERT(fmt->toString(i) == "654");
   ASSERT(fmt->toString(-i) == "-654");
   ASSERT(fmt->toInt("654") == i);
   ASSERT(fmt->toInt("-654") == -i);
   ASSERT_THROW(fmt->toInt(""));
   ASSERT_THROW(fmt->toInt("+"));
   ASSERT_THROW(fmt->toInt("-"));
   ASSERT_THROW(fmt->toInt("+a"));
   ASSERT_THROW(fmt->toInt("1234567890000000000000"));
   ASSERT_THROW(fmt->toInt("-1234567890000000000000"));
   
   i = Integer::MAX;
   String str = fmt->toString(i);
   ASSERT(fmt->toInt(str) == i);
   i = Integer::MIN;
   str = fmt->toString(i);
   ASSERT(fmt->toInt(str) == i);
}

void FormatTest::floatClass()
{
   Format *fmt = Format::def();
   
   // Notat that the default precision is 3
   _float f = 123.653;
   ASSERT(fmt->toString(f) == "123.653");
   ASSERT(fmt->toString(-f) == "-123.653");
   ASSERT(fmt->toFloat("123.653") == f);
   ASSERT(fmt->toFloat("-123.653") == -f);
   
   f = 0.002;
   ASSERT(fmt->toString(f) == "0.002");
   ASSERT(fmt->toString(-f) == "-0.002");
   ASSERT(fmt->toFloat("0.002") == f);
   ASSERT(fmt->toFloat("-0.002") == -f);
   
   ASSERT_THROW(fmt->toFloat(""));
   ASSERT_THROW(fmt->toFloat("."));
   ASSERT_THROW(fmt->toFloat("+"));
   ASSERT_THROW(fmt->toFloat("+."));
   ASSERT_THROW(fmt->toFloat(".1"));
   ASSERT(fmt->toFloat("0.") == 0.0);
   ASSERT_THROW(fmt->toFloat("0.+1"));
   ASSERT_THROW(fmt->toFloat("0.-"));
}

void FormatTest::character()
{
   Format *fmt = Format::def();

   _char c = 'A';
   ASSERT(fmt->toChar("A") == c);
   ASSERT(fmt->toString(c) == "A");
   
   ASSERT_THROW(fmt->toChar(""));
   ASSERT_THROW(fmt->toChar("aa"));
}

void FormatTest::pointer()
{
   Format *fmt = Format::def();

   _pointer p = null;
   String str = fmt->toString(p);
   ASSERT(fmt->toPointer(str) == p);
   ASSERT(fmt->toPointer("0x0") == p);

   p = this;
   str = fmt->toString(p);
   ASSERT(fmt->toPointer(str) == p);
   
   ASSERT_THROW(fmt->toPointer(""));
   ASSERT_THROW(fmt->toPointer("0"));
}

} } }

