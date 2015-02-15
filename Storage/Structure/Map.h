/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Container of key-value pairs.
 * Container of non-duplicated and non-null key elements associated to value elements.
 * The values can be null.
 *
 * Implemented as a container of the key elements, so note that the iteration is done
 * over the keys. No order is guarantied when iterating.
 */
template<class K, class V>
class Map : 
      public virtual Container<K>
{
   __CHECK_BASE(K, Comparable<K>);

public:
   /**
    * Adds a pair of elements into the map.
    * @return true if the key added is new.
    *    If not the older key and value are removed (and deleted if ownership is true).
    */
   virtual _bool add(K *key, V *value);

   /**
    * Adds a pair into the map overriding the ownership.
    * @return true if the key added is new.
    *    If not the older key and value are removed (and deleted if ownership is true).
    */
   virtual _bool add(K *key, V *value, _bool deleting) = 0;


   /**
    * Returns the stored value of associated to the given key.
    * @return The value object or null if none.
    *    Note that a key can exist and contain a null value, in this case null is returned.
    *    To check key existance, contains() must be used.
    */
   virtual V *get(K *key) = 0;
};

