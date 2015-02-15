/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Console user interface
 * Basic support for a console user interface.
 *
 * This class is only intented for debuging and will be deprecated.
 * TODO: Get rid of platform dependency.
 */
class Console :
   public virtual Object
{
public:

   /**
    * Prints out a string.
    */
   static void write(StringBuffer str);

   /**
    * Reads a line from the user input.
    */
   static String readLine();
};


#define PRINT(msg) \
      ::Component::Console::write((::Storage::Structure::Text::StringBuffer) msg)

#define PRINTLN(msg) \
      ::Component::Console::write((::Storage::Structure::Text::StringBuffer) msg + "\n")

