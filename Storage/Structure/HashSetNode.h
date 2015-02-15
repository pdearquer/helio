/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** HashSet element entry.
 * HashSet element entry.
 */
template<class T>
class HashSetNode :
      public virtual Object
{
public:
   /**
    * Stored element.
    */
   T *element;
   
   /**
    * Next node in the bucket or null if none.
    */
   HashSetNode<T> *next;
   
   
   /**
    * Create an unlinked node.
    */   
   HashSetNode(T *el);
};

