/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Iterator for LinkedQueue.
 * Iterator implementation for the LinkedQueue container.
 */
template<class T>
class LinkedQueueIterator :
      public virtual DynIterator<T>
{
protected:
   /**
    * Reference to the list.
    */
   LinkedQueue<T> *_list;

   /**
    * Current node or null if the end has been reached.
    */
   LinkedQueueNode<T> *_node;

   /**
    * Index of fhe element within the node.
    */
   _int _index;


public:
   /**
    * Prepare the iterator to run through the list.
    */
   LinkedQueueIterator(LinkedQueue<T> *list);


   /**
    * If the container has more elements to iterate.
    * That means that get() returns a valid element.
    */
   virtual _bool hasMore() const;

   /**
    * Returns the current element in the container.
    */
   virtual T *get();

   /**
    * Moves to the next element returning the current one.
    */
   virtual T *next();
};

