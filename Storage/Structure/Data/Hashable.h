/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Interface for any object able to generate a hash
 * Interface for any object able to generate a hash of the information
 * that contains.
 *
 * This interface implies comparability because it has to keep as especific
 * relation with the equality;
 *    a->equals(B) --> A->makeHash() == B->makeHash()
 * But not the oposite (different classes could generate the same hash).
 *
 * The way of using this template is as:
 *    class MyClass : public virtual Hashable<MyClass> { ...
 * To make sure that your class is comparable with itself.
 */
template<class T>
class Hashable : 
      public virtual Comparable<T>
{
public:
   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const = 0;
};

