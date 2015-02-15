/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#ifdef __HELIO_STORAGE_MEMORY_MANAGER
using namespace Storage::Memory;
#endif

namespace Loader {

Simulation Simulation::_init;


Simulation::Simulation()
{
#ifdef __HELIO_STORAGE_MEMORY_MANAGER
   // Memory manager
   _byte buf[sizeof(StdAllocator)];
   Manager::init(new(buf) StdAllocator());
   Manager::init(new StdAllocator());   // Allocate the allocator within itself
   
   Manager::current()->registerThread();    
#endif
   
   // Fault handler
   Component::Error::Fault::install();
   
   PRINTLN("[" + __HELIO_PRODUCT + " " + __HELIO_VERSION + " ready]");
}

}

