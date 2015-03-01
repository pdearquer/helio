/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Abstract bytes input
 * Abstract bytes input.
 */
class Input : 
      public virtual Object
{
public:
   /**
    * Read some bytes to the buffer (increase capacity if necessary).
    * Returns the number of bytes read.
    * If bytes is zero, buffer capacity is the requested size.
    * Argument start is the start of the buffer where place bytes.
    */
   virtual _int read(Buffer *buf, _int bytes = 0, _int start = 0) = 0;
};

