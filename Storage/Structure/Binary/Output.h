/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Abstract bytes output
 * Abstract bytes output.
 */
class Output : 
      public virtual Object
{
public:
   /**
    * Write a buffer.
    * If bytes is zero, buffer length is the requested size.
    * Argument start is the start of the buffer where get bytes.
    */
   virtual void write(Buffer *buf, _int bytes = 0, _int start = 0) = 0;
};

