/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Temporary character string.
 * Character sequence based on Text::Buffer that allows text manipulation
 * on an static object (using operators).
 *
 * This class is intended for one unique purpose; String creation. It
 * implements an extensive addition operator to allow a behaviour like this:
 *   String text = "name = " + name + ", age = " + age;
 *
 * TODO: Reimplement using an UTF-8 buffer, which has a quick concatenation.
 * Static object.
 */
class StringBuffer : 
      public virtual StaticObject, public virtual Buffer
{
public:
   /**
    * Create an empty buffer with default capacity.
    */
   StringBuffer();

   /**
    * Copy constructor.
    */
   StringBuffer(const StringBuffer &other);
   
   /**
    * Create a buffer with initial data.
    */
   StringBuffer(const Buffer *buf);

   /**
    * Create a buffer with initial data.
    */
   StringBuffer(const __char *data, _int len);
   
   /**
    * Create a buffer from a String.
    */
   StringBuffer(const String &str);
   
   /**
    * Create a buffer from a native ASCII character array.
    */
   StringBuffer(const char *ascii);
   
   /**
    * Create a buffer from a single character.
    */
   explicit StringBuffer(const Character &c);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Create a buffer from a standard character.
    */
   explicit StringBuffer(_char c);
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Create a buffer from a native character.
    */
   explicit StringBuffer(char ascii);
#endif

   /**
    * Create a buffer from any stringable object.
    */
   explicit StringBuffer(const Object &o);

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Create a buffer from a standard integer.
    */
   explicit StringBuffer(_int num);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Create a buffer from a native integer.
    */
   explicit StringBuffer(int num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Create a string from a standard float.
    */
   explicit StringBuffer(_float num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Create a buffer from a native float.
    */
   explicit StringBuffer(double num);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Create a buffer from a standard boolean.
    */
   explicit StringBuffer(_bool b);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Create a buffer from a native boolean.
    */
   explicit StringBuffer(bool b);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Create a buffer from a standard pointer.
    */
   explicit StringBuffer(_pointer p);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Create a buffer from a native pointer.
    */
   explicit StringBuffer(void *p);
#endif

   
   /**
    * Returns a piece of the buffer.
    * @param length Number of characters to pick up.
    *    If length is 0, returns all the string to the end.
    *    If length is negative, returns all the string to the end less length given.
    */
   StringBuffer sub(_int length) const;
   
   /**
    * Returns a piece of the buffer.
    * @param start The index of the first character included.
    * @param length Number of characters to pick up.
    *    If length is 0, returns all the string to the end.
    *    If length is negative, returns all the string to the end less length given.
    */
   StringBuffer sub(_int start, _int length) const;
   
   
   /**
    * Assignment operator from another buffer.
    */
   void operator =(const StringBuffer &other);
   
   /**
    * Assignment operator from a native ASCII character array.
    */
   void operator =(const char *ascii);

   
   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const StringBuffer &other) const;

   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const StringBuffer &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const StringBuffer &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const StringBuffer &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const StringBuffer &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const StringBuffer &other) const;


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
    * Addition and assignment operator for another StringBuffer.
    */
   void operator +=(const StringBuffer &other);

   /**
    * Addition and assignment operator for String.
    */
   void operator +=(const String &str);

   /**
    * Addition and assignment operator for native ASCII character array.
    */
   void operator +=(const char *ascii);

   /**
    * Addition and assignment operator for a static character.
    */
   void operator +=(const Character &c);

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Addition and assignment operator for a standard character.
    */
   void operator +=(_char ch);
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Addition and assignment operator for a native character.
    */
   void operator +=(char ascii);
#endif

   /**
    * Addition and assignment operator for a stringable object.
    */
   void operator +=(const Object &o);

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Addition and assignment operator for a standard integer.
    */
   void operator +=(_int num);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Addition and assignment operator for a native integer.
    */
   void operator +=(int num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Addition and assignment operator for a standard float.
    */
   void operator +=(_float num);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Addition and assignment operator for a native float.
    */
   void operator +=(double num);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Addition and assignment operator for a standard boolean.
    */
   void operator +=(_bool b);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Addition and assignment operator for a native boolean.
    */
   void operator +=(bool b);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Addition and assignment operator for a standard pointer.
    */
   void operator +=(_pointer p);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Addition and assignment operator for a native pointer.
    */
   void operator +=(void *p);
#endif


   /**
    * Addition operator for another StringBuffer.
    */
   const StringBuffer operator +(const StringBuffer &other) const;

   /**
    * Addition operator for String.
    */
   const StringBuffer operator +(const String &str) const;

   /**
    * Addition operator for native ASCII character array.
    */
   const StringBuffer operator +(const char *ascii) const;

   /**
    * Addition operator for a static character.
    */
   const StringBuffer operator +(const Character &c) const;

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Addition operator for a standard character.
    */
   const StringBuffer operator +(_char ch) const;
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Addition operator for a native character.
    */
   const StringBuffer operator +(char ascii) const;
#endif

   /**
    * Addition operator for a stringable object.
    */
   const StringBuffer operator +(const Object &o) const;

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Addition operator for a standard integer.
    */
   const StringBuffer operator +(_int num) const;
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Addition operator for a native integer.
    */
   const StringBuffer operator +(int num) const;
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Addition operator for a standard float.
    */
   const StringBuffer operator +(_float num) const;
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Addition operator for a native float.
    */
   const StringBuffer operator +(double num) const;
#endif

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Addition operator for a standard boolean.
    */
   const StringBuffer operator +(_bool b) const;
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Addition operator for a native boolean.
    */
   const StringBuffer operator +(bool b) const;
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Addition operator for a standard pointer.
    */
   const StringBuffer operator +(_pointer p) const;
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Addition operator for a native pointer.
    */
   const StringBuffer operator +(void *p) const;
#endif

};

