/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Interface for objects that can be ordered among others
 * Interface for objects that can be ordered among others.
 *
 * The comparison result mus meet these properties:
 *    Consistent with equality: A->equals(B) => A->compare(B) = 0
 *    Inverse commutative: A->compare(B) = -B->compare(A)
 *    Transitive: (A->compare(B) > 0) && (B->compare(C) > 0) => (A.compare(C) > 0)
 *
 * The normal use of this template is as:
 *    class MyClass : public virtual Orderable<MyClass> { ...
 * To make a class orderable among others instances of itself.
 */
template<class T>
class Orderable : 
      public virtual Comparable<T>
{
public:
   /**
    * Compares itself with another object.
    * Returns 0 if equals, -1 if less and +1 if greater than it.
    */
   virtual _int compare(const T *other) const = 0;
};

