/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template<class K, class V> ArrayMapIterator<K, V>::ArrayMapIterator(ArrayMap<K, V> *map)
{
   this->_map = map;
   this->_position = 0;
   this->startVersion(this->_map);
}


template<class K, class V> _bool ArrayMapIterator<K, V>::hasMore() const
{
   this->checkVersion(this->_map);

   return (this->_position < this->_map->_count);
}
   
template<class K, class V> K *ArrayMapIterator<K, V>::get()
{
   if(!hasMore())
   {
      MAKE_ERROR(ex, Error::Structure::IterationEnded);
      ex->addInt("position", this->_position);
      ex->addInt("count", this->_map->_count);
      throw ex;
   }
   
   return this->_map->_elements[this->_position]->key;
}
   
template<class K, class V> K *ArrayMapIterator<K, V>::next()
{
   if(!hasMore())
   {
      MAKE_ERROR(ex, Error::Structure::IterationEnded);
      ex->addInt("position", this->_position);
      ex->addInt("count", this->_map->_count);
      throw ex;
   }

   K *current = this->_map->_elements[this->_position]->key;
   this->_position++;
   return current;
}

} }

