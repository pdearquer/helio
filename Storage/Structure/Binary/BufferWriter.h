/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Byte output to a buffer.
 * Byte output to a buffer.
 */
class BufferWriter : 
      public virtual Input
{
protected:
   /**
    * Buffer reference.
    */
   Buffer *buffer;
   
   
public:
   /**
    * Prepare the buffer reader.
    */
   BufferWriter(Buffer *buf);
   
   
   /**
    * Write a buffer.
    * If bytes is zero, buffer lenght is the requested size.
    * Argument start is the start of the buffer where get bytes.
    */
   virtual void write(Buffer *buf, _int bytes = 0, _int start = 0);   
};
