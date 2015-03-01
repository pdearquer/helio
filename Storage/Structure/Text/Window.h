/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Characters processing window.
 * Allows process a window of characters from a String, Buffer or characters Input.
 * Create a length variable window work that moves when the characters are 
 * processed (always forwards).
 * There are at least two pointers in the window: start and end. You can
 * create others but they are always within this two.
 *
 * TODO: Set limits
 */
class Window :
      public virtual Object
{
   friend class WindowPointer;
   
public:
   /**
    * Start pointer, begin of the window.
    * No pointer can be behind this.
    * This pointer can not move backwards
    */
   static_const_int POINTER_START = 0;
   
   /**
    * End pointer, finish of the window.
    * No pointer can be beyond this, so this pointer moves when required.
    */
   static_const_int POINTER_END = 1;
   
   /**
    * Result pointer, store the last operation result.
    */
   static_const_int POINTER_RESULT = 2;
   
   
   /**
    * String containing all the number characters.
    */
   static_const_String NUMBER = "0123456789";
   
   /**

    * String containing all the alphabetic characters (whether upper or lower case).
    */
   static_const_String ALPHA = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   
   /**
    * String containing all the alphabetic and number characters.
    */
   static_const_String ALPHANUMERIC = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "0123456789";
   
   /**
    * String containing all the upper-case alphabetic characters.
    */
   static_const_String UPPER_ALPHA = "abcdefghijklmnopqrstuvwxyz";
   
   /**
    * String containing all the lower-case alphabetic characters.
    */
   static_const_String LOWER_ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   
   
protected:
   /**
    * Vector storing the pointers positions.
    */
   Storage::Structure::Vector<_int> _pointers;
   
   /**
    * Number of references of each pointer.
    */
   Storage::Structure::Vector<_int> _refs;

   /**
    * Current status of the start pointer.
    */
   WindowStatus status;

 
   /**
    * Initialize the window.
    */
   Window();
   
   
public:      
   /**
    * Returns a reference to the start pointer.
    */
   WindowPointer start();
   
   /**
    * Returns a reference to the end pointer.
    */
   WindowPointer end();

   /**
    * Returns a reference to the results pointer.
    */
   WindowPointer result();
   
   /**
    * Gets a pointer of the window.
    */
   WindowPointer pointer(_int index);
   
   /**
    * Returns the number of pointers.
    */
   _int pointersCount();
   
   
   /**
    * Window length in characters (from start to end).
    */
   _int length();
   
   
   /**
    * Returns the character at the pointer.
    */
   virtual _char getChar(const WindowPointer &p);
    
   
   /**
    * Get a copy of the window in a buffer.
    * The result pointer is not modified.
    */
   virtual Buffer *get();
   
   /**
    * Get a copy of the window from the start to the given pointer in a buffer.
    * The result pointer is not modified.
    */
   virtual Buffer *get(const WindowPointer &to);
   
   /**
    * Get a copy of the window from and to the given pointers in a buffer.
    * The result pointer is not modified.
    */
   virtual Buffer *get(const WindowPointer &from, const WindowPointer &to);

   /**
    * Get a copy of the window in a string.
    * The result pointer is not modified.
    */
   virtual String getString();
   
   /**
    * Get a copy of the window from the start to the given pointer in a string.
    * The result pointer is not modified.
    */
   virtual String getString(const WindowPointer &to);
   
   /**
    * Get a copy of the window from and to the given pointers in a string.
    * The result pointer is not modified.
    */
   virtual String getString(const WindowPointer &from, const WindowPointer &to);

   /**
    * Check if the start points to this character.
    */
   _bool is(_char c, _bool igncase = false);
   
   /**
    * Check if the given pointer points to this character.
    */
   _bool is(_char c, const WindowPointer &p, _bool igncase = false);
   
   /**
    * Check if the start points to this string.
    */
   _bool is(const StringBuffer &s, _bool igncase = false);
   
   /**
    * Check if the given pointer points to this string.
    */
   _bool is(const StringBuffer &s, const WindowPointer &p, _bool igncase = false);
   

   /**
    * Check if the start points to any of the characters of the string.
    */
   _bool isAny(const StringBuffer &valid, _bool igncase = false);
   
   /**
    * Check if the given pointer points to any of the characters of the string.
    */
   _bool isAny(const StringBuffer &valid, const WindowPointer &p, _bool igncase = false);


   /**
    * Check if the start points to none of the characters of the string.
    */
   _bool isNone(const StringBuffer &invalid, _bool igncase = false);
   
   /**
    * Check if the given pointer points to none of the characers of the string.
    */
   _bool isNone(const StringBuffer &invalid, const WindowPointer &p, _bool igncase = false);
   

   /**
    * Look ahead for a character.
    * If success returns true and store the character position in the result pointer.
    * The window may grow up until find it or to the limit..
    */
   _bool find(_char c);
   
   /**
    * Look ahead for a character starting in the pointer.
    * If success returns true and store the character position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool find(_char c, const WindowPointer &from);
   
   /**
    * Look ahead for a character between the pointers.
    * If success returns true and store the character position in the result pointer.
    */
   _bool find(_char c, const WindowPointer &from, const WindowPointer &to);
   
   
   /**
    * Look ahead for a string.
    * If success returns true and store the string start position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool find(const StringBuffer &s);
   
   /**
    * Look ahead for a string starting in the pointer.
    * If success returns true and store the string start position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool find(const StringBuffer &s, const WindowPointer &from);
   
   /**
    * Look ahead for a string between the pointers.
    * If success returns true and store the string start position in the result pointer.
    */
   _bool find(const StringBuffer &s, const WindowPointer &from, const WindowPointer &to);
   
   
   /**
    * Look ahead for any of the characters contained in the string.
    * If success returns true and store the character position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool findAny(const StringBuffer &valid);
   
   /**
    * Look ahead for any of the characters contained in the string starting in
    * the pointer.
    * If success returns true and store the character position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool findAny(const StringBuffer &valid, const WindowPointer &from);
   
   /**
    * Look ahead for any of the strings contained in the vector.
    * If success returns true and store the string start position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   //_bool findAny(const Vector<String> &valid);
      
   
   /**
    * Look ahead for any character NOT contained in the string.
    * If success returns true and store the character position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool findNone(const StringBuffer &invalid);
   
   /**
    * Look ahead for any character NOT contained in the string starting in
    * the pointer.
    * If success returns true and store the character position in the result pointer.
    * The window may grow up until find it or to the limit.
    */
   _bool findNone(const StringBuffer &invalid, const WindowPointer &from);
      
   /**
    * Look ahead for any strings NOT contained in the vector.
    * If success returns true and store the string start position in the result pointer.
    * The window may grow up until find it or to the limit.
    * Note that overlapping is not consider, that means that the invalid strings "abc"
    * and "abcdef" could fail processing "abcdef" ("abc" found and "def" not).
    */
   //_bool findNone(const Vector<String> &invalid);
   
   
   /**
    * Move the end pointer to the last character to process (or to the limit).
    */
   virtual void finish();
   
   /**
    * Returns true if the end pointer is in the last character to process.
    */

   virtual _bool hasFinished() = 0;
   
   /**
    * Returns true if the given pointer is in the last character to process.
    */
   virtual _bool hasFinished(const WindowPointer &p);
   
   
   /**
    * Returns the status descriptor of the pointer.
    */
   WindowStatus *getStatus(const WindowPointer &p);
   
   /**
    * Add the status description to the exception at a character.
    */
   void addStatus(Exception *ex, const WindowPointer &at);
   
   /**
    * Add the status description to the exception in an interval.
    */
   void addStatus(Exception *ex, const WindowPointer &from, const WindowPointer &to);
   
   
protected:
   /**
    * Returns the character at the pointer.
    */
   virtual _char getChar(_int position) = 0;
   
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
   virtual void moveEnd(_int chars) = 0;
   
   /**
    * Move the indicated pointer a number of characters (positive or negative).
    */
   void movePointer(_int index, _int chars);
   
   /**
    * Move a pointer to the others position.
    */
   void setPointer(_int index, _int other);
   
   /**
    * Returns the current position of a pointer.
    */
   _int getPointer(_int index);
   _int getPointer(const WindowPointer &p);
   
   /**
    * Create a new pointer copy of other.
    */
   _int copyPointer(_int index);
   
   
   /**
    * Indicates that there is a new reference to the pointer.
    */
   void addRef(_int index);
   
   /**
    * Indicates that one reference has been deleted to the pointer.
    */
   void removeRef(_int index);
};

