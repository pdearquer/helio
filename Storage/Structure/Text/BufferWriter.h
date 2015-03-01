/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Character output to a buffer.
 * Character output to a buffer.
 */
class BufferWriter : 
      public virtual Output
{
protected:
   /**
    * Buffer reference.
    */
   Buffer *_buffer;
   
   
public:
   /**
    * Prepare the buffer reader.
    */
   BufferWriter(Buffer *buf);
   
   
   /**
    * Write a buffer.
    * If chars is zero, buffer length is the requested size.
    * Argument start is the start of the buffer where get characters.
    */
   virtual void write(Buffer *buf, _int chars = 0, _int start = 0);
   
   /**
    * Write a string of characters.
    */
   virtual void write(String str);
};

