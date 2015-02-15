/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** FIFO queue.
 * First Input First Output byte queue buffer.
 */
class FIFO : 
      public virtual Output,
      public virtual Input
{
protected:
   /**
    * Buffer store.
    */
   Buffer buffer;
   
   
public:
   /**
    * Create a FIFO queue.
    */
   FIFO();
   
   
   /**
    * Bytes currently stored
    */
   _int length();
   
   
   /**
    * Write a buffer.
    * If bytes is zero, buffer length is the requested size.
    * Argument start is the start of the buffer where get bytes.
    */
   virtual void write(Buffer *buf, _int bytes = 0, _int start = 0);
   
   /**
    * Read some bytes to the buffer (increase capacity if necesary).
    * Returns the number of bytes read.
    * If bytes is zero, buffer capacity is the requested size.
    * Argument start is the start of the buffer where place bytes.
    */
   virtual _int read(Buffer *buf, _int bytes = 0, _int start = 0);
};

