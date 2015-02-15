/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Iterator for LinkedList.
 * Iterator implementation for the LinkedList container.
 */
template<class N>
class LinkedListIterator :
      public virtual DynIterator<N>
{
protected:
   /**
    * Reference to the list.
    */
   LinkedList<N> *_list;

   /**
    * Current node.
    */
   N *_node;


public:
   /**
    * Prepare the iterator to run through the list.
    */
   LinkedListIterator(LinkedList<N> *list);


   /**
    * If the container has more elements to iterate.
    */
   virtual _bool hasMore() const;

   /**
    * Returns the current element in the container.
    */
   virtual N *get();

   /**
    * Moves to the next element returning the current one.
    */
   virtual N *next();
};

