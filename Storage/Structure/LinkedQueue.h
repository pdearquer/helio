/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Queue implemented as a linked list.
 * Implements the queue (and dequeue) functionality using a unrolled
 * double linked list.
 *
 * The nodes behind are hidden in order to keep tracking of the count
 * in a safe manner. This improves the performance of methods like
 * count() or add().
 */
template<class T>
class LinkedQueue :
      public virtual Queue<T>
{
   friend class Storage::Structure::LinkedQueueIterator<T>;

protected:
   /**
    * Linked list storing the information.
    */
   LinkedList<LinkedQueueNode<T>> *_list;

   /**
    * Elements count.
    */
   _int _count;


public:
   /**
    * Create an empty list.
    */
   LinkedQueue();

   /**
    * Create an empty list setting the ownership.
    */
   LinkedQueue(_bool owner);

   /**
    * Delete the contained elements if in ownership.
    */
   virtual ~LinkedQueue();


   /**
    * Gets the number of elements.
    * Null elements are included in the count.
    */
   virtual _int count() const;

   /**
    * Says if the container has no element.
    */
   virtual _bool isEmpty() const;

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
    * Adds an element to the queue.
    * The element is added at the end of the list.
    */
   virtual void enqueue(T *el);

   /**
    * Returns and remove the element at the end of the queue, i.e. the older.
    * This method overrides the ownership to NOT delete the element.
    * The element is got from the beginning of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *dequeue();

   /**
    * Returns the older element of the queue but doesn't remove it.
    * The element is got from the beginning of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *front() const;

   /**
    * Adds an element to the queue at the front, i.e. in reverse order.
    * The element is added at the beginning of the list.
    */
   virtual void enqueueFront(T *el);

   /**
    * Returns and remove the element at the beginning of the queue, i.e. the last inserted in the normal order.
    * This method overrides the ownership to NOT delete the element.
    * The element is got from the end of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *dequeueBack();

   /**
    * Returns the last inserted element of the queue but doesn't remove it.
    * The element is got from the end of the list.
    * If the list is empty, it throws an exception.
    */
   virtual T *back() const;


   /**
    * Gets a dynamic iterator over the container elements.
    * This iterator must be deleted by the user.
    */
   virtual DynIterator<T> *dynIterate();
};
