/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Test suite base
 * Group up a list of tests or other suites.
 *
 * To create a new suite inheritate from this class and
 * build the list in you constructor.
 */
class TestSuite :
      public virtual Object
{
protected:
   /**
    * Framework reference.
    */
   TestFramework *_framework;
   
   /**
    * Suite name.
    */
   String _name;
   
   /**
    * Suites list.
    */
   ArrayList<TestSuite> *_suites;

   /**
    * Tests list.
    */
   ArrayList<Test> *_tests;


   /**
    * Protected constructor to inherit.
    * Add the tests and suites in your constructor implementation.
    * Remember to call init() first thing.
    */
   TestSuite();
   
   /**
    * Setup the suite.
    * @param framework Test framework reference
    * @param name Suite name
    */
   void init(TestFramework *framework, const String &name);

public:

   /**
    * Delete all the test and suites on this suite.
    */
   virtual ~TestSuite();


   /**
    * Add a test to the suite.
    */
   void add(Test *test);

   /**
    * Add a suite to this suite.
    * @param suite
    */
   void addSuite(TestSuite *suite);


   /**
    * Returns the name of this test suite.
    */
   String name();

   /**
    * Returns the test suites list.
    */
   ArrayList<TestSuite> *testSuites();

   /**
    * Returns the test units list.
    */
   ArrayList<Test> *tests();


   /**
    * Append the selected test cases contained in this suite to the list.
    * @param tests List of TestCase elements.
    * @param path Full name to this suite ending with ".".
    * @param filter Filtering string:
    *    "*" or "" means add the whole suite
    *    "MySuite."... adds MySuite continuing the filtering proccess
    *    "MyTest" adds all the cases of MyTest 
    *    "MyTest.myCase" adds only the myCase case of MyTest
    * If the filtering pattern is not found an exceptions arises.
    */
   void appendTests(ArrayList<TestCase> *tests, const String &path, const String &filter);
   
protected:
   /**
    * Append all the test cases contained in this suite to the list.
    * @param tests List of TestCase elements.
    * @param path Full name to this suite ending with ".".
    */
   void appendAll(ArrayList<TestCase> *tests, const String &path);

   /**
    * Append the selected test cases contained in one test to the list.
    * @param tests List of TestCase elements.
    * @param path Full name to the test ending with ".".
    * @param test Test unit to add.
    * @param filter Filtering string:
    *    "*" or "" means add the whole suite
    *    "MySuite."... adds MySuite continuing the filtering proccess
    *    "MyTest" adds all the cases of MyTest
    *    "MyTest.myCase" adds only the myCase case of MyTest
    * If the filtering pattern is not found an exceptions arises.
    */
   void appendTest(ArrayList<TestCase> *tests, const String &path, Test *test, const String &filter);

   /**
    * Append all the test cases contained in one test to the list.
    * @param tests List of TestCase elements.
    * @param path Full name to this suite ending with ".".
    * @param test Test unit to add.
    */
   void appendAllTest(ArrayList<TestCase> *tests, const String &path, Test *test);
};

