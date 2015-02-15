/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#undef const_pointer
#include <iostream>

namespace Component {
namespace Error {

void Error::critical(const char *id, const char *file, int line, const char *date)
{
   std::cout << "Critical Error: " << id << std::endl;
   exit(-1);

   for(;;) ;
}
   
void Error::warning(String id, String file, _int line, String date)
{
   PRINTLN("Warning (" + file + ":" + line + ") : " + Messages::get(id));
}

} }

