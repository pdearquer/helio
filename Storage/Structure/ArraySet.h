/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Dynamic array Set implementation.
 * Set implementation using a dynamic array.
 */
template<class T>
class ArraySet : 
      public virtual Set<T>, public virtual ArrayBase<T>
{
   friend class Storage::Structure::ArraySetIterator<T>;

public:
   /**
    * Create an empty set.
    */
   ArraySet();
   
   /**
    * Create an empty set setting the ownership.
    */
   ArraySet(_bool owner);

   /**
    * Delete the contained elements if in ownership.
    */
   virtual ~ArraySet();
   
   
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
};

