/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Iterator for HashMap
 * Iterator implementation for the HashMap container.
 */
template<class K, class V>
class HashMapIterator : 
      public virtual DynIterator<K>
{
protected:
   /**
    * Map reference.
    */
   HashMap<K, V> *_map;
   
   /**
    * Current node.
    */
   HashMapNode<K, V> *_node;
   
   /**
    * Current index positioning the table.
    */
   _int _index;
   
   
public:
   /**
    * Prepare the iterator from the begging of the map.
    */
   HashMapIterator(HashMap<K, V> *map);
   
   
   /**
    * If the container has more elements to iterate.
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

