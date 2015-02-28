/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Processing window over a StringBuffer.
 * Allows parsing a StringBuffer using a Window.
 * Implements a read-only window over a copy of the string.
 * It is always recommended to use BufferWindow instead
 * to avoid copies and control better the buffer.
 */
class StringWindow : 
      public virtual Window
{
   /**
    * Processing string.
    */
   StringBuffer _str;
   
   /**
    * Current position of the start pointer.
    */
   _int _position;

   
public:
   /**
    * Prepare a window over the whole string.
    */
   StringWindow(const StringBuffer &str);
   
   /**
    * Prepare a window over a piece of the string.
    */
   StringWindow(const StringBuffer &str, _int start, _int length);
   
   
   /**
    * Get a copy of the window from and to the given pointers in a buffer.
    * The result pointer is not modified.
    */
   virtual Buffer *get(const WindowPointer &from, const WindowPointer &to);
   using Window::get;
   
   
   /**
    * Get a copy of the complete the proccessing string.
    */
   virtual String getStringCopy();
   
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
};

