/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Floating point number.
 * Floating point safe number.
 *
 * This implementation does not allow not numbers as a result of an operation,
 * and so it will throw an exception on operations like 1.0/0.0, which are valid
 * in C++. It also forbids denormal values, rounding them to 0.0, and adds the
 * modulo operator (should we?).
 *
 * Note that the native type is double, not float. So that you don't have to write
 * the "f" every time (e.g. 1.2f).
 *
 * Static object.
 */
class Float :
      public virtual StaticObject, public virtual Cloneable,
      public virtual Orderable<Float>, public virtual Hashable<Float>,
      public virtual Number
{
public:
   /**
    * Minimum value.
    */
   static_const_float MIN = __HELIO_TYPE_FLOAT_MIN;

   /**
    * Maximum value.
    */
   static_const_float MAX = __HELIO_TYPE_FLOAT_MAX;
   
   /**
    * Minimum value representable with the precision.
    */
   static_const_float EPSILON = __HELIO_TYPE_FLOAT_EPSILON;
   

protected:
   /**
    * Actual value store.
    */
   __float _value;
   

public:
   /**
    * Initialize to zero.
    */
   Float();
   
   /**
    * Copy constructor.
    */
   Float(const Float &other);

   /**
    * Copy constructor.
    */
   Float(const Float *other);

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Initialize from a standard value.
    */
   Float(_float value);
#endif
   
#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Initialize from a native value.
    */
   Float(double value);
#endif


   /**
    * Initialize from an integer.
    */
   explicit Float(const Integer &value);
   
#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Initialize from an standard integer.
    */
   explicit Float(_int value);
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
   /**
    * Initialize from a native integer.
    */
   explicit Float(int value);
#endif
   

   /**
    * Return the value of the float.
    */
   Float get() const;
   
   /**
    * Set the value of the float.
    */
   void set(const Float &other);

   
   /**
    * Return the value of the number converted to integer.
    */
   virtual _int getInt() const;

   /**
    * Return the value of the number converted to float.
    */
   virtual _float getFloat() const;
   
   
   /**
    * Check if it is a normal number.
    */
   _bool isNumber() const;
   
   /**
    * Check if it is Not a Number.
    */
   _bool isNaN() const;
   
   /**
    * Check if it is infinity.
    */
   _bool isInfinity() const;
   
   
   /**
    * Compare to other float.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Float *other) const;
   
   /**
    * Compare itself with another number.
    * Return true if the value is the same.
    */
   virtual _bool equals(const Float *other) const;
   
   /**
    * Makes a copy of the object.
    */
   virtual Float *clone() const;
   
   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;
   
   
   /**
    * Generate a human readable string representing the number.
    */
   virtual String toString() const;
   
   
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Operator cast to standard.
    */
   operator _float() const;
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Operator cast to navite.
    */
   explicit operator double() const;
#endif

#ifndef __HELIO_TYPE_INT_IS_STATIC
   /**
    * Operator cast to integer.
    */
   explicit operator _int() const;
#endif


   /**
    * Assignment operator. Copy other into this.
    */
   void operator =(const Float &other);

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Assignment operator from standard.
    */
   void operator =(_float other);
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Assignment operator from native.
    */
   void operator =(double other);
#endif
   

   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const Float &other) const;

   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const Float &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const Float &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const Float &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const Float &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const Float &other) const;


#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Comparison operator for standard int; Equal.
    */
   _bool operator ==(_float other) const;

   /**
    * Comparison operator for standard int; Unequal.
    */
   _bool operator !=(_float other) const;

   /**
    * Comparison operator for standard int; Less than.
    */
   _bool operator <(_float other) const;

   /**
    * Comparison operator for standard int; Greater than.
    */
   _bool operator >(_float other) const;

   /**
    * Comparison operator for standard int; Less than or equal to.
    */
   _bool operator <=(_float other) const;

   /**
    * Comparison operator for standard int; Greater than or equal to.
    */
   _bool operator >=(_float other) const;
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Comparison operator for native int; Equal.
    */
   _bool operator ==(double other) const;

   /**
    * Comparison operator for native int; Unequal.
    */
   _bool operator !=(double other) const;

   /**
    * Comparison operator for native int; Less than.
    */
   _bool operator <(double other) const;

   /**
    * Comparison operator for native int; Greater than.
    */
   _bool operator >(double other) const;

   /**
    * Comparison operator for native int; Less than or equal to.
    */
   _bool operator <=(double other) const;

   /**
    * Comparison operator for native int; Greater than or equal to.
    */
   _bool operator >=(double other) const;
#endif


   /**
    * Addition and assignment operator.
    */
   void operator +=(const Float &other);

   /**
    * Subtraction and assignment operator.
    */
   void operator -=(const Float &other);

   /**
    * Multiplication and assignment operator.
    */
   void operator *=(const Float &other);

   /**
    * Division and assignment operator.
    */
   void operator /=(const Float &other);

   /**
    * Modulo and assignment operator.
    */
   void operator %=(const Float &other);
   

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**
    * Addition and assignment operator with standard int.
    */
   void operator +=(_float other);
   
   /**
    * Subtraction and assignment operator with standard int.
    */
   void operator -=(_float other);
   
   /**
    * Multiplication and assignment operator with standard int.
    */
   void operator *=(_float other);
   
   /**
    * Division and assignment operator with standard int.
    */
   void operator /=(_float other);
   
   /**
    * Modulo and assignment operator with standard int.
    */
   void operator %=(_float other);
#endif


#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Addition and assignment operator with native int.
    */
   void operator +=(double other);
   
   /**
    * Subtraction and assignment operator with native int.
    */
   void operator -=(double other);
   
   /**
    * Multiplication and assignment operator with native int.
    */
   void operator *=(double other);
   
   /**
    * Division and assignment operator with native int.
    */
   void operator /=(double other);
   
   /**
    * Modulo and assignment operator with native int.
    */
   void operator %=(double other);
#endif
   

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
   const Float operator -() const;
   
   
   /**
    * Addition operator.
    */
   const Float operator +(const Float &other) const;

   /**
    * Subtraction operator.
    */
   const Float operator -(const Float &other) const;

   /**
    * Multiplication operator.
    */
   const Float operator *(const Float &other) const;

   /**
    * Division operator.
    */
   const Float operator /(const Float &other) const;

   /**
    * Modulo operator.
    */
   const Float operator %(const Float &other) const;
   
   
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
   /**

    * Addition operator with standard int.
    */
   const Float operator +(_float other) const;
   
   /**
    * Subtraction operator with standard int.
    */
   const Float operator -(_float other) const;
   
   /**
    * Multiplication operator with standard int.
    */
   const Float operator *(_float other) const;
   
   /**
    * Division operator with standard int.
    */
   const Float operator /(_float other) const;
   
   /**
    * Modulo operator with standard int.
    */
   const Float operator %(_float other) const;
#endif


#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
   /**
    * Addition operator with native int.
    */
   const Float operator +(double other) const;
   
   /**
    * Subtraction operator with native int.
    */
   const Float operator -(double other) const;
   
   /**
    * Multiplication operator with native int.
    */
   const Float operator *(double other) const;
   
   /**
    * Division operator with native int.
    */
   const Float operator /(double other) const;
   
   /**
    * Modulo operator with native int.
    */
   const Float operator %(double other) const;
#endif


   /**
    * Returns the actual value stored.
    */
   virtual __float raw() const;
   
   /**
    * Sets the actual value stored.
    */
   virtual void setRaw(__float value);
   
protected:
   /**
    * Check the limits of the given value to ensure that no overflow
    * has occurred.
    * If the value is correct, it is assigned to _value.
    * If not, an exception is thrown.
    */
   virtual void checkOverflow(__float value);
};

