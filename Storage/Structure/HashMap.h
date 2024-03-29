/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Map based on a hash table.
 * Map that stores the pairs using a hash table of the keys.
 * The key objects must be Hashables.
 *
 * Implemented as a container of the key elements, so note that the iteration is done
 * over the keys. No order is warranted when iterating.
 */
template<class K, class V>
class HashMap : 
      public virtual Map<K, V>
{
   friend class Storage::Structure::HashMapIterator<K, V>;
   
   __CHECK_BASE(K, Hashable<K>);

protected:
   /**
    * Initial size of the table.
    */
   static_const_int INITIAL_CAPACITY = 13;
   
   /**
    * Table load factor; Relation elements to buckets that
    * triggers the size increase. 0.75f means that the table
    * will grow when at 75% of its capacity.
    */
   static_const_float LOAD_FACTOR = 0.75;
   

   /**
    * Array with the buckets (or null).
    */
   HashMapNode<K, V> **_table;
   
   /**
    * Number of buckets in the table.
    */
   _int _capacity;
   
   /**
    * Number of elements in the table.
    */
   _int _count;
   

public:
   /**
    * Create an empty map.
    */
   HashMap();
   
   /**
    * Create an empty map setting the ownership.
    */
   HashMap(_bool owner);

   /**
    * Delete the contained elements if in ownership.
    */
   virtual ~HashMap();
   
   
   /**
    * Gets the number of elements.
    */
   virtual _int count() const;

   /**
    * Adds a pair into the map overriding the ownership.
    * @return true if the key added is new.
    *    If not the older key and value are removed (and deleted if ownership is true).
    */
   virtual _bool add(K *key, V *value, _bool deleting);
   using Map<K, V>::add;
   
   /**
    * Checks if the set has a key.
    */
   virtual _bool contains(K *key);
   
   /**
    * Returns the stored value of associated to the given key.
    * @return The value object or null if none.
    *    Note that a key can exist and contain a null value, in this case null is returned.
    *    To check key existence, contains() must be used.
    */
   virtual V *get(K *key);
   
   /**
    * Removes an element from the container overriding the ownership.
    * The equals() interface is used as in Comparable<T>.
    * @return true if the element was found.
    */
   virtual _bool remove(K *key, _bool deleting);
   using Map<K, V>::remove;
   
   /**
    * Removes all elements overriding the ownership.
    */
   virtual void clear(_bool deleting);
   using Map<K, V>::clear;
   
   
   /**
    * Gets a dynamic iterator over the keys.
    * This iterator must be deleted by the user.
    * Do not modify the container while iterating or the iterator will
    * be invalidated with undetermined behaviour.
    */
   virtual DynIterator<K> *dynIterate();
   
   
protected:
   /**
    * Ensure a minimum capacity.
    */
   virtual void ensureCap(_int min);   
};

