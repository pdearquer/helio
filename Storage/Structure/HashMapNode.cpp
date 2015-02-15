/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class K, class V> HashMapNode<K, V>::HashMapNode(K *k, V *v)
{
   key = k;
   value = v;
   next = null;
}

} }

