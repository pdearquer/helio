/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Abstract characters input.
 * Abstract characters input.
 */
class Input : 
      public virtual Object
{
public:
   /**
    * Read some characters to the buffer (increase capacity if necesary).
    * Returns the number of characters read.
    * If chars is zero, buffer capacity is the requested size.
    * Argument start is the start of the buffer where place characters.
    */
   virtual _int read(Buffer *buf, _int chars = 0, _int start = 0) = 0;
};

