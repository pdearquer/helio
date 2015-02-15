/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Abstract characters output
 * Abstract characters output.
 */
class Output : 
      public virtual Object
{
public:
   /**
    * Write a buffer of characters.
    * If chars is zero, buffer lenght is the requested size.
    * Argument start is the start of the buffer where get characters.
    */
   virtual void write(Buffer *buf, _int chars = 0, _int start = 0) = 0;
   
   /**
    * Write a string of characters.
    */
   virtual void write(String str);
};

