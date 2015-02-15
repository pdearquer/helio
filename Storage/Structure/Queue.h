/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Bidirectional FIFO queue of elements.
 * First Input First Output queue of elements with efficient front insertion and back removal.
 * It supports reverse operation, compling with the double ended queue or deque model.
 */
template<class T>
class Queue :
      public virtual List<T>
{
public:
   /**
    * Adds an element to the queue.
    * The element is added at the end of the list.
    */
   virtual void enqueue(T *el) = 0;

   /**
    * Returns and remove the element at the end of the queue, i.e. the older.
    * This method overrides the ownership as to NOT delete the element.
    * The element is got from the beginning of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *dequeue() = 0;

   /**
    * Returns the older element of the queue but doesn't remove it.
    * The element is got from the beginning of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *front() const = 0;

   /**
    * Adds an element to the queue at the front, i.e. in reverse order.
    * The element is added at the beginning of the list.
    */
   virtual void enqueue_front(T *el) = 0;

   /**
    * Returns and remove the element at the beginning of the queue, i.e. the last inserted in the normal order.
    * This method overrides the ownership as to NOT delete the element.
    * The element is got from the end of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *dequeue_back() = 0;

   /**
    * Returns the last inserted element of the queue but doesn't remove it.
    * The element is got from the end of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *back() const = 0;
};
