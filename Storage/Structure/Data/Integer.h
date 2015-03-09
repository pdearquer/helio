/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Integer number
 * Signed integer number static implementation.
 *
 * Static object.
 */
class Integer :
      public virtual StaticObject, public virtual Cloneable,
      public virtual Orderable<Integer>, public virtual Hashable<Integer>,
      public virtual Number
{
public:
   /**
    * Minimum value.
    */
   static_const_int MIN = __HELIO_TYPE_INT_MIN;

   /**
    * Maximum value.
    */
   static_const_int MAX = __HELIO_TYPE_INT_MAX;


protected:
   /**
    * Actual value stored.
    */
   __int _value;
   

public:
   /**
    * Initialize to zero.
    */
   Integer();

   /**
    * Copy constructor.
    */
   Integer(const Integer &other);

   /**
    * Copy constructor.
    */
   Integer(const Integer *other);

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Initialize from a standard value.
    */
   Integer(_int value);
#endif
   
#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Initialize from a native value.
    */
   Integer(int value);
#endif

   /**
    * Initialize from size_t (sizeof).
    */
   explicit Integer(size_t value);
   
   /**
    * Initialize from a binary of 8 bits.
    */
   explicit Integer(_uint8 value);
   
   /**
    * Initialize from a binary of 16 bits.
    */
   explicit Integer(_uint16 value);
   
   /**
    * Initialize from a binary of 32 bits.
    */
   explicit Integer(_uint32 value);
   
   /**
    * Initialize from a binary of 64 bits.
    */
   explicit Integer(_uint64 value);
   
   /**
    * Initialize from a signed binary of 64 bits.
    */
   explicit Integer(__sint64 value);
   
   /**
    * Initialize from a float point number
    */
   explicit Integer(const Float &value);
   
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Initialize from a standard float point number
    */
   explicit Integer(_float value);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Initialize from a native float point number
    */
   explicit Integer(double value);
#endif


   /**
    * Return the value of the integer.
    */
   Integer get() const;
   
   /**
    * Set the value of the integer.
    */
   void set(const Integer &other);


   /**
    * Return the value of the number converted to integer.
    */
   virtual _int getInt() const;

   /**
    * Return the value of the number converted to float.
    */
   virtual _float getFloat() const;
   
   
   /**
    * Compare to other integer.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Integer *other) const;
   
   /**
    * Compare itself with another integer.
    * Return true if the value is the same.
    */
   virtual _bool equals(const Integer *other) const;
   
   /**
    * Makes a copy of the object.
    */
   virtual Integer *clone() const;
   
   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;


   /**
    * Generate a human readable string representing the number.
    */
   virtual String toString() const;

   
#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Operator cast to standard int.
    */
   operator _int() const;
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Operator cast to native int.
    */
   explicit operator int() const;
#endif

   /**
    * Operator cast to native size_t to allow expressions like:
    *   _int *a = new _int[b];
    */
   operator size_t() const;
   
   /**
    * Operator cast to binary of 8 bits.
    */
   explicit operator _uint8() const;
   
   /**
    * Operator cast to binary of 16 bits.
    */
   explicit operator _uint16() const;
   
   /**
    * Operator cast to binary of 32 bits.
    */
   explicit operator _uint32() const;
   
   /**
    * Operator cast to binary of 64 bits.
    */
   explicit operator _uint64() const;
   
   /**
    * Operator cast to signed binary of 64 bits.
    */
   explicit operator __sint64() const;
   
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC   
   /**
    * Operator cast to floating point number.
    */
   explicit operator _float() const;
#endif


   /**
    * Assignment operator. Copy other into this.
    */
   void operator =(const Integer &other);

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Assignment operator from standard int.
    */
   void operator =(_int other);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Assignment operator from native int.
    */
   void operator =(int other);
#endif

   /**
    * Assignment operator from sizeof().
    */
   void operator =(size_t other);
   
   
   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const Integer &other) const;

   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const Integer &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const Integer &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const Integer &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const Integer &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const Integer &other) const;


#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Comparison operator for standard int; Equal.
    */
   _bool operator ==(_int other) const;

   /**
    * Comparison operator for standard int; Unequal.
    */
   _bool operator !=(_int other) const;

   /**
    * Comparison operator for standard int; Less than.
    */
   _bool operator <(_int other) const;

   /**
    * Comparison operator for standard int; Greater than.
    */
   _bool operator >(_int other) const;

   /**
    * Comparison operator for standard int; Less than or equal to.
    */
   _bool operator <=(_int other) const;

   /**
    * Comparison operator for standard int; Greater than or equal to.
    */
   _bool operator >=(_int other) const;
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Comparison operator for native int; Equal.
    */
   _bool operator ==(int other) const;

   /**
    * Comparison operator for native int; Unequal.
    */
   _bool operator !=(int other) const;

   /**
    * Comparison operator for native int; Less than.
    */
   _bool operator <(int other) const;

   /**
    * Comparison operator for native int; Greater than.
    */
   _bool operator >(int other) const;

   /**
    * Comparison operator for native int; Less than or equal to.
    */
   _bool operator <=(int other) const;

   /**
    * Comparison operator for native int; Greater than or equal to.
    */
   _bool operator >=(int other) const;
#endif

   /**
    * Comparison operator for sizeof(); Equal.
    */
   _bool operator ==(size_t other) const;

   /**
    * Comparison operator for sizeof(); Unequal.
    */
   _bool operator !=(size_t other) const;

   /**
    * Comparison operator for sizeof(); Less than.
    */
   _bool operator <(size_t other) const;

   /**
    * Comparison operator for sizeof(); Greater than.
    */
   _bool operator >(size_t other) const;

   /**
    * Comparison operator for sizeof(); Less than or equal to.
    */
   _bool operator <=(size_t other) const;

   /**
    * Comparison operator for sizeof(); Greater than or equal to.
    */
   _bool operator >=(size_t other) const;
   

   /**
    * Addition and assignment operator.
    */
   void operator +=(const Integer &other);

   /**
    * Subtraction and assignment operator.
    */
   void operator -=(const Integer &other);

   /**
    * Multiplication and assignment operator.
    */
   void operator *=(const Integer &other);

   /**
    * Division and assignment operator.
    */
   void operator /=(const Integer &other);

   /**
    * Modulo and assignment operator.
    */
   void operator %=(const Integer &other);
   

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Addition and assignment operator with standard int.
    */
   void operator +=(_int other);
   
   /**
    * Subtraction and assignment operator with standard int.
    */
   void operator -=(_int other);
   
   /**
    * Multiplication and assignment operator with standard int.
    */
   void operator *=(_int other);
   
   /**
    * Division and assignment operator with standard int.
    */
   void operator /=(_int other);
   
   /**
    * Modulo and assignment operator with standard int.
    */
   void operator %=(_int other);
#endif


#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Addition and assignment operator with native int.
    */
   void operator +=(int other);
   
   /**
    * Subtraction and assignment operator with native int.
    */
   void operator -=(int other);
   
   /**
    * Multiplication and assignment operator with native int.
    */
   void operator *=(int other);
   
   /**
    * Division and assignment operator with native int.
    */
   void operator /=(int other);
   
   /**
    * Modulo and assignment operator with native int.
    */
   void operator %=(int other);
#endif

   /**
    * Addition and assignment operator with sizeof().
    */
   void operator +=(size_t other);
   
   /**
    * Subtraction and assignment operator with sizeof().
    */
   void operator -=(size_t other);
   
   /**
    * Multiplication and assignment operator with sizeof().
    */
   void operator *=(size_t other);
   
   /**
    * Division and assignment operator with sizeof().
    */
   void operator /=(size_t other);
   
   /**
    * Modulo and assignment operator with sizeof().
    */
   void operator %=(size_t other);
   

   /**
    * Increment postfix operator.
    */
   void operator ++(int);
   
   /**
    * Increment prefix operator.
    */
   void operator ++();

   /**
    * Decrement postfix operator.
    */
   void operator --(int);
   
   /**
    * Decrement prefix operator.
    */
   void operator --();
   
   /**
    * Inverse operator.
    */
   const Integer operator -() const;
   
   
   /**
    * Addition operator.
    */
   const Integer operator +(const Integer &other) const;

   /**
    * Subtraction operator.
    */
   const Integer operator -(const Integer &other) const;

   /**
    * Multiplication operator.
    */
   const Integer operator *(const Integer &other) const;

   /**
    * Division operator.
    */
   const Integer operator /(const Integer &other) const;

   /**
    * Modulo operator.
    */
   const Integer operator %(const Integer &other) const;
   
   
#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**

    * Addition operator with standard int.
    */
   const Integer operator +(_int other) const;
   
   /**
    * Subtraction operator with standard int.
    */
   const Integer operator -(_int other) const;
   
   /**
    * Multiplication operator with standard int.
    */
   const Integer operator *(_int other) const;
   
   /**
    * Division operator with standard int.
    */
   const Integer operator /(_int other) const;
   
   /**
    * Modulo operator with standard int.
    */
   const Integer operator %(_int other) const;
#endif


#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Addition operator with native int.
    */
   const Integer operator +(int other) const;
   
   /**
    * Subtraction operator with native int.
    */
   const Integer operator -(int other) const;
   
   /**
    * Multiplication operator with native int.
    */
   const Integer operator *(int other) const;
   
   /**
    * Division operator with native int.
    */
   const Integer operator /(int other) const;
   
   /**
    * Modulo operator with native int.
    */
   const Integer operator %(int other) const;
#endif

   /**
    * Addition operator with sizeof().
    */
   const Integer operator +(size_t other) const;
   
   /**
    * Subtraction operator with sizeof().
    */
   const Integer operator -(size_t other) const;
   
   /**
    * Multiplication operator with sizeof().
    */
   const Integer operator *(size_t other) const;
   
   /**
    * Division operator with sizeof().
    */
   const Integer operator /(size_t other) const;
   
   /**
    * Modulo operator with sizeof().
    */
   const Integer operator %(size_t other) const;
   

   /**
    * Returns the actual value stored.
    */
   __int raw() const;

protected:
   /**
    * Check the limits of the given value to ensure that no overflow
    * has occurred.
    * If the value is correct, it is assigned to _value.
    * If not, an exception is thrown.
    */
   void checkOverflow(__int value);
};

