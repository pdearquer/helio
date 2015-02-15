/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Linked queue node.
 * Stores a static array of elements within the doubly linked node.
 */
template<class T>
class LinkedQueueNode :
   public virtual LinkedNode<LinkedQueueNode<T> >
{
   friend class Storage::Structure::LinkedQueue<T>;
   friend class Storage::Structure::LinkedQueueIterator<T>;

protected:
   /**
    * Number of elements stored in each node.
    */
   static_const_int CAPACITY = 128;


   /**
    * Contained element.
    */
   T *_elements[CAPACITY];

   /**
    * Actual number of elements stored.
    */
   _int _count;


public:
   /**
    * Preps an empty node.
    */
   LinkedQueueNode();


   /**
    * Returns the first element.
    */
   virtual T *front();

   /**
    * Tries to add an element at the beggining of the array.
    * @return false if there is no room for it.
    */
   virtual _bool add_front(T *el);

   /**
    * Returns and removes the first element.
    */
   virtual T *dequeue();


   /**
    * Returns the last element.
    */
   virtual T *back();

   /**
    * Tries to add an element at the end of the array.
    * @return false if there is no room for it.
    */
   virtual _bool add(T *el);

   /**
    * Returns and removes the last element.
    * @return
    */
   virtual T *dequeue_back();


   /**
    * Removes some elements from the node.
    * @param start Index of the first element to remove.
    * @param end Index of the last element to remove.
    * @param deleting Whether if delete the removed elements or not.
    */
   virtual void erase(_int start, _int end, _bool deleting);
};
