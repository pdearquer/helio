/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** List of linked nodes.
 * List of nodes doubly linked in a chain. An interface similar
 * to the Queue is implemented, except that for nodes instead of
 * elements.
 *
 * A reference to the first and last node is kept to allow fast
 * insertion at both beginning and end. It is recommended to iterate
 * this list using first() and last() instead of the standard
 * iterator, it is faster and allows modification/removal.
 *
 * This graph is symmetric and does not allow loops (see Node::hasLink() for details).
 *
 * Nodes must derive from LinkedNode<N>.
 */
template<class N>
class LinkedList :
      public virtual Graph<N>
{
   friend class Storage::Structure::LinkedNode<N>;

   __CHECK_BASE(N, LinkedNode<N>);

protected:
   /**
    * First node of the list or null if empty.
    */
   N *_first;

   /**
    * Last node of the list or null if empty.
    */
   N *_last;


public:
   /**
    * Create an empty list.
    */
   LinkedList();

   /**
    * Create an empty list setting the ownership.
    */
   LinkedList(_bool owner);

   /**
    * Delete the contained nodes if in ownership.
    */
   virtual ~LinkedList();


   /**
    * Gets the number of nodes.
    */
   virtual _int count() const;

   /**
    * Counts the number of nodes in the list in reverse order.
    * Used in unit test.
    */
   virtual _int countReverse() const;

   /**
    * Says if the container has no node at all.
    */
   virtual _bool isEmpty() const;

   /**
    * Removes an element from the container overriding the ownership.
    * The equals() interface is used as in Comparable<T>.
    * @return true if the element was found.
    */
   virtual _bool remove(N *node, _bool deleting);

   /**
    * Removes all elements overriding the ownership.
    */
   virtual void clear(_bool deleting);


   /**
    * Returns the first node of the list or null if empty.
    */
   N *first() const;

   /**
    * Returns the last node of the list or null if empty.
    */
   N *last() const;


   /**
    * Adds a node to the queue.
    * The node is added at the end of the list.
    */
   virtual void enqueue(N *node);

   /**
    * Returns and remove the node at the end of the queue, i.e. the older.
    * This method overrides the ownership as to NOT delete the node.
    * The node is got from the beginning of the list.
    * If the list is empty, null is returned.
    */
   virtual N *dequeue();

   /**
    * Returns the older node of the queue but doesn't remove it.
    * The node is got from the beginning of the list.
    * If the list is empty, null is returned.
    */
   virtual N *front() const;

   /**
    * Adds a node to the queue at the front, i.e. in reverse order.
    * The node is added at the beginning of the list.
    */
   virtual void enqueue_front(N *node);

   /**
    * Returns and remove the node at the beginning of the queue, i.e. the last inserted in the normal order.
    * This method overrides the ownership as to NOT delete the node.
    * The node is got from the end of the list.
    * If the list is empty, null is returned.
    */
   virtual N *dequeue_back();

   /**
    * Returns the last inserted node of the queue but doesn't remove it.
    * The node is got from the end of the list.
    * If the list is empty, null is returned.
    */
   virtual N *back() const;


   /**
    * Gets a dynamic iterator over the container's elements.
    * This iterator must be deleted by the user.
    */
   virtual DynIterator<N> *dynIterate();
};

