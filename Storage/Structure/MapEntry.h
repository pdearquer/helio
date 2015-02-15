/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Array map implementations pair entry.
 * Array map implementations pair entry. Note that this structure is not a node.
 */
template<class K, class V>
class MapEntry :
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
    * Create an unlinked node.
    */   
   MapEntry(K *k, V *v);
};

