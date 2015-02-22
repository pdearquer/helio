/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Container of elements stored by index.
 * Stores elements assigning a stable numeric index to each one.
 * Preserves the order of insertion and ensures it on iterations.
 *
 * The elements can be null or repeated. Note that if the ownership
 * is true, the elements must NOT be repeated.
 *
 * When implementing a list, keep in mind that the elements can be null
 * (especially in comparisons).
 */
template<class T>
class List : 
      public virtual Container<T>
{
public:
   /**
    * Sets the number of elements removing the tail.
    * It cannot be higher than the current count.
    */
   virtual void setCount(_int num);

   /**
    * Sets the number of elements removing the tail overriding the ownership
    * It cannot be higher than the current count.
    */
   virtual void setCount(_int num, _bool deleting) = 0;

   /**
    * Adds an element at the end of the list.
    * @return The index assigned.
    */
   virtual _int add(T *el) = 0;
   
   /**
    * Sets the indexed element with a new one.
    */
   virtual void set(_int index, T *el);
   
   /**
    * Sets the indexed element with a new one overriding the ownership.
    */
   virtual void set(_int index, T *el, _bool deleting) = 0;
      
   /**
    * Returns the indexed element of the list.
    */
   virtual T *get(_int index) const = 0;

   /**
    * Checks if the list has an element.
    */
   virtual _bool contains(T *el);

   /**
    * Removes an element from the list overriding the ownership.
    * Set its position to null.
    * @return true if the element was found and removed.
    */
   virtual _bool remove(T *el, _bool deleting);
   using Container<T>::remove;

   /**
    * Removes the indexed element from the list.
    * Set its position to null.
    * @return Always true.
    */
   virtual _bool remove(_int index);
   
   /**
    * Removes the indexed element from the list overriding the ownership.
    * Set its position to null.
    * @return Always true.
    */
   virtual _bool remove(_int index, _bool deleting);

   /**
    * Removes all elements overriding the ownership.
    */
   virtual void clear(_bool deleting);
   using Container<T>::clear;
   
   /**
    * Erase the selected elements moving the elements ahead
    * back and reducing the count.
    * @start First element to erase.
    * @end Last element to erase.
    */
   virtual void erase(_int start, _int end);

   /**
    * Erase the selected elements moving the elements ahead
    * back and reducing the count.
    * @start First element to erase.
    * @end Last element to erase.
    */
   virtual void erase(_int start, _int end, _bool deleting) = 0;
   
   
   /**
    * Returns the position of an element.
    * The comparison is based on the instances.
    * @return -1 if the element isn't in the list.
    */
   virtual _int indexOf(T *el) const;
   
   /**
    * Returns the position of an element, starting after in the indicated index.
    * The comparison is based on the instances.
    * @return -1 if the element isn't in the list.
    */
   virtual _int indexOf(T *el, _int start) const;
};

