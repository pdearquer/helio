/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Buffer of characters.
 * Similar to String but with faster performance (no internal encoding).
 * Note that this buffer can contain '\0' characters inside.
 */
class Buffer : 
      public virtual Comparable<Buffer>
{
   friend class String;
   
protected:
   /**
    * Defines the default minimum capacity in constructors.
    */
   static_const_int MIN_CAPACITY = 16;


   /**
    * Array of UTF-32 (target endianess) characters.
    */
   __char *_data;
   
   /**
    * Number of characters in the buffer.
    */
   _int _length;
   
   /**
    * Buffer capacity.
    */
   _int _capacity;
   
   
public:
   /**
    * Creates an empty buffer of the default capacity.
    */
   Buffer();
   
   /**
    * Creates an empty buffer of the given initial capacity.
    * Overrides the default MIN_CAPACITY.
    */
   Buffer(_int cap);
   
   /**
    * Makes a buffer copy.
    */
   Buffer(const Buffer *other);

   /**
    * Create a buffer with initial data.
    */
   Buffer(const __char *data, _int len);
   
   /**
    * Creates a buffer with initial data and sets the capacity.
    * Overrides the default MIN_CAPACITY.
    */
   Buffer(const __char *data, _int len, _int cap);
   
   /**
    * Creates a buffer from a String.
    */
   Buffer(const String &str);

   /**
    * Creates a buffer from a single character.
    * Uses a capacity of 1, this is an optimization for character handling.
    */
   Buffer(_char ch);
   
   /**
    * Releases the buffer.
    */
   ~Buffer();
   
      
   /**
    * Returns the number of characters stored.
    */
   _int length() const;

   /**
    * Returns the number of characters stored.
    */
   _int count() const;
   
   /**
    * Sets the number of characters stored.
    * Remove the remaining or fill with zeros if higher!
    */
   void setLength(_int len);

   /**
   * Sets the number of characters stored.
   * Remove the remaining or fill with zeros if higher!
   */
   void setCount(_int len);

   /**
    * Says if the buffer contains no character.
    */
   _bool empty() const;   
   
   /**
    * Removes all bytes (does not reduce capacity).
    */
   void clear();
   
   /**
    * Returns true if the buffer has any null character.
    */
   _bool hasNull();   
   
   /**
    * Gets current capacity.
    */
   _int capacity() const;
   
   /**
    * Sets the capacity (could lose data).
    */
   void setCapacity(_int cap);
   
   
   /**
    * Gets a character from the buffer.
    */
   _char get(_int index) const;
   
   /**
    * Index operator (read only).
    */
   const _char operator [](_int index) const;
   
   /**
    * Sets a character in the buffer.
    */
   void set(_int index, _char c);

   /**
    * Sets some characters in the buffer from a string.
    * The current length cannot be exceeded.
    */
   void set(_int index, const String &s);
      
   /**
    * Sets some characters in the buffer from another buffer.
    * The current length cannot be exceeded.
    */
   void set(_int index, const Buffer *b);
   
   /**
    * Gets or sets a raw character in the buffer.
    */
   __char &operator [](_int index);
   
   
   /**
    * Returns the position of a character starting in the indicated position.
    * Returns -1 if the character isn't in this buffer.
    * A negative start value means from the end (-1 means last character).
    */
   _int indexOf(_char c, _int start = 0) const;
   
   /**
    * Returns the position of a string starting from the indicated position.
    * Returns -1 if the string can't be found in this buffer.
    * A negative start value means from the end (-1 means last character).
    */
   _int indexOf(const String &s, _int start = 0) const;
   
   /**
    * Returns the position of a buffer starting from the indicated position.
    * Returns -1 if the buffer can't be found in this buffer.
    * A negative start value means from the end (-1 means last character).
    */
   _int indexOf(const Buffer *b, _int start = 0) const;
   
   
   /**
    * Returns the position of the last appearance of a character starting from
    * the indicated position.
    * Returns -1 if the character isn't in this buffer.
    * A negative start value means from the end (-1 means last character).  
    */
   _int lastIndexOf(_char c, _int start = -1) const;
   
   /**
    * Returns the position of the last appearance of a string starting from the
    * indicated position.
    * Returns -1 if the string can't be found in this buffer.
    * A negative start value means from the end (-1 means last character).  
    */
   _int lastIndexOf(const String &s, _int start = -1) const;
   
   /**
    * Returns the position of the last appearance of a buffer starting from the
    * indicated position.
    * Returns -1 if the buffer can't be found in this buffer.
    * A negative start value means from the end (-1 means last character).  
    */
   _int lastIndexOf(const Buffer *b, _int start = -1) const;
   
   
   /**
    * Check if the string starts with a prefix.
    */
   _bool startsWith(_char c) const;
   
   /**
    * Check if the string starts with a prefix.
    */
   _bool startsWith(const String &s) const;
   
   /**
    * Check if the string starts with a prefix.
    */
   _bool startsWith(const Buffer *b) const;
 
   /**
    * Check if the string ends with a sufix.
    */
   _bool endsWith(_char c) const;
   
   /**
    * Check if the string ends with a sufix.
    */
   _bool endsWith(const String &s) const;
   
   /**
    * Check if the string ends with a sufix.
    */
   _bool endsWith(const Buffer *b) const;
   
   
   /**
    * Adds some characters to the end of this buffer.
    */
   void add(const __char *data, _int len);
   
   /**
    * Adds some characters from another buffer to the end of this.
    */
   void add(const Buffer *b);
   
   /**
    * Adds some characters from another buffer to the end of this.
    * Starts copying from the given position (always adds to the end).
    */
   void add(const Buffer *b, _int count, _int start);
   
   /**
    * Adds a character to the end of buffer.
    */
   void add(const Character &c);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Adds a standard character to the end of this buffer.
    */
   void add(_char c);
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Adds a native character to the end of this buffer.
    */
   void add(char c);
#endif
   
   /**
    * Adds a string to the end of buffer this buffer.
    */
   void add(const String &str);
   
   /**
    * Adds a string to the end of buffer this buffer.
    */
   void add(const StringBuffer &str);
   
   /**
    * Adds a native array of characters to the end of this buffer.
    */
   void add(const char *ascii);

   /**
    * Adds characters from another buffer into this.
    * @param start Is the character index in this buffer where place the first byte.
    * The difference with set() is that this method allows growth.
    */
   void add(_int start, const Buffer *b);
   
   /**
    * Adds characters from another buffer into this.
    * @param start Is the character index in this buffer where place the first byte.
    * The difference with set() is that this method allows growth.
    */
   void add(_int start, const Buffer *b, _int count);
   
   /**
    * Adds characters from another buffer into this.
    * @param start Is the character index in this buffer where place the first byte.
    * @param start2 Is the character index in b where get the first byte.
    * The difference with set() is that this method allows growth.
    */
   void add(_int start, const Buffer *b, _int count, _int start2);
   
   
   /**
    * Returns a piece of the buffer from the beginning.
    * @param length Number of characters to pick up.
    *    If length is 0, returns all the string until the end of the buffer.
    *    If length is negative, returns all the string until the end minus the given length.
    */
   Buffer *sub(_int length) const;
   
   /**
    * Returns a piece of the buffer.
    * @param start The index of the first character included.
    * @param length Number of characters to pick up.
    *    If length is 0, returns all the string until the end of the buffer.
    *    If length is negative, returns all the string until the end minus the given length.
    */
   Buffer *sub(_int start, _int length) const;

   
   /**
    * Moves the buffer a number of characters (positive ahead and negative backwards).
    * Fills with nulls.
    */
   void move(_int count);
         
   /**
    * Discards some characters in the buffer shortening the length.
    * If count is negative a hole of abs(count) null characters is made at index.
    */
   void erase(_int index, _int count);
   
   
   /**
    * Inserts a character in the buffer shifting the tail.
    * It can discard a given number of characters from the index
    * (eg if discard is 1 this method equals to set).
    */
   void insert(_int index, _char c, _int discard = 0);
   
   /**
    * Inserts a string in the buffer shifting the tail.
    * It can discard a given number of characters from the index
    * (eg if discard is the string length this method equals to set).
    */
   void insert(_int index, const String &s, _int discard = 0);
   
   /**
    * Inserts other buffer in this buffer shifting the tail.
    * It can discard a given number of characters from the index
    * (eg if discard is the other buffer length this method equals to set).
    * NOTE: If trying to insert itself, a copy is done prior to the insertion.
    */
   void insert(_int index, const Buffer *b, _int discard = 0);
   
   
   /**
    * Looks for a character and replace all occurrences with another.
    * A negative start value means from the end (-1 means last character).
    */
   void replace(_char find, _char other, _int start = 0);
   
   /**
    * Looks for a string and replace all occurrences with another.
    * A negative start value means from the end (-1 means last character).
    */
   void replace(const String &find, const String &other, _int start = 0);
   
   /**
    * Looks for a buffer and replace all occurrences with another.
    * A negative start value means from the end (-1 means last character).
    * NOTE: If "find" or "other" is itself, a copy is done prior to the replacement.
    */
   void replace(const Buffer *find, const Buffer *other, _int start = 0);
   
   
   /**
    * Fills the buffer with a character from the right growing to a
    * minimum length.
    */
   void padRight(_int length, _char c);

   /**
    * Fills the buffer with a character from the left growing to a
    * minimum length.
    */
   void padLeft(_int length, _char c);
      
   /**
    * Reverse all the characters (first to last and last to first).
    */
   void reverse();

   
   /**
    * Compare to other buffer.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Buffer *other) const;
    
   /**
    * Compares itself with another buffer.
    */
   virtual _bool equals(const Buffer *other) const;
  
   /**
    * Encode the Buffer of characters in a String.
    */
   virtual String toString() const;
     

protected:
   /**
    * Returns the raw data buffer. Use with care!
    */
   __char *data();

   /**
    * Ensure a minimum capacity.
    */
   void ensureCap(_int min);
};

