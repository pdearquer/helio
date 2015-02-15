/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Testing framework and runner
 * Manage and process all the tests in secure environments.
 *
 * A single test is called a test case and it is implemented with a
 * single method within the Test class. All the test cases in a single
 * class form a test unit or simply a test. Tests are grouped in
 * test suites. A test suite can contain more test suites.
 *
 * This framework manage the test's structure and run the required
 * test cases. Every test case run in an independent secure environment.
 * At the end of the run all the memory allocated must be released.
 */
class TestFramework :
      public virtual Object
{
protected:
   /**
    * Default size of the memory for the tests in KB.
    */
   static_const_int MEMORY_KB = (sizeof(_int) == 16/8) ? 15 : 32;

   
   /**
    * Root test suite.
    */
   TestSuite *_root;
   
   /**
    * Test cases selected. See TestCase.
    */
   ArrayList<TestCase> *_tests;

   /**
    * Number of times to repeat every test.
    * If a test report errors, it stops running.
    * The value of 0 means for ever.
    */
   _int _repeat;

   /**
    * Running in verbose mode.
    */
   _bool _verbose;

   /**
    * Test reports handler.
    */
   TestReporter *_report;

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   /**
    * Memory buffer for the tests to run.
    */
   _byte *_memBuffer;

   /**
    * Memory pages allocator.
    */
   ::Storage::Memory::BufferPageAllocator *_memPages;

   /**
    * Memory runner allocator
    */
   ::Storage::Memory::RunnerAllocator *_memRunner;
#endif


public:
   /**
    * Build up the list of tests.
    */
   TestFramework();

   /**
    * Clean up ignoring errors
    */
   virtual ~TestFramework();


   /**
    * Set up the test runner parameters from the command line.
    * @return true if the configuration is correct.
    */
   _bool setup(int argc, char **argv);

   /**
    * Says if running in verbose mode.
    */
   _bool verbose();

   /**
    * Returns selected test cases list. See TestCase.
    */
   ArrayList<TestCase> *tests();


   /**
    * Run the tests as setup.
    * @return true if all gone correctly.
    */
   _bool run();
};

