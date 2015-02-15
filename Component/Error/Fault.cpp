/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

using namespace Storage::Structure;

namespace Component {
namespace Error {

// Signal handlers:
// Defined here because of the type siginfo_t

/**
 * Segment fault signal handler.
 */
void sig_segv(int signal, siginfo_t *si, void *arg)
{
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->push(0);
#endif

   Exception *ex = new Exception("Component.Error.MemoryFault", 2);
   ex->addPointer("address", si->si_addr);
   switch(si->si_code)
   {
      case SEGV_MAPERR:
         ex->add("reason", "Address not mapped");
         break;
      case SEGV_ACCERR:
         ex->add("reason", "Invalid permissions");
         break;
      default:
         ex->addInt("code", si->si_code);
   }
   
#ifdef __HELIO_STORAGE_MEMORY_MANAGER   
   Storage::Memory::Manager::current()->pop();
#endif
   throw ex;
}

/**
 * Floating point exception signal handler.
 */
void sig_fpe(int signal, siginfo_t *si, void *arg)
{
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->push(0);
#endif

   Exception *ex = new Exception("Component.Error.FloatingPoint", 2);
   ex->addPointer("address", si->si_addr);
   switch(si->si_code)
   {
      case FPE_INTDIV:
         ex->add("reason", "Integer divide-by-zero");
         break;
      case FPE_INTOVF:
         ex->add("reason", "Integer overflow");
         break;
      case FPE_FLTDIV:
         ex->add("reason", "Floating point divide-by-zero");
         break;
      case FPE_FLTOVF:
         ex->add("reason", "Floating point overflow");
         break;
      case FPE_FLTUND:
         ex->add("reason", "Floating point underflow");
         break;
      case FPE_FLTRES:
         ex->add("reason", "Floating point inexact result");
         break;
      case FPE_FLTINV:
         ex->add("reason", "Invalid floating point operation");
         break;
      case FPE_FLTSUB:
         ex->add("reason", "Subscript out of range");
         break;
      default:
         ex->addInt("code", si->si_code);
   }
   
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->pop();
#endif
   throw ex;
}

/**
 * Illegal instruction signal handler.
 */
void sig_ill(int signal, siginfo_t *si, void *arg)
{
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->push(0);
#endif
   
   Exception *ex = new Exception("Component.Error.IllegalInstruction", 2);
   ex->addPointer("address", si->si_addr);
   switch(si->si_code)
   {
      case ILL_ILLOPC:
         ex->add("reason", "Illegal opcode");
         break;
      case ILL_ILLOPN:
         ex->add("reason", "Illegal operand");
         break;
      case ILL_ILLADR:
         ex->add("reason", "Illegal addressing mode");
         break;
      case ILL_ILLTRP:
         ex->add("reason", "Illegal trap");
         break;
      case ILL_PRVOPC:
         ex->add("reason", "Privileged opcode");
         break;
      case ILL_PRVREG:
         ex->add("reason", "Privileged register");
         break;
      case ILL_COPROC:
         ex->add("reason", "Coprocessor error");
         break;
      case ILL_BADSTK:
         ex->add("reason", "Internal stack error");
         break;
      default:
         ex->addInt("code", si->si_code);
   }
   
#ifdef __HELIO_STORAGE_MEMORY_MANAGER   
   Storage::Memory::Manager::current()->pop();
#endif
   throw ex;
}

/**
 * User interrupt (Ctrl C) signal handler.
 */
void sig_int(int signal, siginfo_t *si, void *arg)
{
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->push(0);
#endif

   Exception *ex = new Exception("Component.Error.UserInterrupt", 2);
   ex->addPointer("address", si->si_addr);

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->pop();
#endif
   throw ex;
}

/**
 * Alarm or time out signal handler.
 */
void sig_alarm(int signal, siginfo_t *si, void *arg)
{
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->push(0);
#endif

   Exception *ex = new Exception("Component.Error.TimeOut", 2);

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   Storage::Memory::Manager::current()->pop();
#endif
   throw ex;
}


void Fault::install()
{
   struct sigaction sa;

   Binary::Buffer::memset(&sa, 0, sizeof(struct sigaction));
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_SIGINFO;
   
   sa.sa_sigaction = sig_segv;   
   sigaction(SIGSEGV, &sa, NULL);

   sa.sa_sigaction = sig_fpe;
   sigaction(SIGFPE, &sa, NULL);
   
   sa.sa_sigaction = sig_ill;
   sigaction(SIGILL, &sa, NULL);

   sa.sa_sigaction = sig_int;
   sigaction(SIGINT, &sa, NULL);

   sa.sa_sigaction = sig_alarm;
   sigaction(SIGALRM, &sa, NULL);
}

void Fault::setTimeOut(int seconds)
{
   alarm(seconds);
}

} }

