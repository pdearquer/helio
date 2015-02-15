/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Array map of pairs key-value for static types
 * Array map of pairs key-value implemented as a template for cast avoiding.
 */
template <class K, class T>
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
   T *_values;
   
   /**
    * Number of elements.
    */
   _int _length;
   
   /**
    * Array total lenght.
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
   Table(const Table<K, T> &other);
   
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
   _bool empty() const;
   
   
   /**
    * Adds an element to the table and returns true if was overwriten.
    */
   _bool add(K key, T value);
   
   /**
    * Set the value for the given key (it must exists).
    */
   void set(K key, T value);
      
   /**
    * Get a value from its key.
    */
   T get(K key) const;
      
   /**
    * Index operator (write allowed)
    */
   T &operator [](const K key);
   
   
   /**
    * Check if the value is in the table.
    */
   _bool contains(T value) const;
   
   /**
    * Check if the key is in the table.
    */
   _bool containsKey(K key) const;
      
   /**
    * Remove a entry from its key (not delete it).
    * The elements after reduce them index by one.
    */
   T remove(K key);
   
   /**
    * Removes all elements (not deleting it).
    */
   void clear();
   
   
   /**
    * Returns the first key of a value or null if not found.
    */
   K keyOf(T value) const;
   
   /**
    * Returns a key from a index (from 0 to count - 1).
    */
   K getKey(_int index) const;
   
   /**
    * Returns a value from a index (from 0 to count - 1).
    */
   T getValue(_int index) const;
   
   
   /**
    * Compare itself with another table.
    * Return true if the information is similar, but note that comparison is
    * performed by the == operator.
    */
   virtual _bool equals(const Table<K, T> &other) const;
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

