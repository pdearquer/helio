/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Memory address pointer
 * Pointer to a memory address.
 *
 * Static object.
 */
class Pointer : 
      public virtual StaticObject, public virtual Cloneable,
      public virtual Comparable<Pointer>, public virtual Hashable<Pointer>
{
public:
   /**
    * Null object or pointer.
    */
   static_const_pointer NULL = null;


protected:
   /**
    * Actual pointer.
    */
   __pointer _value;
   

public:
   /**
    * Creates a null pointer.
    */
   Pointer();

   /**
    * Copy constructor.
    */
   Pointer(const Pointer &other);
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC   
   /**
    * Creates it from a standard pointer.
    */
   Pointer(_pointer p);
#endif
   
#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Creates it from a native pointer.
    */
   Pointer(const void *p);
#endif
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC   
   /**
    * Creates a pointer from the address and move it some
    * bytes forward (positive) or backward (negative).
    */
   Pointer(_pointer p, _int bytes);
#endif
   
#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Creates a pointer from the address and move it some
    * bytes forward (positive) or backward (negative).
    */
   Pointer(const void *p, _int bytes);
#endif


   /**
    * Returns the value of the pointer.
    */
   Pointer get() const;

   /**
    * Sets the value of the pointer.
    */
   void set(const Pointer &other);


   /**
    * Says if the pointer is null.
    */
   _bool isNull() const;
   
   
   /**
    * Moves the pointer a number of bytes forward (positive) or
    * backward (negative).
    */
   void move(_int bytes);
   
   /**
    * Returns the difference in bytes from this pointer to other
    * (negative is the other is behind).
    */
   _int diff(const Pointer &to) const;
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Returns the difference in bytes from this pointer to other
    * (negative is the other is behind).
    */
   _int diff(_pointer to) const;
#endif

   
   /**
    * Compare to other pointer.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Pointer *other) const;
   
   /**
    * Compare itself with another pointer.
    * Return true if the address is the same.
    */
   virtual _bool equals(const Pointer *other) const;
   
   /**
    * Makes a copy of the object.
    */
   virtual Pointer *clone() const;

   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;
   
   
   /**
    * Generate a human readable string representing the pointer.
    */
   virtual String toString() const;
   
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Operator cast to standard pointer.
    */
   explicit operator _pointer() const;
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Operator cast to navite pointer.
    */
   explicit operator void*() const;
#endif


   /**
    * Assignment operator. Copy other into this.
    */
   void operator =(const Pointer &other);
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Assignment operator from standard.
    */
   void operator =(_pointer other);
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Assignment operator from native.
    */
   void operator =(const void *other);
#endif

   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const Pointer &other) const;

   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const Pointer &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const Pointer &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const Pointer &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const Pointer &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const Pointer &other) const;
   

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Comparison operator for standard; Equal.
    */
   _bool operator ==(_pointer other) const;

   /**
    * Comparison operator for standard; Unequal.
    */
   _bool operator !=(_pointer other) const;

   /**
    * Comparison operator for standard; Less than.
    */
   _bool operator <(_pointer other) const;

   /**
    * Comparison operator for standard; Greater than.
    */
   _bool operator >(_pointer other) const;

   /**
    * Comparison operator for standard; Less than or equal to.
    */
   _bool operator <=(_pointer other) const;

   /**
    * Comparison operator for standard; Greater than or equal to.
    */
   _bool operator >=(_pointer other) const;
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
   /**
    * Comparison operator for native; Equal.
    */
   _bool operator ==(const void *other) const;

   /**
    * Comparison operator for native; Unequal.
    */
   _bool operator !=(const void *other) const;

   /**
    * Comparison operator for native; Less than.
    */
   _bool operator <(const void *other) const;

   /**
    * Comparison operator for native; Greater than.
    */
   _bool operator >(const void *other) const;

   /**
    * Comparison operator for native; Less than or equal to.
    */
   _bool operator <=(const void *other) const;

   /**
    * Comparison operator for native; Greater than or equal to.
    */
   _bool operator >=(const void *other) const;
#endif

   /**
    * Returns the actual value stored.
    */
   virtual __pointer raw() const;
   
   /**
    * Sets the actual value stored.
    */
   virtual void setRaw(__pointer value);
   

   /* Static operations */
   
   /**
    * Moves the pointer a number of bytes forward (positive) or
    * backward (negative).
    */
   static Pointer move(const Pointer &p, _int bytes);
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Moves the pointer a number of bytes forward (positive) or
    * backward (negative).
    */
   static _pointer move(_pointer p, _int bytes);
#endif

   /**
    * Returns the difference in bytes from this pointer to other
    * (negative is the other is behind).
    */
   static _int diff(const Pointer &from, const Pointer &to);
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
   /**
    * Returns the difference in bytes from this pointer to other
    * (negative is the other is behind).
    */
   static _int diff(_pointer from, _pointer to);
#endif
};

