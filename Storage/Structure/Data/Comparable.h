/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Interface for objects that can be compared with others for equality
 * Interface for objects that can be compared with others for equality.
 *
 * This interface force equality comparison between two objects. The
 * operation must meet these properties:
 *    Reflexive: A->equals(A) must be true
 *    Commutative: A->equals(B) => B->equals(A)
 *    Transitive: A->equals(B) && B->equals(C) => A->equals(C)
 *
 * The normal use of this template is as:
 *    class MyClass : public virtual Comparable<MyClass> { ...
 * To make a class comparable with itself.
 */
template<class T>
class Comparable :
      public virtual Object
{
public:  
   /**
    * Returns true if both objects contain the same information.
    * Check that other is null before calling this method.
    */
   virtual _bool equals(const T *other) const = 0;
};

