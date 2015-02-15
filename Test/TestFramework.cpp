/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
using namespace ::Storage::Memory;
#endif

namespace Test {

const_int TestFramework::MEMORY_KB;


TestFramework::TestFramework()
{
   _root = new RootSuite(this);

   _tests = new ArrayList<TestCase>(false);

   _repeat = 1;
   _verbose = false;
   _report = null;

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   _int bytes = MEMORY_KB * 1024;
   _memBuffer = new _byte[bytes];
   _memPages = new BufferPageAllocator(_memBuffer, bytes, 10);
   _memRunner = new RunnerAllocator(_memPages, 0);
#endif
}

TestFramework::~TestFramework()
{
   delete _root;
   delete _tests;
   if(_report != null)
      delete _report;

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   delete _memRunner;
   delete _memPages;
   delete _memBuffer;
#endif
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
                        ERROR("Storage.Structure.InvalidLength");
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
   catch(Exception *ex)
   {
      if(ex->id() != "Test.InvalidFilter")
         throw ex;

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
   ::Component::Error::Messages::get("OperationNotAllowed");
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
#ifndef __HELIO_STORAGE_MEMORY_MANAGER
   PRINTLN("Warning: Memory check not available.");
#endif

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
      catch(Exception *ex)
      {
         tc->error = true;
         _report->fixtureError(tc, ex);

         if(ex->id() == "Component.Error.UserInterrupt")
            throw ex;
         delete ex;
      }
      catch(std::exception &stdex)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR("Test.UnknownException");
         ex->add("std.class", typeid(stdex).name());
         ex->add("std.what", stdex.what());
         _report->fixtureError(tc, ex);
         delete ex;
      }
      catch(...)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR("Test.UnknownException");
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
            catch(Exception *ex)
            {
               tc->error = true;
               _report->fixtureError(tc, ex);

               if(ex->id() == "Component.Error.UserInterrupt")
                  throw ex;
               delete ex;
            }
            catch(std::exception &stdex)
            {
               tc->error = true;
               Exception *ex = MAKE_ERROR("Test.UnknownException");
               ex->add("std.class", typeid(stdex).name());
               ex->add("std.what", stdex.what());
               _report->fixtureError(tc, ex);
               delete ex;
            }
            catch(...)
            {
               tc->error = true;
               Exception *ex = MAKE_ERROR("Test.UnknownException");
               _report->fixtureError(tc, ex);
               delete ex;
            }


            if(!tc->error)
            {
               // Test run
               _report->testStart(tc);

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
               // Debug allocator
               _memRunner->clear();
               DebugAllocator *mem_debug = new DebugAllocator(_memRunner);
               _int mem_id = Manager::current()->registerAlloc(mem_debug);
#endif

               // Time control
               _uint64 start_time = 0;
               _uint64 end_time = 0;
               Fault::setTimeOut(tc->timeSeconds);
               start_time = Device::Time::Clock::getCurrentMillis();
               
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
               Manager::current()->push(mem_id);
#endif
               try
               {
                  tc->method->invoke();
               }
               catch(Exception *ex)
               {
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
                  Manager::current()->pop();
#endif                  
                  Fault::setTimeOut(0);

                  tc->error = true;
                  _report->testError(tc, ex);

                  if(ex->id() == "Component.Error.UserInterrupt")
                     throw ex;
                     
                  if(ex->id() == "Component.Error.MemoryFault"
                        || ex->id() == "Component.Error.FloatingPoint"
                        || ex->id() =="Component.Error.IllegalInstruction"
                        || ex->id() == "Component.Error.TimeOut")
                     delete ex;
                  // Elsewhere not, because it was created in a debug environment
               }
               catch(std::exception &stdex)
               {
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
                  Manager::current()->pop();
#endif
                  Fault::setTimeOut(0);

                  tc->error = true;
                  Exception *ex = MAKE_ERROR("Test.UnknownException");
                  ex->add("std.class", typeid(stdex).name());
                  ex->add("std.what", stdex.what());
                  _report->testError(tc, ex);
                  //delete ex;   // Created in a debug environment
               }
               catch(...)
               {
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
                  Manager::current()->pop();
#endif
                  Fault::setTimeOut(0);

                  tc->error = true;
                  Exception *ex = MAKE_ERROR("Test.UnknownException");
                  _report->testError(tc, ex);
                  //delete ex;   // Created in a debug environment
               }
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
               if(!tc->error)
                  Manager::current()->pop();
#endif
               end_time = Device::Time::Clock::getCurrentMillis();
               Fault::setTimeOut(0);

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
               if(!tc->error)
               {
                  // Check memory errors
                  ArrayList *objs = mem_debug->objects();
                  for(_int i = 0; i < objs->count(); i++)
                  {
                     ObjectDebug *o = objs->get(i)->as<ObjectDebug>();
                     if(!o->correct())
                     {
                        if(o->alloc == null)
                        {
                           for(_int j = 0; j < o->deallocs->count(); j++)
                           {
                              tc->error = true;
                              Exception *ex = new Exception("Storage.Memory.InvalidPointer",
                                    new Trace(o->deallocs->get(j)->as<Trace>()));
                              ex->addPointer("pointer", o->obj);
                              _report->testError(tc, ex);
                              delete ex;
                           }
                        }
                        else
                        {
                           if(o->deallocs->count() == 0)
                           {
                              tc->error = true;
                              Exception *ex = new Exception("Storage.Memory.MemoryLeak", new Trace(o->alloc));
                              ex->addPointer("pointer", o->obj);
                              ex->addInt("size", o->size);
                              _report->testError(tc, ex);
                              delete ex;
                           }
                           else
                           {
                              for(_int j = 1; j < o->deallocs->count(); j++)
                              {
                                 tc->error = true;
                                 Exception *ex = new Exception("Storage.Memory.DoubleDeallocation",
                                       new Trace(o->deallocs->get(j)->as<Trace>()));
                                 ex->addPointer("pointer", o->obj);
                                 ex->addInt("size", o->size);
                                 _report->testError(tc, ex);
                                 delete ex;
                              }
                           }
                        }
                     }
                  }
               }
               
               Manager::current()->unregisterAlloc(mem_id);
               delete mem_debug;
#endif

               _int millis = 0;
               if(!tc->error)
                  millis = (_int)(end_time - start_time);

               _report->testEnd(tc, millis);

               // Fixture destroy
               try
               {
                  tc->test->destroy();
               }
               catch(Exception *ex)
               {
                  tc->error = true;
                  _report->fixtureError(tc, ex);

                  if(ex->id() == "Component.Error.UserInterrupt")
                     throw ex;
                  delete ex;
               }
               catch(std::exception &stdex)
               {
                  tc->error = true;
                  Exception *ex = MAKE_ERROR("Test.UnknownException");
                  ex->add("std.class", typeid(stdex).name());
                  ex->add("std.what", stdex.what());
                  _report->fixtureError(tc, ex);

                  if(ex->id() == "Component.Error.UserInterrupt")
                     throw ex;
                  delete ex;
               }
               catch(...)
               {
                  tc->error = true;
                  Exception *ex = MAKE_ERROR("Test.UnknownException");
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
      catch(Exception *ex)
      {
         tc->error = true;
         _report->fixtureError(tc, ex);

         if(ex->id() == "Component.Error.UserInterrupt")
            throw ex;
         delete ex;
      }
      catch(std::exception &stdex)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR("Test.UnknownException");
         ex->add("std.class", typeid(stdex).name());
         ex->add("std.what", stdex.what());
         _report->fixtureError(tc, ex);
         delete ex;
      }
      catch(...)
      {
         tc->error = true;
         Exception *ex = MAKE_ERROR("Test.UnknownException");
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
   TestFramework *tf;
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
   catch(Exception *ex)
   {
      if(ex->id() == "Component.Error.UserInterrupt")
      {
         PRINTLN(ex->msg());

         if(tf != null)
            delete tf;
         return 2;
      }

      /* No attempt to delete the framework is made because at this
       * point it is far more important to report.
       */
      PRINTLN(" *** CRITICAL ERROR ***");
      PRINTLN(ex->dump());
      return 3;
   }
   catch(...)
   {
      PRINTLN(" *** CRITICAL ERROR ***");
      PRINTLN("Unknown exception!!!");
      return 3;
   }
}
