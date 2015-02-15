/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template<class K, class V> _bool Map<K, V>::add(K *key, V *value)
{
   this->modified();

   return add(key, value, this->ownership());
}

} }

