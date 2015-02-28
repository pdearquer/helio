/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

using namespace ::Loader;

namespace Test {

const_int TestFramework::MEMORY_KB;


TestFramework::TestFramework()
{
   _root = new RootSuite(this);

   _tests = new ArrayList<TestCase>(false);

   _repeat = 1;
   _verbose = false;
   _report = null;
}

TestFramework::~TestFramework()
{
   delete _root;
   delete _tests;
   if(_report != null)
      delete _report;
}


_bool TestFramework::setup(int argc, char **argv)
{
   String run = "*";
   _bool list = false;

   // Process command line
   for(_int i = 1; i < argc; i++)
   {
      String arg = argv[i];

      if(arg.startsWith("--"))
      {
         if(arg == "--help" || arg == "-h")
         {
            PRINTLN("Run a set of tests");
            PRINTLN("use:");
            PRINTLN("test [--run * | Suite | Suite.Test | Suite.Test.testCase]");
            PRINTLN("     [--repeat <number> | -]   # Stops on error. By default 1 time");
            PRINTLN("     [--list]   # Dump a list of the tests selected and end");
            PRINTLN("     [--verbose | --silent]   # Silent by default (only errors)");
            PRINTLN("");
            return false;
         }
         else if(arg == "--run")
         {
            if(i + 1 >= argc)
            {
               PRINTLN("Run filtering required");
               PRINTLN("Run test --help for more information.");
               return false;
            }
            else
            {
               i++;
               String value = argv[i];
               if(value.startsWith("--"))
               {
                  PRINTLN("Run filtering required");
                  PRINTLN("Run test --help for more information.");
                  return false;
               }

               run = value;
            }
         }
         else if(arg == "--repeat")
         {
            if(i + 1 >= argc)
            {
               PRINTLN("Repeat value required");
               PRINTLN("Run test --help for more information.");
               return false;
            }
            else
            {
               i++;
               String value = argv[i];
               if(value.startsWith("--"))
               {
                  PRINTLN("Repeat value required");
                  PRINTLN("Run test --help for more information.");
                  return false;
               }

               if(value == "-")
               {
                  _repeat = 0;
               }
               else
               {
                  try
                  {
                     _repeat = Format::def()->toInt(value);
                     if(_repeat < 0)
                        ERROR(Error::Structure::InvalidLength);
                  }
                  catch(Exception *ex)
                  {
                     delete ex;
                     PRINTLN("Repeat value required");
                     PRINTLN("Run test --help for more information.");
                     return false;
                  }
               }
            }
         }
         else if(arg == "--list")
         {
            list = true;
         }
         else if(arg == "--verbose")
         {
            _verbose = true;
         }
         else if(arg == "--silent")
         {
            _verbose = false;
         }
         else
         {
            PRINTLN("Argument \"" + arg + "\" not recognized.");
            PRINTLN("Run test --help for more information.");
            return false;
         }
      }
      else
      {
         PRINTLN("Argument \"" + arg + "\" not recognized.");
         PRINTLN("Run test --help for more information.");
         return false;
      }
   }

   // Make filtered list
   _tests->clear();
   try
   {
      _root->appendTests(_tests, "", run);
   }
   catch(Exception::Test::IllegalFilter *ex)
   {
      PRINTLN("Test filter \"" + run + "\" not valid.");
      delete ex;
      return false;
   }
   if(_tests->count() == 0)
   {
      PRINTLN("No test selected.");
      return false;
   }

   // List tests if requested
   if(list)
   {
      for(_int i = 0; i < _tests->count(); i++)
      {
         TestCase *tc = _tests->get(i);
         PRINTLN(tc->fullName);
      }
      return false;
   }

   // Set up the Reporter
   if(_verbose)
      _report = new VerboseReporter();
   else
      _report = new TestReporter();

   /* Load all the singletons to prevent them to load on a
    * debug environment.
    */
   ::Storage::Structure::Text::Format::def();
   Date now;

   return true;
}

_bool TestFramework::verbose()
{
   return _verbose;
}

ArrayList<TestCase> *TestFramework::tests()
{
   return _tests;
}


_bool TestFramework::run()
{
   PRINTLN("Warning: Memory check not available.");

   _report->runStart(this);
   _bool run_error = false;

   // Test unit setups
   for(_int i = 0; i < _tests->count(); i++)
   {
      TestCase *tc = _tests->get(i);
      try
      {
         tc->test->setupTestOnce();
      }
      catch(Error::UserInterrupt *ex)
      {
         throw ex;
      }
      catch(Component::Error::Throwable *ex)
      {
         tc->error = true;
         _report->fixtureError(tc, ex);
         delete ex;
      }
      catch(std::exception &stdex)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
         ex->add("std.class", typeid(stdex).name());
         ex->add("std.what", stdex.what());
         _report->fixtureError(tc, ex);
         delete ex;
      }
      catch(...)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
         _report->fixtureError(tc, ex);
         delete ex;
      }

      if(tc->error)
         run_error = true;
   }

   _int iteration = 0;
   while(true)
   {
      // TODO: Order randomly

      // Process
      _bool none_run = true;
      for(_int i = 0; i < _tests->count(); i++)
      {
         TestCase *tc = _tests->get(i);

         if(!tc->error)
         {
            // Fixture setup
            try
            {
               tc->test->setup();
            }
            catch(Error::UserInterrupt *ex)
            {
               throw ex;
            }
            catch(Component::Error::Throwable *ex)
            {
               tc->error = true;
               _report->fixtureError(tc, ex);
               delete ex;
            }
            catch(std::exception &stdex)
            {
               tc->error = true;
               Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
               ex->add("std.class", typeid(stdex).name());
               ex->add("std.what", stdex.what());
               _report->fixtureError(tc, ex);
               delete ex;
            }
            catch(...)
            {
               tc->error = true;
               Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
               _report->fixtureError(tc, ex);
               delete ex;
            }


            if(!tc->error)
            {
               // Test run
               _report->testStart(tc);

               // Time control
               _uint64 start_time = 0;
               _uint64 end_time = 0;
               Simulation::setTimeOut(tc->timeSeconds);
               start_time = Device::Time::Clock::getCurrentMillis();
               
               try
               {
                  tc->method->invoke();
               }
               catch(Error::TimeOut *ex)
               {
               Simulation::setTimeOut(0);

                  tc->error = true;
                  _report->testError(tc, ex);
                  delete ex;
               }
               catch(Error::UserInterrupt *ex)
               {
                  Simulation::setTimeOut(0);
                  throw ex;
               }
               catch(::Component::Error::Throwable *ex)
               {       
                  Simulation::setTimeOut(0);

                  tc->error = true;
                  _report->testError(tc, ex);
                  delete ex;
               }
               catch(std::exception &stdex)
               {
                  Simulation::setTimeOut(0);

                  tc->error = true;
                  Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
                  ex->add("std.class", typeid(stdex).name());
                  ex->add("std.what", stdex.what());
                  _report->testError(tc, ex);
                  delete ex;
               }
               catch(...)
               {
                  Simulation::setTimeOut(0);

                  tc->error = true;
                  Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
                  _report->testError(tc, ex);
                  delete ex;
               }
               
               Simulation::setTimeOut(0);
               end_time = Device::Time::Clock::getCurrentMillis();
               
               _int millis = 0;
               if(!tc->error)
                  millis = (_int)(end_time - start_time);

               _report->testEnd(tc, millis);

               // Fixture destroy
               try
               {
                  tc->test->destroy();
               }
               catch(Error::UserInterrupt *ex)
               {
                  throw ex;
               }
               catch(Component::Error::Throwable *ex)
               {       
                  tc->error = true;
                  _report->fixtureError(tc, ex);
                  delete ex;
               }
               catch(std::exception &stdex)
               {
                  tc->error = true;
                  Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
                  ex->add("std.class", typeid(stdex).name());
                  ex->add("std.what", stdex.what());
                  _report->fixtureError(tc, ex);
                  delete ex;
               }
               catch(...)
               {
                  tc->error = true;
                  Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
                  _report->fixtureError(tc, ex);
                  delete ex;
               }
            }

            if(tc->error)
               run_error = true;
            none_run = false;
         }
      }

      if(none_run)
         break;

      iteration++;
      if(_repeat > 0 && iteration >= _repeat)
         break;
   }

   // Test unit destroys
   for(_int i = 0; i < _tests->count(); i++)
   {
      TestCase *tc = _tests->get(i);
      try
      {
         tc->test->destroyTestOnce();
      }
      catch(Error::UserInterrupt *ex)
      {
         throw ex;
      }
      catch(Component::Error::Throwable *ex)
      {       
         tc->error = true;
         _report->fixtureError(tc, ex);
         delete ex;
      }
      catch(std::exception &stdex)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
         ex->add("std.class", typeid(stdex).name());
         ex->add("std.what", stdex.what());
         _report->fixtureError(tc, ex);
         delete ex;
      }
      catch(...)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR(Exception::Test::UnknownException);
         _report->fixtureError(tc, ex);
         delete ex;
      }

      if(tc->error)
         run_error = true;
   }

   _report->runEnd(run_error);
   return !run_error;
}

}


using namespace Test;

/**
 * Main application entry.
 */
int main(int argc, char **argv)
{
   TestFramework *tf = null;
   try
   {
      PRINTLN("[Helio Test framework]");

      tf = new TestFramework();
      bool ret = tf->setup(argc, argv);
      if(!ret)
      {
         delete tf;
         return 2;
      }

      ret = tf->run();

      delete tf;

      if(ret)
         return 0;
      else
         return 1;
   }
   catch(Error::UserInterrupt *ex)
   {
      PRINTLN(ex->msg());
      delete ex;
      
      if(tf != null)
         delete tf;
         
      return 2;
   }
   catch(Component::Error::Throwable *ex)
   {
      /* No attempt to delete the framework or exception is made
       * because at this point it is far more important to report.
       */
      PRINTLN(" *** CRITICAL ERROR ***");
      ex->report();
      return 3;
   }
   catch(...)
   {
      PRINTLN(" *** CRITICAL ERROR ***");
      PRINTLN("Unknown exception!!!");
      return 3;
   }
}

