/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Container of nodes.
 * A graph is a container of nodes interconnected or linked among them.
 * The equivalent in graph theory for vertex is node and for edge is link.
 *
 * Some container require a significat amount of metainformation to store
 * every element, but give them structure. Checking if the element is contained
 * or retrieving it is not enough, in fact the biggest value is its relation
 * with other elments. Consider for example a tree.
 *
 * To be able to provide this information, the graph and all its descendents
 * store nodes instead of elements. The user must provide a node implementation
 * which derived from the container's associated node. It is possible mix different
 * classes as long as all of them implement derive from the required node.
 *
 * The insertion of null nodes is not permitted.
 */
template<class N>
class Graph :
      public virtual Container<N>
{
   __CHECK_BASE(N, Node<N>);

public:

};
