/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Processing window over a Buffer of characters.
 * Allows parsing a Buffer of characters using a Window.
 * This class does NOT create a buffer copy, uses the given (and does not delete it).
 */
class BufferWindow : 
      public virtual WritableWindow
{
   /**
    * Processing buffer.
    */
   Buffer *_buffer;
   
   /**
    * Current position of the start pointer.
    */
   _int _position;
   

public:
   /**
    * Prepare a window over the whole buffer (work over the given reference).
    */
   BufferWindow(Buffer *buf);
   
      
   /**
    * Sets the character at the pointer.
    */
   virtual void setChar(const WindowPointer &p, _char c);
   
   
   /**
    * Get a copy of the window from and to the given pointers in a buffer.
    * The result pointer is not modified.
    */
   virtual Buffer *get(const WindowPointer &from, const WindowPointer &to);
   using Window::get;
   
   
   /**
    * Recover the proccessing buffer reference (complete).
    */
   virtual Buffer *getBuffer();
   
   /**
    * Returns the absolute character position in the string.
    */
   virtual _int absolute(const WindowPointer &pos);   
   
   /**
    * Returns true if the end pointer is in the last character to proccess.
    */
   virtual _bool hasFinished();
   using Window::hasFinished;
   
protected:
   /**
    * Returns the character at the pointer.
    */
   virtual _char getChar(_int position);
   
   /**
    * Move the start pointer to the given position releasing characters if possible.
    * All pointers could need update and can change (when lag behind).
    * The pointer could move less characters if the end is reached.
    */
   virtual void moveStart(_int chars);
   
   /**
    * Move the end pointer to the given position allocating characters if necessary.
    * The pointer could move less characters if the end is reached.
    */
   virtual void moveEnd(_int chars);
   
   /**
    * Adds (positive values) or removes (negative values) characters in the window.
    * New characters must be null.
    * This method only manage pointers, buffer implementation must be provide.
    */
   virtual void displace(const WindowPointer &p, _int chars);
};

