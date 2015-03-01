/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Boolean primitive type
 * Boolean type, variable whose value is true or false.
 *
 * Static object.
 */
class Boolean : 
      public virtual Cloneable, public virtual Hashable<Boolean>
{
public:
   /**
    * False value.
    */
   static_const_bool FALSE = false;
   
   /**
    * True value.
    */
   static_const_bool TRUE = true;
   

protected:
   /**
    * Actual value.
    */
   __bool _value;
   

public:
   /**
    * Initialize to false.
    */
   Boolean();

   /**
    * Copy constructor.
    */
   Boolean(const Boolean &other);

   /**
    * Copy constructor.
    */
   Boolean(const Boolean *other);

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Initialize from a standard value.
    */
   Boolean(_bool value);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Initialize from a native value.
    */
   Boolean(bool value);
#endif
   
   
   /**
    * Gets the current value.
    */
   Boolean get() const;
   
   /**
    * Set the value.
    */
   void set(const Boolean &other);
   
   
   /**
    * Compare itself with another object.
    * Return true if the information is similar.
    */
   virtual _bool equals(const Boolean *other) const;
   
   /**
    * Makes a copy of the object.
    */
   virtual Boolean *clone() const;

   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;
   
   
   /**
    * Generate a human readable string representing the object information.
    */
   virtual String toString() const;
   
   
#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Operator cast to standard bool.
    */
   operator _bool() const;
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Operator cast to native bool.
    */
   operator bool() const;
#endif

   
   /**
    * Assignment operator. Copy other into this.
    */
   void operator =(const Boolean &other);
   
#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Assignment operator from standard.
    */
   void operator =(_bool other);
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Assignment operator from native.
    */
   void operator =(bool other);
#endif


   /**
    * Logical operator; Not
    */
   const Boolean operator !() const;

   /**
    * Logical operator; And
    */
   const Boolean operator &&(const Boolean& other) const;

   /**
    * Logical operator; Or
    */
   const Boolean operator ||(const Boolean& other) const;

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
   /**
    * Logical operator for standard type; And
    */
   const Boolean operator &&(_bool other) const;

   /**
    * Logical operator for standard type; Or
    */
   const Boolean operator ||(_bool other) const;
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
   /**
    * Logical operator for native type; And
    */
   const Boolean operator &&(bool other) const;

   /**
    * Logical operator for native type; Or
    */
   const Boolean operator ||(bool other) const;
#endif
};

