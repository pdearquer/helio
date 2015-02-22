/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Component {
namespace Error {

void Reporter::report(Throwable *error, _bool silently)
{
   if(silently)
      return;
      
   while(error != null)
   {
      if(error->is<Exception>())
      {
         PRINTLN("Exception: " + error->msg());
      }
      else if(error->is< ::Error>())
      {
         PRINTLN("Error: " + error->msg());
      }
      else if(error->is<Fault>())
      {
         PRINTLN("Fault: " + error->msg());
      }
      else
      {
         PRINTLN(error->getClass() + ": " + error->msg());
      }
      
      _int pars = 0;
      const Table<String, String> *params = error->params();
      if(params->contains("debug.file"))
      {
         PRINT(" from " + params->get("debug.file"));
         pars++;
         
         if(params->contains("debug.line"))
         {
            PRINT(':' + params->get("debug.line"));
            pars++;
         }
         
         if(params->contains("debug.date"))
         {
            PRINT(" (" + params->get("debug.date") + ")");
            pars++;
         }

         PRINT("\n");
      }
      
      if(params->count() > pars)
      {
         for(_int i = 0; i < params->count(); i++)
         {
            String key = params->getKey(i);
            if(key != "debug.file" && key != "debug.line" && key != "debug.date")
            {
               PRINTLN("   " + key + ": " + params->get(key));
            }
         }
      }

      if(error->child() == null)
      {
         // Prints only the stack trace of the original error
         PRINT(error->trace()->toString());
         break;
      }
      
      error = error->child();
      PRINTLN("Child exception:");
   }
}

} }

