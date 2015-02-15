/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base of every array implementation.
 * Variable size dynamic array for internal use in containers.
 */
template<class T>
class ArrayBase :
      public virtual Object
{
protected:
   /**
    * Inicial size of the array allocated.
    */
   static_const_int INICIAL_CAPACITY = 16;


   /**
    * Array of elements.
    */
   T **_elements;
   
   /**
    * Number of elements contained.
    */
   _int _count;
   
   /**
    * List current capacity (allocated positions).
    */
   _int _size;

   
   /**
    * Create an empty array.
    */
   ArrayBase();
   
   /**
    * Destroy the array NOT deleting its elements.
    */
   virtual ~ArrayBase();
   

   /**
    * Ensure a minimum capacity.
    */
   void ensureSize(_int min);
   
   /**
    * Adds an element at the end of the array.
    * @return The index assigned.
    */
   _int appendElement(T *el);
   
   /**
    * Erase the selected elements moving the elements ahead
    * back and reducing the count (eraseElements(i, i) erases the element i).
    * The elements are NOT deleted.
    * @start First element to erase.
    * @end Last element to erase.
    */
   void eraseElements(_int start, _int end);
};

