/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Character store
 * Character representation.
 *
 * Static object.
 */
class Character : 
      public virtual Cloneable, public virtual Orderable<Character>,
      public virtual Hashable<Character>
{
protected:
   /**
    * Character representation in UTF32.
    */
   __char _value;
   
   
public:
   /**
    * Create a null character.
    */   
   Character();
   
   /**
    * Copy constructor.
    */   
   Character(const Character &other);
   
   /**
    * Copy constructor.
    */   
   Character(const Character *other);
   
#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Initialize from a standard value.
    */
   Character(_char value);
#endif   
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Initialize from a native value.
    */
   Character(char value);
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_INTERNAL
   /**
    * Initialize from an internal value.
    */
   Character(__char value);
#endif

   
   /**
    * Return the value of the character.
    */
   virtual Character get() const;
   
   /**
    * Set the value of the character.
    */
   virtual void set(const Character &other);
   
   
   /**
    * Say if it is a valid Unicode character
    */
   static _bool isValid(__char utf32);
   
   /**
    * Returns the ASCII representation of the character.
    */
   virtual _uint8 getAscii() const;
   
   /**
    * Set the charater from its ASCII representation.
    */
   virtual void setAscii(_uint8 ascii);
   
   /**
    * Gets the character in UTF-16.
    */
   virtual _uint16 getUtf16() const;
   
   /**
    * Sets the character in UTF-16.
    */
   virtual void setUtf16(_uint16 utf16);
   
   /**
    * Gets the character in UTF-32.
    */
   virtual _uint32 getUtf32() const;
   
   /**
    * Sets the character in UTF-32.
    */
   virtual void setUtf32(_uint32 utf32);
   
   
   /**
    * Says if this character is lower case.
    */
   virtual _bool isLowerCase() const;
   
   /**
    * Says if this character is upper case.
    */
   virtual _bool isUpperCase() const;
   
   /**
    * Returns the lower case character of this (not modifying this).
    */
   virtual Character toLowerCase() const;
   
   /**
    * Returns the upper case character of this (not modifying this).
    */
   virtual Character toUpperCase() const;
   
   
   /**
    * Compare to other character.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Character *other) const;

   /**
    * Compare to other character ignoring the case if required.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Character &other, _bool igncase = false) const;
#ifndef __HELIO_TYPE_CHAR_IS_STATIC
   /**
    * Compare to other character ignoring the case if required.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(_char other, _bool igncase = false) const;
#endif
   
   /**
    * Compare itself with another character.
    * Return true if the value is the same.
    */
   virtual _bool equals(const Character *other) const;

   /**
    * Compare itself with another character ignoring the case if required.
    * Return true if the value is the same.
    */
   virtual _bool equals(const Character &other, _bool igncase = false) const;
#ifndef __HELIO_TYPE_CHAR_IS_STATIC
   /**
    * Compare itself with another character ignoring the case if required.
    * Return true if the value is the same.
    */
   virtual _bool equals(_char other, _bool igncase = false) const;
#endif
   
   /**
    * Makes a copy of the object.
    */
   virtual Character *clone() const;

   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;


   /**
    * Generate a human readable string representing the character.
    */
   virtual String toString() const;
   

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Operator cast to standard.
    */
   operator _char() const;
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Operator cast to navite.
    */
   operator char() const;
#endif   

#ifndef __HELIO_TYPE_CHAR_IS_INTERNAL
   /**
    * Operator cast to internal.
    */
   explicit operator __char() const;
#endif
   
   
   /**
    * Assignment operator. Copy other into this.
    */
   void operator =(const Character &other);
   
#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Assignment operator from standard type.
    */
   void operator =(_char other);
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Assignment operator from native type.
    */
   void operator =(char other);
#endif   

#ifndef __HELIO_TYPE_CHAR_IS_INTERNAL
   /**
    * Assignment operator from internal type.
    */
   void operator =(__char other);
#endif
   

   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const Character &other) const;

   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const Character &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const Character &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const Character &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const Character &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const Character &other) const;


#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
   /**
    * Comparison operator for standard type; Equal.
    */
   _bool operator ==(_char other) const;

   /**
    * Comparison operator for standard type; Unequal.
    */
   _bool operator !=(_char other) const;

   /**
    * Comparison operator for standard type; Less than.
    */
   _bool operator <(_char other) const;

   /**
    * Comparison operator for standard type; Greater than.
    */
   _bool operator >(_char other) const;

   /**
    * Comparison operator for standard type; Less than or equal to.
    */
   _bool operator <=(_char other) const;

   /**
    * Comparison operator for standard type; Greater than or equal to.
    */
   _bool operator >=(_char other) const;
#endif
#endif

#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
   /**
    * Comparison operator for native type; Equal.
    */
   _bool operator ==(char other) const;

   /**
    * Comparison operator for native type; Unequal.
    */
   _bool operator !=(char other) const;

   /**
    * Comparison operator for native type; Less than.
    */
   _bool operator <(char other) const;

   /**
    * Comparison operator for native type; Greater than.
    */
   _bool operator >(char other) const;

   /**
    * Comparison operator for native type; Less than or equal to.
    */
   _bool operator <=(char other) const;

   /**
    * Comparison operator for native type; Greater than or equal to.
    */
   _bool operator >=(char other) const;
#endif

};

