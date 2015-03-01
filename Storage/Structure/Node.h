/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base of any graph node.
 * Any element inserted into a graph must derive from this class.
 * In fact every graph have a specific Node associated with the functionality
 * required for this container, and this is the class which must be derived.
 *
 * Note that the provided Nodes cannot be used directly, it is required an
 * implementation similar to:
 *    class MyNode : public virtual Node<MyNode>
 *    {
 *       // My data attributes
 *    };
 *
 * See Graph for more details.
 */
template<class N>
class Node :
      public virtual Object
//      public virtual Iterable<N>
{
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
    * This event is called after the actual operation, so all the references
    * can be cleared.
    * Static restrictions to the container can be applied.
    */
   virtual void removed(Object *container);


public:
   /**
    * Returns true if this node has a link to the other provided.
    *
    * Note that A->hasLink(B) does not necessarily mean that B->hasLink(A),
    * this is only true for symmetric graphs. In addition, A->hasLink(A) only
    * can happen for graphs that allow loops.
    *
    * Read the description of each graph implementation to know if it allows
    * loops and/or is symmetric.
    */
   virtual _bool hasLink(N *other) = 0;
};

