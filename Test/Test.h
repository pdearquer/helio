/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Test unit base
 * Group of test cases with common fixtures.
 *
 * Add all the methods that run test cases in the constructor.
 * Do NOT assume any order in the execution of the tests.
 *
 * Fixtures are common resources shared among a some test cases.
 * These resources can be created in setup() and must be destroyed
 * in destroy() for every test case. It is important that one test
 * do not affect others. Note that the fixtures do not run in a memory
 * safe environment because the resources allocated have to be available
 * for the test cases.
 *
 * See ASSERT macros at the end of this file.
 *
 * TODO: Add float numbers support.
 */
class Test :
      public virtual Object
{
protected:
   /**
    * Default time limit for every test case execution.
    */
   static_const_int DEFAULT_TIMEOUT = 5;


   /**
    * Framework reference.
    */
   TestFramework *_framework;

   /**
    * Test unit name.
    */
   String _name;
   
   /**
    * Test cases list. See TestCase.
    */
   ArrayList<TestCase> *_cases;
   
   /**
    * Flag to know if the setup and destroy have already run.
    */
   _bool _setupOk;


   /**
    * Protected constructor to inherit.
    * Add the test cases in your constructor implementation.
    * Remember to call init() first thing.
    */
   Test();
   
   /**
    * Setup the test.
    * @param framework Test framework reference
    * @param name Test unit name
    */
   void init(TestFramework *framework, const String &name);
   
public:

   /**
    * Test cases list destroy.
    */
   virtual ~Test();


   /**
    * Add a test case to this unit.
    * See macro ADD_TEST_CASE().
    * @param name Unique (along the unit) test name
    * @param method to invoke when running the test.
    *    The prototype must be like:
    *       public: void myTestCase();
    */
   void add(const String &name, Function<> *method);

   /**
    * Add a test case to this unit.
    * See macro ADD_TEST_CASE_TIME().
    * @param name Unique (along the unit) test name
    * @param method to invoke when running the test.
    *    The prototype must be like:
    *       public: void myTestCase();
    * @param seconds Time limit in seconds or 0 for none.
    */
   void add(const String &name, Function<> *method, _int seconds);

   /**
    * Says if running in verbose mode. Dump useful information for the user wants to check it.
    * Use the TEST_PRINTLN() macro for easy.
    */
   _bool verbose();


   /**
    * Prepare the fixture to run one test case.
    */
   virtual void setup();

   /**
    * Clean the fixture.
    * Make sure you clean it properly.
    */
   virtual void destroy();

   /**
    * Prepare the fixture for the whole test.
    */
   virtual void setupTest();

   /**
    * Clean the fixture of the whole test.
    * Make sure you clean it properly.
    */
   virtual void destroyTest();


   /**
    * Returns the name of this test unit.
    */
   String name();

   /**
    * Returns the test cases list.
    */
   ArrayList<TestCase> *testCases();

   /**
    * Run the test setup only if it has not been done.
    */
   void setupTestOnce();

   /**
    * Run the test destroy only if it has not been done.
    */
   void destroyTestOnce();
};


/**
 * Test case adding helper. Use as:
 *    ADD_TEST_CASE(MyClass, myTestCase);
 * It will name the test as its method and assume the object this.
 */
#define ADD_TEST_CASE(thisclass, method) \
      add(#method, new MemberFunction<thisclass>(this, &thisclass::method))
// I was unable to use decltype(*this)

/**
 * Test case adding helper including time limit. Use as:
 *    ADD_TEST_CASE_TIME(MyClass, myTestCase, 10);
 * It will name the test as its method and assume the object this.
 */
#define ADD_TEST_CASE_TIME(thisclass, method, time) \
      add(#method, new MemberFunction<thisclass>(this, &thisclass::method), time)

/**
 * Print a message in the console only if in verbose mode.
 */
#define TEST_PRINTLN(msg) \
      do { \
         if(verbose()) { \
            PRINTLN("  " + msg); \
         } \
      } while(false)


/**
 * Checks that the condition is true. Otherwise aborts.
 */
#define ASSERT(cond) \
      do { \
         if( !(cond) ) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT"); \
            ex->add("condition", #cond); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the condition is true. Otherwise aborts.
 * Adds extra information.
 */
#define ASSERT_EX(cond, extra) \
      do { \
         if( !(cond) ) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_EX"); \
            ex->add("extra", (::Storage::Structure::Text::StringBuffer) extra); \
            ex->add("condition", #cond); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the condition is false. Otherwise aborts.
 */
#define ASSERT_NO(cond) \
      do { \
         if( (cond) ) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_NO"); \
            ex->add("condition", #cond); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the condition is false. Otherwise aborts.
 * Adds extra information.
 */
#define ASSERT_NO_EX(cond, extra) \
      do { \
         if( (cond) ) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_NO_EX"); \
            ex->add("extra", (::Storage::Structure::Text::StringBuffer) extra); \
            ex->add("condition", #cond); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the two integer expressions are equal. Otherwise aborts.
 */
#define ASSERT_EQ(exp1, exp2) \
      do { \
         _int e1 = (exp1); \
         _int e2 = (exp2); \
         if(e1 != e2) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_EQ"); \
            ex->add("exp1", #exp1); \
            ex->addInt("exp1.value", e1); \
            ex->add("exp2", #exp2); \
            ex->addInt("exp2.value", e2); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the two integer expressions are equal. Otherwise aborts.
 * Adds extra information.
 */
#define ASSERT_EQ_EX(exp1, exp2, extra) \
      do { \
         _int e1 = (exp1); \
         _int e2 = (exp2); \
         if(e1 != e2) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_EQ_EX"); \
            ex->add("extra", (::Storage::Structure::Text::StringBuffer) extra); \
            ex->add("exp1", #exp1); \
            ex->addInt("exp1.value", e1); \
            ex->add("exp2", #exp2); \
            ex->addInt("exp2.value", e2); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the two integer expressions are not equal. Otherwise aborts.
 */
#define ASSERT_NO_EQ(exp1, exp2) \
      do { \
         _int e1 = (exp1); \
         _int e2 = (exp2); \
         if(e1 == e2) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_NO_EQ"); \
            ex->add("exp1", #exp1); \
            ex->addInt("exp1.value", e1); \
            ex->add("exp2", #exp2); \
            ex->addInt("exp2.value", e2); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the two integer expressions are not equal. Otherwise aborts.
 * Adds extra information.
 */
#define ASSERT_NO_EQ_EX(exp1, exp2, extra) \
      do { \
         _int e1 = (exp1); \
         _int e2 = (exp2); \
         if(e1 == e2) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_NO_EQ_EX"); \
            ex->add("extra", (::Storage::Structure::Text::StringBuffer) extra); \
            ex->add("exp1", #exp1); \
            ex->addInt("exp1.value", e1); \
            ex->add("exp2", #exp2); \
            ex->addInt("exp2.value", e2); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the expression throws a specific exception. Otherwise aborts.
 */
#define ASSERT_THROW(exp, except) \
      do { \
         _bool thrown = false; \
         try { \
            exp; \
         } catch(except *ex) { \
            thrown = true; \
            delete ex; \
         } \
         if(!thrown) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_THROW"); \
            ex->add("exp", #exp); \
            ex->add("except", #except); \
            throw ex; \
         } \
      } while(false)

/**
 * Checks that the expression throws an exception. Otherwise aborts.
 * Adds extra information.
 */
#define ASSERT_THROW_EX(exp, except, extra) \
      do { \
         _bool thrown = false; \
         try { \
            exp; \
         } catch(except *ex) { \
            thrown = true; \
            delete ex; \
         } \
         if(!thrown) { \
            MAKE_ERROR(ex, Error::Test::Assertion); \
            ex->add("macro", "ASSERT_THROW_EX"); \
            ex->add("extra", (::Storage::Structure::Text::StringBuffer) extra); \
            ex->add("exp", #exp); \
            ex->add("except", #except); \
            throw ex; \
         } \
      } while(false)

