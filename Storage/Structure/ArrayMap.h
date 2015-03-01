/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Map implementation using an array.
 * Map implementation using an array of entries. It is not very efficient, but only
 * require the keys to be Comparable.
 *
 * Implemented as a container of the key elements, so note that the iteration is done
 * over the keys. The insertion order is maintained. No null key is allowed internally.
 * The values must be Comparable so it can do searches on them.
 */
template<class K, class V>
class ArrayMap : 
      public virtual Map<K, V>, public virtual ArrayBase<MapEntry<K, V>>
{
   __CHECK_BASE(V, Comparable<V>);

   friend class Storage::Structure::ArrayMapIterator<K, V>;

public:
   /**
    * Create an empty map.
    */
   ArrayMap();
   
   /**
    * Create an empty map setting the ownership.
    */
   ArrayMap(_bool owner);

   /**
    * Delete the contained elements if in ownership.
    */
   virtual ~ArrayMap();
   
   
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
    * Checks if the map has a key.
    */
   virtual _bool contains(K *key);
   
   /**
    * Checks if the map has a value.
    */
   virtual _bool containsValue(V *value);
   
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
    * @return true if the element was found and removed.
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
};

