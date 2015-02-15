/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base of any information class
 * Base of any information class
 */
class Object
{
public:
   /**
    * Default empty constructor.
    */
   Object();

   /**
    * Invalid copy constructor.
    * This method is not implemented in purpose to prevent static objects to
    * be incorrectly copied silently.
    */
   Object(const Object &o);

   /**
    * Virtual null descriptor that ensures that all descriptors are virtual.
    */
   virtual ~Object();
   
   
   /**
    * Invalid assign constructor.
    * This method is not implemented in purpose to prevent static objects to
    * be incorrectly copied silently.
    */
   const Object &operator=(const Object &o);

   /**
    * Compare itself with another object.
    * Return true if the instance is the same.
    */
   virtual _bool equals(const Object *other) const;
   
   /**
    * Generate a human readable string representing the object information.
    */
   virtual String toString() const;
   
   /**
    * Returns the class name of the object.
    */
   String getClass() const;
   

   /**
    * Check if belong to some class.
    */
   template <class T> _bool is();
   
   /**

    * Check if belong to some class (constant object version).
    */
   template <class T> _bool is() const;
   
   /**
    * Soft dynamic casting. If it fails returns null.
    */
   template <class T> T *tryAs();
   
   /**
    * Soft dynamic constant casting. If it fails returns null.
    */
   template <class T> const T *tryAs() const;
   
   /**
    * Hard dynamic casting. If it fails, throws an exception.
    */
   template <class T> T *as();
   
   /**
    * Hard dynamic constant casting. If it fails, throws an exception.
    */
   template <class T> const T *as() const;
};

