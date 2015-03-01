/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Linked list node minimal structure.
 * Doubly linked list node.
 *
 * This node does not support belonging to more than one graph.
 */
template<class N>
class LinkedNode :
      public virtual Node<N>
{
   friend class Storage::Structure::LinkedList<N>;

protected:
   /**
    * Reference to the list containing this node.
    */
   LinkedList<N> *_list;

   /**
    * Reference to the previous node or null if none.
    */
   N *_prev;

   /**
    * Reference to the next node or null if none.
    */
   N *_next;


public:
   /**
    * Ensures null references.
    */
   LinkedNode();


   /**
    * Returns a reference to the previous node or null if none.
    */
   N *prev();

   /**
    * Returns a reference to the next node or null if none.
    */
   N *next();


   /**
    * Remove this node from the list.
    * Warning, after calling this method, the object may not
    * exist any more (depending on the LinkedList nodes ownership).
    */
   void removeThis();

   /**
    * Remove this node from the list using the given deleting flag.
    * Warning, if deleting is true, after calling this method, the object
    * will not exist any more.
    */
   void removeThis(_bool deleting);

   /**
    * Remove the previous node from the list.
    */
   void removePrev();

   /**
    * Remove the next node from the list.
    */
   void removeNext();


   /**
    * Insert another node after this in the list.
    */
   void insertAfter(N *node);

   /**
    * Insert another node before this in the list.
    */
   void insertBefore(N *node);


   /**
    * Swaps this node with the previous, so this becomes closer to the head.
    * If this is the first node an exception is thrown.
    */
   void swapWithPrev();

   /**
    * Swaps this node with the next, so this becomes closer to the tail.
    * If this is the last node an exception is thrown.
    */
   void swapWithNext();

   /**
    * Swaps positions with another node of the list.
    */
   void swap(N *other);


protected:
   /**
    * Notification of being added to a container.
    * An exception is thrown if any restriction applies.
    * This event is called before the actual operation, so an exception will
    * abort the process.
    * Static restrictions to the container are also necessary.
    */
   virtual void adding(Object *container);

   /**
    * Notification of being removed from a container.
    * This event is called after the actual operation.
    * Static restrictions to the container can be applied.
    */
   virtual void removed(Object *container);

public:
   /**
    * Returns true if this node has a link to the other provided.
    * Note that A->hasLink(B) does not necessarily mean that B->hasLink(A),
    * this is only true for symmetric graphs. Read the description of each
    * graph implementation to know if it is symmetric.
    */
   virtual _bool hasLink(N *other);
};

