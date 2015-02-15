/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** LIFO queue of elements.
 * Last Input First Output queue of elements.
 */
template<class T>
class Stack : 
      public virtual List<T>
{
public:   
   /**
    * Adds an element to the stack.
    * The element is added at the end of the list.
    */
   virtual void push(T *el) = 0;
   
   /**
    * Returns and remove from the stack the last element inserted.
    * This method overrides the ownership to NOT delete the element.
    * The element is got from the end of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *pop() = 0;
   
   /**
    * Returns last element inserted in the stack but doesn't remove it.
    * The element is got from the end of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *peek() const = 0;
};

