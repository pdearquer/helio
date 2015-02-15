/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Dynamic array List implementation.
 * List implementation using a dynamic array.
 *
 * The stack interface is implemented by pushing elements at the end
 * of the list (as add do) and poping them from there.
 */
template<class T>
class ArrayList : 
      public virtual Stack<T>, public virtual ArrayBase<T>
{
   friend class Storage::Structure::ArrayListIterator<T>;

public:
   /**
    * Create an empty list.
    */
   ArrayList();
   
   /**
    * Create an empty list setting the ownership.
    */
   ArrayList(_bool owner);

   /**
    * Delete the contained elements if in ownership.
    */
   virtual ~ArrayList();
   

   /**
    * Gets the number of elements.
    * Null elements are included in the count.
    */
   virtual _int count() const;
   
   /**
    * Sets the number of elements removing the tail overriding the ownership.
    * It cannot be higher than the current count.
    */
   virtual void setCount(_int num, _bool deleting);
   using List<T>::setCount;

   /**
    * Adds an element at the end of the list.
    * @return The index assigned.
    */
   virtual _int add(T *el);
   
   /**
    * Sets the indexed element with a new one.
    */
   virtual void set(_int index, T *el, _bool deleting);
   using List<T>::set;
   
   /**
    * Returns the indexed element of the list.
    */
   virtual T *get(_int index) const;

   /**
    * Erase the selected elements moving the elements ahead
    * back and reducing the count.
    * @start First element to erase.
    * @end Last element to erase.
    */
   virtual void erase(_int start, _int end, _bool deleting);
   using List<T>::erase;
   
   
   /**
    * Adds an element to the stack.
    */
   virtual void push(T *el);
   
   /**
    * Returns and remove from the stack the last element inserted.
    * This method overrides the ownership to NOT delete the element.
    */
   virtual T *pop();
   
   /**
    * Returns last element inserted in the stack but doesn't remove it.
    */
   virtual T *peek() const;
   
   
   /**
    * Gets a dynamic iterator over the container elements.
    * This iterator must be deleted by the user.
    */
   virtual DynIterator<T> *dynIterate();
};

