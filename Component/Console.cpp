/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

#undef const_pointer
#include <unistd.h>
#include <stdio.h>
#include <iostream>

namespace Component {

void Console::write(StringBuffer str)
{
   String s = str.toString();
   const _char *utf8 = (const _char *)s.getUTF8();
   
   /* Std handles funny the unknown exceptions and that prevents the fault
    * interrupts to work properly.
    */
   //std::cout << utf8;

   ::write(STDOUT_FILENO, utf8, Storage::Structure::Binary::Buffer::strlen(utf8));
}

String Console::readLine()
{
   std::string str;
   std::getline(std::cin, str);
   return (String) str.c_str();
}

}

