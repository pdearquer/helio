/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Byte input from a buffer.
 * Byte input from a buffer.
 */
class BufferReader : 
      public virtual Input
{
protected:
   /**
    * Buffer reference.
    */
   Buffer *buffer;
   
   /**
    * Current position (last byte read).
    */
   _int position;
   
   
public:
   /**
    * Prepare the buffer reader.
    */
   BufferReader(Buffer *buf);
   
   
   /**
    * Read some bytes to the buffer (increase capacity if necessary).
    * Returns the number of bytes read.
    * If bytes is zero, buffer capacity is the requested size.
    * Argument start is the start of the buffer where place bytes.
    */
   virtual _int read(Buffer *buf, _int bytes = 0, _int start = 0);
   
   
   /**
    * Gets the current position.
    */
   _int seek();
   
   /**
    * Sets the current position.
    */
   _int seek(_int pos);
};

