/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Processing window from an input to an output.
 * Window that gets characters from an input, store them in a buffer,
 * proccess them and send the result to an output.
 */
class ProcessWindow : 
      public virtual WritableWindow
{
protected:
   /**
    * Character input.
    */
   Input *_in;
   
   /**
    * Character output.
    */
   Output *_out;
   
   /**
    * Characters buffer.
    */
   Buffer _buffer;
   
   /**
    * If has been riched the end of the input.
    */
   _bool _finish;
   
   /**
    * Reading step.
    */
   _int _step;
   
   
public:
   /**
    * Prepare a window over the input.
    */
   ProcessWindow(Input *in, Output *out, _int step = 128);
   
   
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
    * Returns true if the end pointer is in the last character to proccess.
    */
   virtual _bool hasFinished();
   using Window::hasFinished;
   
   
   /**
    * Gets the number of characters to read in each step.
    */
   _int step();
   
   /**
    * Sets the number of characters to read in each step.
    */
   _int step(_int step);
   
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

