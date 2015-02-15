/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Processing window that allows modify data.
 * Generic window that allows change characters while processing.
 */
class WritableWindow : 
      public virtual Window
{
public:
   /**
    * Sets the character at the pointer.
    */
   virtual void setChar(const WindowPointer &p, _char c) = 0;
   
   /**
    * Sets a string in the window overwriting other characters.
    * If the end is reached an exception is thrown (you may want to use insert).
    */
   void set(const WindowPointer &p, String s);
   
   
   /**
    * Inserts a character at the pointer.
    */
   void insert(_char c, const WindowPointer &p);
   
   /**
    * Inserts a character at the pointer.
    */
   void insert(const StringBuffer &s, const WindowPointer &p);
   
   /**
    * Erase some characters (including the pointed).
    */
   void erase(const WindowPointer &from, const WindowPointer &to);
      
   /**
    * Replace some characters for another (including the pointed).
    */
   void replace(_char c, const WindowPointer &from, const WindowPointer &to);

   /**
    * Replace some characters for a string (including the pointed).
    */
   void replace(const StringBuffer &s, const WindowPointer &from, const WindowPointer &to);
   
   
protected:
   /**
    * Adds (positive values) or removes (negative values) characters in the window.
    * New characters must be null.
    * This method only manage pointers, buffer implementation must be provide.
    */
   virtual void displace(const WindowPointer &p, _int chars);
};

