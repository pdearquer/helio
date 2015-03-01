/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Array map of pairs key-value for static types
 * Array map of pairs key-value implemented as a template for cast avoiding.
 */
template <class K, class V>
class Table :
      public virtual Object
{
protected:
   /**
    * Array of stored keys.
    */
   K *_keys;
   
   /**
    * Array of stored values.
    */
   V *_values;
   
   /**
    * Number of elements of the container.
    */
   _int _count;
   
   /**
    * Number of elements allocated in the array.
    */
   _int _size;
   
   
public:
   /**
    * Create an empty table.
    */
   Table();
   
   /**
    * Create an empty table with the given capacity.
    */
   Table(_int capacity);
   
   /**
    * Copy other table.
    */
   Table(const Table<K, V> &other);
   
   /**
    * Destroy the table.
    */
   virtual ~Table();
   
   
   /**
    * Gets the number of elements.
    */
   _int count() const;
   
   /**
    * Says if the table has no element.
    */
   _bool isEmpty() const;
   
   
   /**
    * Adds an element to the table.
    * @return true if other was overwritten.
    */
   _bool add(K key, V value);
   
   /**
    * Set the value for the given key (it must exists).
    */
   void set(K key, V value);
      
   /**
    * Get a value from its key.
    */
   V get(K key) const;
      
   /**
    * Index operator (write allowed)
    */
   V &operator [](const K key);
   
   
   /**
    * Check if the key is in the table.
    */
   _bool contains(K key) const;
   
   /**
    * Check if the value is in the table.
    */
   _bool containsValue(V value) const;
      
   /**
    * Remove a entry from its key if found.
    * The elements after it decrease their index by one.
    * @return true if the element was found and removed.
    */
   _bool remove(K key);
   
   /**
    * Removes all elements.
    */
   void clear();
   
   
   /**
    * Returns the first key of a value or null if not found.
    */
   K keyOf(V value) const;
   
   /**
    * Returns a key from a index (from 0 to count - 1).
    */
   K getKey(_int index) const;
   
   /**
    * Returns a value from a index (from 0 to count - 1).
    */
   V getValue(_int index) const;
   
   
   /**
    * Compare itself with another table.
    * Return true if the information is similar. Note that the comparison is
    * done with the == operator.
    */
   virtual _bool equals(const Table<K, V> &other) const;
   using Object::equals;
   
   /**
    * Generate a human readable string representing the object information.
    */
   virtual String toString() const;
   
   
protected:
   /**
    * Ensure a minimum capacity.
    */
   void ensureSize(_int min);
};

