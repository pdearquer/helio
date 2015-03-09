/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Text string
 * Character string intended for read access only.
 * To handle or edit character sequences use Buffer instead
 * (from Storage::Structure::Text).
 *
 * Static object.
 */
class String : 
      public virtual StaticObject, public virtual Cloneable,
      public virtual Orderable<String>, public virtual Hashable<String>
{
   friend class Storage::Structure::Text::Buffer;
   
protected:   
   /**
    * String data encoded in UTF-8.
    */
   _uint8 *_value;
   
   /**
    * String length in characters.
    */
   _int _length;
   
   /**
    * Number of bytes used.
    * Note that the data will be (_bytes + 1) long to allow the '\0' tail.
    * In case of 0 bytes (0 characters) no allocation is done (_data = null).
    */
   _int _bytes;
   
   
public:    
   /**
    * Create an empty storing.
    */
   String();
   
   /**
    * Copy constructor.
    */
   String(const String &other);
   
   /**
    * Copy constructor.
    */
   String(const String *other);

   /**
    * Create a string from a UTF-8 character array with the given length.
    * @param lenght Number of characters (not bytes) to copy.
    */
   String(const _uint8 *utf8, _int length);
   
   /**
    * Create a String from a buffer of characters.
    */
   String(const Storage::Structure::Text::Buffer *buf);
   
   /**
    * Create a String from a buffer of characters.
    */
   String(const Storage::Structure::Text::StringBuffer &buf);
   
   /**
    * Create a string from a native ASCII character array.
    */
   String(const char *ascii);
   
   /**
    * Create a string from a single character.
    */
   explicit String(const Character &c);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Create a string from a standard character.
    */
   explicit String(_char ch);
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Create a string from a native character.
    */
   explicit String(char ascii);
#endif

   /**
    * Create a string from any stringable object.
    */
   explicit String(const Object &o);

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Create a string from a standard integer.
    */
   explicit String(_int num);
#endif
   
#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Create a string from a native integer.
    */
   explicit String(int num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Create a string from a standard float.
    */
   explicit String(_float num);
#endif
   
#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Create a string from a native float.
    */
   explicit String(double num);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Create a string from a standard boolean.
    */
   explicit String(_bool b);
#endif
   
#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Create a string from a native boolean.
    */
   explicit String(bool b);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Create a string from a standard pointer.
    */
   explicit String(_pointer p);
#endif
   
#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Create a string from a native pointer.
    */
   explicit String(void *p);
#endif
   
   /**
    * Realease the string.
    */
   virtual ~String();
   
   
   /**
    * Gets the string length in characters.
    */
   _int length() const;
   
   /**
    * Gets the string length in characters.
    */
   _int count() const;
   
   /**
    * Says if the string has no character at all.
    */
   _bool isEmpty() const;
   
   /**
    * Returns the character at the given position.
    */
   _char get(_int index) const;
   
   
   /**
    * Compare to other element.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const String *other) const;

   /**
    * Compare to other string ignoring the case if required.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   _int compare(const String &other, _bool igncase = false) const;
   
   /**
    * Compare itself with another string.
    * Return true if the text is similar.
    */
   virtual _bool equals(const String *other) const;

   /**
    * Compare itself with another string ignoring the case if required.
    * Return true if the text is similar.
    */
   _bool equals(const String &other, _bool igncase = false) const;
   
   /**
    * Makes a copy of the object.
    */
   virtual String *clone() const;

   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;

   /**
    * Returns a buffer with a copy of the character sequence.
    */
   Text::Buffer *toBuffer() const;
   

   /**
    * Create the sub string between the start and the given end.
    * @param length Number of characters to pick up.
    *    If length is 0, returns all the string until the end of the string.
    *    If length is negative, returns all the string to the end less given length.
    */
   String sub(_int length) const;
   
   /**
    * Create the sub string between the given limits.
    * @param start The index of the first character included.
    * @param length Number of characters to pick up.
    *    If length is 0, returns all the string until the end of the string.
    *    If length is negative, returns all the string to the end less given length.
    */
   String sub(_int start, _int length) const;
 
 
   /**
    * Returns a new string with all the characters converted to lower case.
    */
   String toLowerCase() const;
   
   /**
    * Returns a new string with all the characters converted to upper case.
    */
   String toUpperCase() const;
      
   
   /**
    * Returns the position of a character starting in the indicated position.
    * Returns -1 if the character isn't in this string.
    * A negative start value means from the end (-1 means last character).
    */
   _int indexOf(_char c, _int start = 0) const;

   /**
    * Returns the position of a string starting from the indicated position.
    * Returns -1 if the string can't be found in this string.
    * A negative start value means from the end (-1 means last character).    
    */
   _int indexOf(const String &s, _int start = 0) const;
   
   
   /**
    * Returns the position of the last appearance of a character starting from
    * the indicated position.
    * Returns -1 if the character isn't in this string.
    * A negative start value means from the end (-1 means last character).
    */
   _int lastIndexOf(_char c, _int start = -1) const;

   /**
    * Returns the position of the last appearance of a string starting from the
    * indicated position.
    * Returns -1 if the string can't be found in this string.
    * A negative start value means from the end (-1 means last character).  
    */
   _int lastIndexOf(const String &s, _int start = -1) const;
   
   
   /**
    * Checks if the string starts with a prefix.
    */
   _bool startsWith(_char c) const;

   /**
    * Checks if the string starts with a prefix.
    */
   _bool startsWith(const String &s) const;
 
   /**
    * Checks if the string ends with a sufix.
    */
   _bool endsWith(_char c) const;

   /**
    * Checks if the string ends with a sufix.
    */
   _bool endsWith(const String &s) const;


   /**
    * Assignment operator.
    * Note that this operator should not be implemented because this
    * is a read-only data type. However it was allowed for late initialization.
    */
   void operator =(const String &other);

   /**
    * Assignment operator.
    * Note that this operator should not be implemented because this
    * is a read-only data type. However it was allowed for late initialization.
    */
   void operator =(const char *ascii);


   /**
    * Index operator (read only).
    */
   const Character operator [](const _int index) const;
   
   
   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const String &other) const;

   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const String &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const String &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const String &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const String &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const String &other) const;
   
   
   /**
    * Comparison operator for native type; Equal.
    */
   _bool operator ==(const char *ascii) const;
   
   /**
    * Comparison operator for native type; Unequal.
    */
   _bool operator !=(const char *ascii) const;

   /**
    * Comparison operator for native type; Less than.
    */
   _bool operator <(const char *ascii) const;

   /**
    * Comparison operator for native type; Greater than.
    */
   _bool operator >(const char *ascii) const;

   /**
    * Comparison operator for native type; Less than or equal to.
    */
   _bool operator <=(const char *ascii) const;

   /**
    * Comparison operator for native type; Greater than or equal to.
    */
   _bool operator >=(const char *ascii) const;
   
   
   /**
    * Returns a constant UTF-8 encoded representation (internal).
    */
   const _uint8 *getUTF8() const;
};

