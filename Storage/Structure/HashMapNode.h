/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** HashMap pair entry.
 * HashMap pair entry.
 */
template<class K, class V>
class HashMapNode :
      public virtual Object
{
public:
   /**
    * Stored key.
    */
   K *key;

   /**
    * Stored value.
    */
   V *value;
   
   /**
    * Next node in the bucket or null if none.
    */
   HashMapNode<K, V> *next;
   
   
   /**
    * Create an unlinked node.
    */   
   HashMapNode(K *k, V *v);
};

