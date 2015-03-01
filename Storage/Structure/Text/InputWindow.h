/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Moving window from an input.
 * Keep a moving buffer over a character input.
 */
class InputWindow : 
      public virtual Window
{
protected:
   /**
    * Character input.
    */
   Input *_in;
   
   /**
    * Characters buffer.
    */
   Buffer _buffer;
   
   /**
    * If has been reached the end of the input.
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
   InputWindow(Input *in, _int step = 128);
   
   
   /**
    * Get a copy of the window from and to the given pointers in a buffer.
    * The result pointer is not modified.
    */
   virtual Buffer *get(const WindowPointer &from, const WindowPointer &to);
   using Window::get;


   /**
    * Returns true if the end pointer is in the last character to process.
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
};

