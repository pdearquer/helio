/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Iterator for ArraySetIterator
 * Iterator for the ArraySetIterator container.
 */
template<class T>
class ArraySetIterator :
      public virtual DynIterator<T>
{
protected:
   /**
    * Set reference.
    */
   ArraySet<T> *_set;
   
   /**
    * Current index position.
    */
   _int _position;
   
   
public:
   /**
    * Prepare the iterator from the begging of the array.
    */
   ArraySetIterator(ArraySet<T> *set);
   
   
   /**
    * If the container has more elements to iterate.
    * That means that get() returns a valid element.
    */
   virtual _bool hasMore() const;
   
   /**
    * Returns the current element in the container.
    */
   virtual T *get();
   
   /**
    * Moves to the next element returning the current one.
    */
   virtual T *next();
};

