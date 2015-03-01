/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Set implementation using hash indices.
 * Dynamic hash table set with separate chaining by linked lists (called
 * buckets).
 *
 * The elements stored must be Hashable<> with themselves.
 *
 * No order is warranted when iterating.
 */
template<class T>
class HashSet : 
      public virtual Set<T>
{
   friend class Storage::Structure::HashSetIterator<T>;
   
   __CHECK_BASE(T, Hashable<T>);      
      
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
   HashSetNode<T> **_table;   
   
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
    * Create an empty set.
    */
   HashSet();
   
   /**
    * Create an empty set setting the ownership.
    */
   HashSet(_bool owner);

   /**
    * Delete the contained elements if in ownership.
    */
   virtual ~HashSet();
   
    
   /**
    * Gets the number of elements.
    */
   virtual _int count() const;

   /**
    * Adds an element into the set overriding the ownership.
    * @return true if the element added is new.
    *    If not the older equivalent is removed (and deleted if ownership is true).
    */
   virtual _bool add(T *el, _bool deleting);
   using Set<T>::add;
   
   /**
    * Checks if the set has an element.
    */
   virtual _bool contains(T *el);
   
   /**
    * Returns the stored element equals to the given.
    * @param el Element to look for.
    * @return The inner element that equals el or null if none.
    */
   virtual T *get(T *el);

   /**
    * Removes an element from the container overriding the ownership.
    * @return true if the element was found.
    */
   virtual _bool remove(T *el, _bool deleting);
   using Set<T>::remove;
   
   /**
    * Removes all elements overriding the ownership.
    */
   virtual void clear(_bool deleting);
   using Set<T>::clear;

   
   /**
    * Gets a dynamic iterator over the container elements.
    * This iterator must be deleted by the user.
    * Do not modify the container while iterating or the iterator will
    * be invalidated with undetermined behaviour.
    */
   virtual DynIterator<T> *dynIterate();
   
   
protected:
   /**
    * Ensure a minimum capacity.
    */
   virtual void ensureCap(_int min);
};

