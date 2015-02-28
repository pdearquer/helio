/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Pointer into a window.
 * Pointer to a character into a window.
 *
 * Static object.
 */
class WindowPointer :
      public virtual Object
{
   friend class Window;
   friend class WritableWindow;
   
protected:
   /**
    * Reference to the window.
    */  
   Window *_win;
   
   /**
    * Pointer index into the window.
    */
   _int _index;
   

   /**
    * Create a pointer reference.
    */
   WindowPointer(Window *win, _int index);
   
public:
   /**
    * Copy constructor.    
    */
   WindowPointer(const WindowPointer &other);
   
   /**
    * Remove the pointer.
    */
   ~WindowPointer();
   
   
   /**
    * Move the pointer a number of characters (positive or negative).
    */ 
   void move(const _int chars);
   
   /**
    * Move to other pointer position.
    */
   void move(const WindowPointer &other);
   
   /**
    * Move to the start of the window.
    */
   void start();
   
   /**
    * Move to the end of the window.
    */
   void end();
   
   
   /**
    * Calculate the difference (positive or negative) with other pointer.
    * Negative means that the other pointer is behind this.
    */
   _int diff(const WindowPointer &other) const;
   
   
   /**
    * Asignment operator. Copy the position of the other pointer.
    */
   WindowPointer &operator =(const WindowPointer &other);
   
   /**
    * Moves by operators.
    */
   WindowPointer operator +(const _int chars) const;
   WindowPointer operator -(const _int chars) const;
   WindowPointer &operator ++();
   WindowPointer operator ++(int);
   WindowPointer &operator --();
   WindowPointer operator --(int);
   WindowPointer &operator +=(const _int b);
   WindowPointer &operator -=(const _int b);

   /**
    * Pointers comparison.
    */
   _bool operator ==(const WindowPointer &other) const;
   _bool operator !=(const WindowPointer &other) const;
   _bool operator <(const WindowPointer &other) const;
   _bool operator >(const WindowPointer &other) const;
   _bool operator <=(const WindowPointer &other) const;
   _bool operator >=(const WindowPointer &other) const;
   
   
   /**
    * Create a new pointer in the same position that this.
    */
   WindowPointer dup() const;   
};

