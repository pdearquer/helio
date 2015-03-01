/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Console user interface
 * Basic support for a console user interface.
 *
 * It is preferred to use the print macros defined below:
 *  PRINT(msg)
 *  PRINTLN(msg)
 *
 * For example:
 *  PRINTLN("The result is " + distance + " meters.");
 *
 * This class is only intended for debugging and will be deprecated.
 * TODO: Get rid of platform dependency.
 */
class Console :
   public virtual Object
{
public:

   /**
    * Prints out a string to the user.
    */
   static void write(StringBuffer str);

   /**
    * Reads a line from the user input.
    */
   static String readLine();
};

/**
 * Prints a message to the console.
 * It makes a cast to StringBuffer to support uses like:
 *  PRINT(12);
 */
#define PRINT(msg) \
      ::Component::Console::write((::Storage::Structure::Text::StringBuffer) msg)

/**
 * Prints a line (message plus line feed) to the console.
 * It makes a cast to StringBuffer to support uses like:
 *  PRINTLN(12);
 */
#define PRINTLN(msg) \
      ::Component::Console::write((::Storage::Structure::Text::StringBuffer) msg + "\n")

