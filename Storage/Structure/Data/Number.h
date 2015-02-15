/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base of any number
 * Base of any number
 */
class Number : 
      public virtual Orderable<Number>
{
public:
   /**
    * Return the value of the number converted to integer.
    */
   virtual _int getInt() const = 0;
   
   /**
    * Return the value of the number converted to float.
    */
   virtual _float getFloat() const = 0;
   
   
   /**
    * Compare itself with another number.
    * Return true if the value is the same.
    */
   virtual _bool equals(const Number *other) const;
   
   /**
    * Compare to other element.
    * Return 0 if equals, -1 if less and +1 if more than it.
    */
   virtual _int compare(const Number *other) const;
};

