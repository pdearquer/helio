/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Iterator for HashSet
 * Iterator implementation for the HashSet container.
 */
template<class T>
class HashSetIterator : 
      public virtual DynIterator<T>
{
protected:
   /**
    * Set reference.
    */
   HashSet<T> *_set;
   
   /**
    * Current node.
    */
   HashSetNode<T> *_node;
   
   /**
    * Current index positionin the table.
    */
   _int _index;
   
   
public:
   /**
    * Prepare the iterator from the begging of the set.
    */
   HashSetIterator(HashSet<T> *set);
   
   
   /**
    * If the container has more elements to iterate.
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

