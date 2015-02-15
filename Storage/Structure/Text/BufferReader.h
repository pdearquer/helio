/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Character input from a buffer.
 * Character input from a buffer.
 */
class BufferReader : 
      public virtual Input
{
protected:
   /**
    * Buffer reference.
    */
   Buffer *_buffer;
   
   /**
    * Current position (last character read).
    */
   _int _position;
   
   
public:
   /**
    * Prepare the buffer reader.
    */
   BufferReader(Buffer *buf);
   
   
   /**
    * Read some characters to the buffer (increase capacity if necesary).
    * Returns the number of characters read.
    * If chars is zero, buffer capacity is the requested size.
    * Argument start is the start of the buffer where place bytes.
    */
   virtual _int read(Buffer *buf, _int chars = 0, _int start = 0);
   
   
   /**
    * Gets the current position.
    */
   _int seek();
   
   /**
    * Sets the current position.
    */
   _int seek(_int pos);
};

