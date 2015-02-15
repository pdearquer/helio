/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Container of non-duplicated elements.
 * Container of non-duplicated and non-null elements.
 *
 * The elements stored must be Comparable<> with themsleves.
 *
 * No order is guarantied when iterating.
 */
template<class T>
class Set : 
      public virtual Container<T>
{
   __CHECK_BASE(T, Comparable<T>);
   
public:
   /**
    * Adds an element into the set.
    * @return true if the element added is new.
    *    If not the older equivalent is removed (and deleted if ownership is true).
    */
   virtual _bool add(T *el);
   
   /**
    * Adds an element into the set overriding the ownership.
    * @return true if the element added is new.
    *    If not the older equivalent is removed (and deleted if ownership is true).
    */
   virtual _bool add(T *el, _bool deleting) = 0;


   /**
    * Returns the stored element equals to the given.
    * @param el Element to look for.
    * @return The inner element that equals el or null if none.
    */
   virtual T *get(T *el) = 0;
};

