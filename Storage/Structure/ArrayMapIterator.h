/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Iterator for any ArrayBase
 * Iterator for any container derived from ArrayBase.
 */
template<class K, class V>
class ArrayMapIterator :
      public virtual DynIterator<K>
{
protected:
   /**
    * Map reference.
    */
   ArrayMap<K, V> *_map;
   
   /**
    * Current index position.
    */
   _int _position;
   
   
public:
   /**
    * Prepare the iterator from the begging of the map.
    */
   ArrayMapIterator(ArrayMap<K, V> *map);
   
   
   /**
    * If the container has more elements to iterate.
    * That means that get() returns a valid element.
    */
   virtual _bool hasMore() const;
   
   /**
    * Returns the current element in the container.
    */
   virtual K *get();
   
   /**
    * Moves to the next element returning the current one.
    */
   virtual K *next();
};

