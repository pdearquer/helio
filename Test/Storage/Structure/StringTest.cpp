/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Test {
namespace Storage {
namespace Structure {

StringTest::StringTest(TestFramework *framework)
{
   init(framework, "StringTest");

   ADD_TEST_CASE(StringTest, string);
   ADD_TEST_CASE(StringTest, stringBuffer);
   ADD_TEST_CASE(StringTest, addition);
   ADD_TEST_CASE(StringTest, stringBufferEdit);
}


void StringTest::string()
{
   String s;
   ASSERT(s.length() == 0);
   ASSERT(s.isEmpty());
   ASSERT(s == "");

   s = "abca";
   ASSERT(s.length() == 4);
   ASSERT_NO(s.isEmpty());
   ASSERT(s == "abca");
   ASSERT(s == s);

   ASSERT(s.sub(0) == "abca");
   ASSERT(s.sub(1) == "a");
   ASSERT(s.sub(-2) == "ab");
   ASSERT(s.sub(1, 0) == "bca");
   ASSERT(s.sub(1, 1) == "b");
   ASSERT(s.sub(1, -1) == "bc");

   ASSERT_EQ(s.indexOf('a'), 0);
   ASSERT_EQ(s.indexOf('b'), 1);
   ASSERT_EQ(s.indexOf('c'), 2);
   ASSERT_EQ(s.indexOf('d'), -1);
   ASSERT_EQ(s.indexOf('a', 1), 3);
   ASSERT_EQ(s.indexOf('b', 1), 1);
   ASSERT_EQ(s.indexOf('b', 2), -1);

   ASSERT_EQ(s.indexOf("a"), 0);
   ASSERT_EQ(s.indexOf("ab"), 0);
   ASSERT_EQ(s.indexOf("ca"), 2);
   ASSERT_EQ(s.indexOf("cb"), -1);
   ASSERT_EQ(s.indexOf("a", 1), 3);

   ASSERT_EQ(s.lastIndexOf('a'), 3);
   ASSERT_EQ(s.lastIndexOf('a', 3), 3);
   ASSERT_EQ(s.lastIndexOf('a', 2), 0);
   ASSERT_EQ(s.lastIndexOf('d'), -1);

   ASSERT_EQ(s.lastIndexOf("a"), 3);
   ASSERT_EQ(s.lastIndexOf("ab"), 0);
   ASSERT_EQ(s.lastIndexOf("ba"), -1);
   ASSERT_EQ(s.lastIndexOf("a", 2), 0);
   ASSERT_EQ(s.lastIndexOf("abc", 1), -1);

   ASSERT(s.startsWith('a'));
   ASSERT(s.startsWith("a"));
   ASSERT(s.startsWith("ab"));
   ASSERT_NO(s.startsWith("aa"));

   ASSERT(s.endsWith('a'));
   ASSERT(s.endsWith("a"));
   ASSERT(s.endsWith("ca"));
   ASSERT_NO(s.endsWith("ab"));

   String s2 = "cba";
   ASSERT(s2 == "cba");
   ASSERT(s != s2);
   ASSERT(s < s2);
   ASSERT(s <= s2);
   ASSERT(s2 > s);
   ASSERT(s2 >= s);

   s2 = s.toUpperCase();
   ASSERT(s2 == "ABCA");
   ASSERT(s2.toLowerCase() == s);
}


void StringTest::stringBuffer()
{
   StringBuffer s;
   ASSERT(s.length() == 0);
   ASSERT(s.empty());
   ASSERT(s == "");

   s = "abca";
   ASSERT(s.length() == 4);
   ASSERT_NO(s.empty());
   ASSERT(s == "abca");
   ASSERT(s == s);

   ASSERT(s.sub(0) == "abca");
   ASSERT(s.sub(1) == "a");
   ASSERT(s.sub(-2) == "ab");
   ASSERT(s.sub(1, 0) == "bca");
   ASSERT(s.sub(1, 1) == "b");
   ASSERT(s.sub(1, -1) == "bc");

   ASSERT_EQ(s.indexOf('a'), 0);
   ASSERT_EQ(s.indexOf('b'), 1);
   ASSERT_EQ(s.indexOf('c'), 2);
   ASSERT_EQ(s.indexOf('d'), -1);
   ASSERT_EQ(s.indexOf('a', 1), 3);
   ASSERT_EQ(s.indexOf('b', 1), 1);
   ASSERT_EQ(s.indexOf('b', 2), -1);

   ASSERT_EQ(s.indexOf("a"), 0);
   ASSERT_EQ(s.indexOf("ab"), 0);
   ASSERT_EQ(s.indexOf("ca"), 2);
   ASSERT_EQ(s.indexOf("cb"), -1);
   ASSERT_EQ(s.indexOf("a", 1), 3);

   ASSERT_EQ(s.lastIndexOf('a'), 3);
   ASSERT_EQ(s.lastIndexOf('a', 3), 3);
   ASSERT_EQ(s.lastIndexOf('a', 2), 0);
   ASSERT_EQ(s.lastIndexOf('d'), -1);

   ASSERT_EQ(s.lastIndexOf("a"), 3);
   ASSERT_EQ(s.lastIndexOf("ab"), 0);
   ASSERT_EQ(s.lastIndexOf("ba"), -1);
   ASSERT_EQ(s.lastIndexOf("a", 2), 0);
   ASSERT_EQ(s.lastIndexOf("abc", 1), -1);

   ASSERT(s.startsWith('a'));
   ASSERT(s.startsWith("a"));
   ASSERT(s.startsWith("ab"));
   ASSERT_NO(s.startsWith("aa"));

   ASSERT(s.endsWith('a'));
   ASSERT(s.endsWith("a"));
   ASSERT(s.endsWith("ca"));
   ASSERT_NO(s.endsWith("ab"));

   StringBuffer s2 = "cba";
   ASSERT(s2 == "cba");
   ASSERT(s != s2);
   ASSERT(s < s2);
   ASSERT(s <= s2);
   ASSERT(s2 > s);
   ASSERT(s2 >= s);
}

void StringTest::addition()
{
   String s = "abc";
   StringBuffer sb = "xyz";

   ASSERT(s + s == "abcabc");
   ASSERT(s + sb == "abcxyz");
   ASSERT(s + "def" == "abcdef");
   ASSERT(s + "" == s);
   ASSERT("def" + s == "defabc");
   ASSERT(sb + s == "xyzabc");
   ASSERT(sb + "def" == "xyzdef");
   ASSERT("def" + sb == "defxyz");

   ASSERT(s + 123 == "abc123");
   ASSERT(-123 + s == "-123abc");
   ASSERT(sb + -123 == "xyz-123");
   ASSERT(123 + sb == "123xyz");

   ASSERT(s + false == "abcfalse");
   ASSERT(true + s == "trueabc");
   ASSERT(sb + true == "xyztrue");
   ASSERT(false + sb == "falsexyz");

   ASSERT(s + '!' == "abc!");
   ASSERT('!' + s == "!abc");
   ASSERT(sb + '!' == "xyz!");
   ASSERT('!' + sb == "!xyz");

   TEST_PRINTLN("String addition to float: " + s + -0.15);
   ASSERT(s + -0.15 == "abc-0.150");
   ASSERT(-0.15 + s == "-0.150abc");
   ASSERT(sb + -0.15 == "xyz-0.150");
   ASSERT(-0.15 + sb == "-0.150xyz");

   ASSERT(s + '=' + 123 + ", " + sb + "=" + -8585 + ", " + true == "abc=123, xyz=-8585, true");
}

void StringTest::stringBufferEdit()
{
   StringBuffer s = "Buffer to edit";

   _int pos = s.lastIndexOf('e');
   ASSERT(pos > 0);
   s.set(pos, 'E');
   ASSERT(s == "Buffer to Edit");
   s.set(pos, "EDIT");
   ASSERT(s == "Buffer to EDIT");
   s[pos] = 'e';
   ASSERT(s == "Buffer to eDIT");

   s.move(-2);
   ASSERT(s == "ffer to eDIT");
   s.erase(2, 2);
   ASSERT(s == "ff to eDIT");
   s.insert(0, "B");
   ASSERT(s == "Bff to eDIT");
   s.insert(1, 'U');
   ASSERT(s == "BUff to eDIT");
   s.insert(2, "FFER", 2);
   ASSERT(s == "BUFFER to eDIT");

   s.replace("to", "TO");
   ASSERT(s == "BUFFER TO eDIT");
   s.replace('e', 'E');
   ASSERT(s == "BUFFER TO EDIT");

   s.padRight(s.length() + 3, '*');
   ASSERT(s == "BUFFER TO EDIT***");
   s.padLeft(s.length() + 3, '*');
   ASSERT(s == "***BUFFER TO EDIT***");

   s.reverse();
   ASSERT(s == "***TIDE OT REFFUB***");

   TEST_PRINTLN("Edited buffer: " + s);
}

} } }

